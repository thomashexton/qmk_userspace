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

# if_rec is a 2.4GHz receiver whose LAYOUT is a 253-key composite of three
# physical keyboards (ergo+corne+alice) padded with PAD_NOT_CONNECTED. The real
# keymap is just the embedded Ergolite block (4 rows x 14 + a 10-key thumb row),
# so we expand with keymap_to_json.py --eglt (which drops the pad columns down to
# the 49 real keys) and render against a SYNTHETIC cols+thumbs layout instead of
# the useless composite info.json. GAME (QWERTY) reduces cleanly and is drawn;
# the empty POINTER layer is skipped.
draw_eglt() {
  local kb="if_rec" kmdir="if_rec"
  local name="$kb"
  local kmc="$USERSPACE/keyboards/$kmdir/keymaps/thomashexton/keymap.c"
  # 5 cols/hand x 4 rows (number row + 3 alpha) + 5 left / 4 right thumbs.
  local cols_thumbs='44444+5 4+44444'
  local select="Base Raise Lower Symbol Game"
  echo "=== $kb (eglt; synthetic $cols_thumbs layout) ==="

  python3 "$HERE/keymap_to_json.py" "$kmc" "$USERS" "$TMP/$name.json" \
    --keyboard "$kb" --layout LAYOUT --keycount 66 --eglt \
    --combos-out "$TMP/$name.combos.yaml"

  local nlayers
  nlayers="$(python3 -c "import json;print(len(json.load(open('$TMP/$name.json'))['layers']))")"
  keymap parse -q "$TMP/$name.json" -l "${LAYER_NAMES[@]:0:$nlayers}" -o "$TMP/$name.yaml"
  # shellcheck disable=SC2086
  keymap -c "$CONFIG" draw "$TMP/$name.yaml" "$TMP/$name.combos.yaml" \
    -n "$cols_thumbs" -s $select -o "$OUT/$name.svg"
  echo "    -> docs/keymaps/$name.svg"
}

draw_eglt
