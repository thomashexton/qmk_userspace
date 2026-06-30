#!/usr/bin/env python3
"""Generate a per-key physical layout (QMK info.json style) for the IFKB
Ergolite, in LAYOUT_eglt order: 4 main rows x 14 cols (7 left + 7 right) then a
10-key thumb row (5 per hand). Column stagger + thumb arc approximate the board;
tweak the tables below and re-run to nudge."""
import json

# Column stagger (downward y offset), left hand cols 0..6 = outer..inner.
LEFT_STAGGER = [0.35, 0.35, 0.15, 0.0, 0.10, 0.30, 0.45]
GAP = 2.0                     # blank space between the two halves
RIGHT_X0 = 6 + GAP           # x of right-hand inner col (c=7)

keys = []

def add(r, c, x, y):
    keys.append({"matrix": [r, c], "x": round(x, 3), "y": round(y, 3)})

# main grid: 4 rows x 14 cols
for r in range(4):
    for c in range(14):
        if c <= 6:                       # left hand, col0 outer .. col6 inner
            x = c
            stag = LEFT_STAGGER[c]
        else:                            # right hand, col7 inner .. col13 outer
            x = RIGHT_X0 + (c - 7)
            stag = LEFT_STAGGER[13 - c]  # mirror
        add(r, c, x, r + stag)

# thumb row: 10 keys, LAYOUT order — matches the receiver matrix (row 19).
# Left LAYOUT order is OUTER->INNER (matrix cols 2..6):
#   idx 0..4 = LALT, LCTL, L_OUTER(Space/Raise), L_INNER(Lower), ESC
# so ESC is the innermost left thumb (nearest the center), LALT the outermost.
# Shallow arc dipping at the thumb-home (Space) key; tweak to taste.
LEFT_THUMBS = [   # (x, y) for LALT, LCTL, L_OUTER, L_INNER, ESC  (outer -> inner)
    (2.3, 4.60),  # LALT          (outermost)
    (3.2, 4.85),  # LCTL
    (4.1, 5.00),  # L_OUTER Space  (thumb home, lowest)
    (5.0, 4.85),  # L_INNER Lower
    (5.9, 4.60),  # ESC           (innermost, near center)
]
# Right LAYOUT order is INNER->OUTER (matrix cols 9..13): TO(GAME), R_INNER,
# R_OUTER, (xxx), RGUI — the mirror of the left row, reversed.
CENTER = 7.0  # mirror axis (midway between the two inner columns)
right_thumbs = [(2 * CENTER - x, y) for (x, y) in reversed(LEFT_THUMBS)]

for i, (x, y) in enumerate(LEFT_THUMBS):
    add(4, i, x, y)
for i, (x, y) in enumerate(right_thumbs):
    add(4, 5 + i, x, y)

out = {"keyboard": "ergolite", "layouts": {"LAYOUT": {"layout": keys}}}
import sys
path = sys.argv[1] if len(sys.argv) > 1 else "/dev/stdout"
with open(path, "w") as f:
    json.dump(out, f, indent=1)
print(f"wrote {path}: {len(keys)} keys")
