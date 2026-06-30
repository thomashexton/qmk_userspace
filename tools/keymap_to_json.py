#!/usr/bin/env python3
"""Generate a QMK keymap.json from a macro-based thomashexton keymap.c.

The thomashexton userspace builds its layers from C macros (BASE_LAYER etc.)
plus a few project-specific wrapper macros (home-row mods, thumb keys, combos).
`qmk c2json` can't expand those without the full build include environment, so
this does a small targeted expansion and emits a plain QMK keymap.json that
keymap-drawer understands. See tools/draw_keymaps.sh for the full pipeline.

Usage:
  keymap_to_json.py <keymap.c> <users_dir> <out.json> \
      --keyboard NAME --layout LAYOUT --keycount N [--combos-out combos.yaml]

For the if_rec receiver, the keymap is the embedded Ergolite block (LAYOUT_eglt:
4 rows x 14 cols + a 10-key thumb row = 66 real keys per layer). Those 66 keys
are all real (7 cols + 5 thumbs per hand), so they're emitted as-is and drawn
against tools/ergolite.layout.json (a per-key physical layout) rather than the
receiver's useless ~253-key composite info.json. PAD_NOT_CONNECTED and its XX*
helpers live only in the LAYOUT_eglt wrapper, never in a layer body, and are
skipped in collect_defines.
"""
import argparse
import json
import re
import sys

# Canonical home-row-mod wrappers from users/thomashexton/home_row_mods.h.
# Left:  Ctrl Alt Gui Shift   Right: Shift Gui Alt Ctrl
HRM = {
    "TH_HRM_LEFT":  ["LCTL_T(KC_{})", "LALT_T(KC_{})", "LGUI_T(KC_{})", "LSFT_T(KC_{})"],
    "TH_HRM_RIGHT": ["RSFT_T(KC_{})", "RGUI_T(KC_{})", "RALT_T(KC_{})", "RCTL_T(KC_{})"],
}
HRM_MODS = {
    "TH_HRM_LEFT_MODS":  "KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX",
    "TH_HRM_RIGHT_MODS": "XXXXXXX, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL",
}
# Project custom keycodes -> short readable labels for the diagram.
CUSTOM_KC = {"P_SCROLL": "SCRL", "P_DEBUG": "PDBG"}
# Combo output keycode -> label.
COMBO_OUT = {"QK_BOOT": "BOOT", "KC_ESC": "ESC", "KC_TAB": "TAB", "KC_BTN2": "RCLK"}


def read(path):
    with open(path) as f:
        return f.read()


def parse_layer_enum(users_dir):
    """LAYER_BASE -> 0, LAYER_RAISE -> 1, ... from thomashexton.h."""
    m = re.search(r"enum\s+\w+\s*\{(.*?)\}", read(f"{users_dir}/thomashexton.h"), re.S)
    names, idx = {}, 0
    for line in m.group(1).splitlines():
        line = re.sub(r"//.*", "", line).strip().rstrip(",")
        if not line:
            continue
        nm = line.split("=")[0].strip()
        if "=" in line:
            idx = int(line.split("=")[1].strip())
        names[nm] = idx
        idx += 1
    return names


def collect_defines(src):
    """Single-line object-like #defines (THUMB_*, POINTER_HOLD_*, ...),
    excluding *_LAYER bodies and function-like macros."""
    out = {}
    for m in re.finditer(r"^#define\s+(\w+)\s+(.+)$", src, re.M):
        name = m.group(1)
        val = re.sub(r"//.*|/\*.*?\*/", "", m.group(2)).strip()
        if name.endswith("_LAYER") or name in HRM or name in HRM_MODS:
            continue
        # if_rec's PAD_NOT_CONNECTED is a multi-line continuation whose first
        # physical line is just a backslash; its XX* helpers only ever appear
        # inside that pad, never in a real layer body. Skip them so they don't
        # break re.sub (a lone "\\" is an invalid replacement) or pollute output.
        if val == "\\" or re.fullmatch(r"XX\d+", name):
            continue
        out[name] = val
    return out


def extract_layer_bodies(src):
    """LAYER_BODY_NAME -> raw text for each `#define X_LAYER \\ ...` block."""
    bodies = {}
    for m in re.finditer(r"#define\s+(\w+_LAYER)\s*\\\n(.*?)(?=\n#|\n//|\n/\*|\nconst|\n\Z)", src, re.S):
        body = re.sub(r"\\\s*\n", " ", m.group(2))   # join continuations
        body = re.sub(r"//.*", "", body)             # strip comments
        bodies[m.group(1)] = body.strip()
    return bodies


