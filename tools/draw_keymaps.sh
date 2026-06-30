#!/usr/bin/env bash
# Regenerate the keymap diagrams in docs/keymaps/ from the live keymap.c sources.
#
# Pipeline per board:  keymap.c --(keymap_to_json.py)--> keymap.json
#                      --(keymap parse)--> .yaml  --(keymap draw)--> .svg
# Physical layout comes from `qmk info` (merged, so it works for boards whose
# info.json is split across the QMK hierarchy, e.g. the charybdis).
#
# Requires: qmk CLI, keymap-drawer (`keymap`), python3.
# Run from anywhere; paths are resolved relative to this script.
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
USERSPACE="$(cd "$HERE/.." && pwd)"
USERS="$USERSPACE/users/thomashexton"
OUT="$USERSPACE/docs/keymaps"
CONFIG="$HERE/keymap_drawer.config.yaml"
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

mkdir -p "$OUT"

# Shared layer enum order (users/thomashexton/thomashexton.h):
# BASE=0 RAISE=1 LOWER=2 POINTER=3 SYMBOL=4 GAME=5
# GAME only exists on if_rec; the other boards stop at SYMBOL, so the name list
# passed to `keymap parse` is sliced to each board's actual layer count.
LAYER_NAMES=(Base Raise Lower Pointer Symbol Game)

# board_keyboard | keymap_dir | layers_to_draw
BOARDS=(
  "oldman/endgame|oldman/endgame|Base Raise Lower Symbol"
  "bastardkb/charybdis/3x5/v2/splinky_3|bastardkb/charybdis/3x5/v2/splinky_3|Base Raise Lower Symbol Pointer"
)

draw_board() {
  local kb="$1" kmdir="$2" select="$3"
  local name="${kb//\//_}"
  local kmc="$USERSPACE/keyboards/$kmdir/keymaps/thomashexton/keymap.c"
  echo "=== $kb ==="

  # Merged physical layout + key count from qmk.
  qmk info -kb "$kb" -f json >"$TMP/$name.info.json" 2>/dev/null
  local layout keycount
  layout="$(python3 -c "import json;d=json.load(open('$TMP/$name.info.json'));print(next(iter(d['layouts'])))")"
  keycount="$(python3 -c "import json;d=json.load(open('$TMP/$name.info.json'));print(len(d['layouts']['$layout']['layout']))")"

  python3 "$HERE/keymap_to_json.py" "$kmc" "$USERS" "$TMP/$name.json" \
    --keyboard "$kb" --layout "$layout" --keycount "$keycount" \
    --combos-out "$TMP/$name.combos.yaml"

  local nlayers
  nlayers="$(python3 -c "import json;print(len(json.load(open('$TMP/$name.json'))['layers']))")"
  keymap parse -q "$TMP/$name.json" -l "${LAYER_NAMES[@]:0:$nlayers}" -o "$TMP/$name.yaml"
  # shellcheck disable=SC2086
  keymap -c "$CONFIG" draw "$TMP/$name.yaml" "$TMP/$name.combos.yaml" \
    -j "$TMP/$name.info.json" -s $select -o "$OUT/$name.svg"
  echo "    -> docs/keymaps/$name.svg"
}

for entry in "${BOARDS[@]}"; do
  IFS='|' read -r kb kmdir select <<<"$entry"
  draw_board "$kb" "$kmdir" "$select"
done

# if_rec is the 2.4GHz receiver/dongle; you type on the IFKB Ergolite. The
# receiver's own LAYOUT is a useless ~253-key composite of three boards, so we
# draw the embedded Ergolite block (LAYOUT_eglt: 66 real keys = 7 cols + 5 thumbs
# per hand) against tools/ergolite.layout.json, a hand-authored per-key physical
# layout. Output is named for the keyboard you actually use: ergolite.svg.
# GAME (QWERTY) is drawn; the empty POINTER layer is skipped.
draw_eglt() {
  local kmc="$USERSPACE/keyboards/if_rec/keymaps/thomashexton/keymap.c"
  local layout_json="$HERE/ergolite.layout.json"
  local name="ergolite"
  local select="Base Raise Lower Symbol Game"
  echo "=== ergolite (if_rec firmware; per-key physical layout) ==="

  python3 "$HERE/keymap_to_json.py" "$kmc" "$USERS" "$TMP/$name.json" \
    --keyboard ergolite --layout LAYOUT --keycount 66 \
    --combos-out "$TMP/$name.combos.yaml"

  local nlayers
  nlayers="$(python3 -c "import json;print(len(json.load(open('$TMP/$name.json'))['layers']))")"
  keymap parse -q "$TMP/$name.json" -l "${LAYER_NAMES[@]:0:$nlayers}" -o "$TMP/$name.yaml"
  # shellcheck disable=SC2086
  keymap -c "$CONFIG" draw "$TMP/$name.yaml" "$TMP/$name.combos.yaml" \
    -j "$layout_json" -s $select -o "$OUT/$name.svg"
  echo "    -> docs/keymaps/$name.svg"
}

draw_eglt