def expand(body, defines, layer_idx):
    for name, val in defines.items():            # THUMB_*, POINTER_HOLD_*
        body = re.sub(rf"\b{name}\b", val, body)
    for name, val in HRM_MODS.items():
        body = re.sub(rf"\b{name}\b", val, body)

    def hrm_sub(m):
        templates = HRM[m.group(1)]
        args = [a.strip() for a in m.group(2).split(",")]
        return ", ".join(t.format(a) for t, a in zip(templates, args))
    body = re.sub(r"\b(TH_HRM_LEFT|TH_HRM_RIGHT)\s*\(([^)]*)\)", hrm_sub, body)

    for nm, idx in sorted(layer_idx.items(), key=lambda kv: -len(kv[0])):
        body = re.sub(rf"\b{nm}\b", str(idx), body)  # LT/MO/TO/TG layer args
    for kc, label in CUSTOM_KC.items():
        body = re.sub(rf"\b{kc}\b", label, body)
    body = re.sub(r"_______", "KC_TRNS", body)
    body = re.sub(r"XXXXXXX", "KC_NO", body)
    return body


def split_top(body):
    """Split on commas not nested in parens."""
    out, depth, cur = [], 0, ""
    for ch in body:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return [k for k in out if k]


def extract_combos(users_dir):
    """combos.h: combo arrays + ALL_COMBOS table -> [(trigger_kcs, output)]."""
    txt = read(f"{users_dir}/combos.h")
    arrays = {}
    for m in re.finditer(r"(\w+)\[\]\s*=\s*\{([^}]*)\}", txt):
        keys = [k.strip() for k in m.group(2).split(",") if k.strip() not in ("", "COMBO_END")]
        arrays[m.group(1)] = keys
    combos = []
    for m in re.finditer(r"COMBO\(\s*(\w+)\s*,\s*([^)]+)\)", txt):
        if m.group(1) in arrays:
            combos.append((arrays[m.group(1)], m.group(2).strip()))
    return combos


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("keymap_c")
    ap.add_argument("users_dir")
    ap.add_argument("out_json")
    ap.add_argument("--keyboard", required=True)
    ap.add_argument("--layout", required=True)
    ap.add_argument("--keycount", type=int, required=True)
    ap.add_argument("--combos-out", help="write keymap-drawer combos yaml here")
    args = ap.parse_args()

    src = read(args.keymap_c)
    layer_idx = parse_layer_enum(args.users_dir)
    defines = collect_defines(src)
    bodies = extract_layer_bodies(src)

    assign = dict(re.findall(r"\[(\w+)\]\s*=\s*\w+\((\w+_LAYER)\)", src))
    if not assign:
        sys.exit("could not find keymaps[] assignments")

    max_idx = max(layer_idx[n] for n in assign)
    layers = [None] * (max_idx + 1)
    for lname, body_name in assign.items():
        keys = split_top(expand(bodies[body_name], defines, layer_idx))
        if len(keys) != args.keycount:
            sys.exit(f"{body_name}: got {len(keys)} keys, expected {args.keycount}")
        layers[layer_idx[lname]] = keys
    for i, l in enumerate(layers):           # unused layers (e.g. POINTER on oldman)
        if l is None:
            layers[i] = ["KC_NO"] * args.keycount

    with open(args.out_json, "w") as f:
        json.dump({"keyboard": args.keyboard, "keymap": "thomashexton",
                   "layout": args.layout, "layers": layers}, f, indent=2)
    print(f"wrote {args.out_json}: {len(layers)} layers x {args.keycount} keys")

    if args.combos_out:
        pos = {kc: i for i, kc in enumerate(layers[layer_idx["LAYER_BASE"]])}
        lines = ["combos:"]
        for triggers, out in extract_combos(args.users_dir):
            idxs = [pos.get(t) for t in triggers]
            if any(i is None for i in idxs):
                continue  # trigger key not on base layer (e.g. mouse combo)
            label = COMBO_OUT.get(out, out.replace("KC_", "").replace("QK_", ""))
            lines.append(f"  - {{p: {idxs}, k: {label}, l: [Base]}}")
        with open(args.combos_out, "w") as f:
            f.write("\n".join(lines) + "\n")
        print(f"wrote {args.combos_out}: {len(lines)-1} combos")


if __name__ == "__main__":
    main()
