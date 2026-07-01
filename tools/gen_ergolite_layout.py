#!/usr/bin/env python3
"""Generate a per-key physical layout (QMK info.json style) for the IFKB
Ergolite, in LAYOUT_eglt order: 4 main rows x 14 cols (7 left + 7 right) then a
10-key thumb row (5 per hand). Column stagger + thumb arc approximate the board;
tweak the tables below and re-run to nudge."""
import json

# Column stagger (downward y offset), left hand cols 0..6 = outer..inner.
LEFT_STAGGER = [0.35, 0.35, 0.15, 0.0, 0.10, 0.30, 0.45]
GAP = 6.0                     # blank space between the two halves
RIGHT_X0 = 6 + GAP           # x of right-hand inner col (c=7)

# Mirror axis = midpoint between the left inner column's right edge (x=7) and the
# right inner column's left edge (x = RIGHT_X0). Must use the edges, not the
# column origins, or the right thumbs land a half-unit off (under the wrong,
# lower-staggered column).
CENTER = (7 + RIGHT_X0) / 2
keys = []

def add(d):
    keys.append({k: (round(v, 3) if isinstance(v, float) else v) for k, v in d.items()})

# main grid: 4 rows x 14 cols
for r in range(4):
    for c in range(14):
        if c <= 6:                       # left hand, col0 outer .. col6 inner
            x = c
            stag = LEFT_STAGGER[c]
        else:                            # right hand, col7 inner .. col13 outer
            x = RIGHT_X0 + (c - 7)
            stag = LEFT_STAGGER[13 - c]  # mirror
        add({"matrix": [r, c], "x": x, "y": r + stag})

# Thumb keys, LAYOUT order idx0..4 (left OUTER->INNER, matrix cols 2..6), per
# Thomas's physical description. Bottom alpha row: C=col3 (x3), D=col4 (x4),
# V=col5 (x5); x is the key's top-left, y increases downward; r = clockwise
# degrees about (rx, ry).
LEFT_THUMBS = [
    # idx0: 1u, centered under the C|D boundary (x=4)
    {"x": 3.5, "y": 4.10, "w": 1, "h": 1},
    # idx1: 1u, centered under the D|V midline (x=5)
    {"x": 4.5, "y": 4.25, "w": 1, "h": 1},
    # idx2 (Space/Raise): 1x1.25, rotated 45 CW, bottom-left corner touching idx1
    {"x": 5.5, "y": 4.00, "w": 1, "h": 1.25, "r": 45, "rx": 5.5, "ry": 5.25},
    # idx3 (Lower): 1x1.25, rotated 45 CW, right beside idx2
    {"x": 6.21, "y": 4.71, "w": 1, "h": 1.25, "r": 45, "rx": 6.21, "ry": 5.96},
    # idx4: 1x1, tight-stacked directly on top of idx3 (same rotation, so it
    # nests above the Lower key in the rotated frame)
    {"x": 6.21, "y": 3.71, "w": 1, "h": 1, "r": 45, "rx": 6.21, "ry": 5.96},
]

def mirror(k):
    """Mirror a key across x=CENTER (for the right hand)."""
    m = dict(k)
    m["x"] = 2 * CENTER - k["x"] - k.get("w", 1)
    if "r" in k:
        m["r"] = -k["r"]
        m["rx"] = 2 * CENTER - k["rx"]
        m["ry"] = k["ry"]
    return m

# Right LAYOUT order idx5..9 is INNER->OUTER (matrix cols 9..13), i.e. the left
# row reversed and mirrored.
RIGHT_THUMBS = [mirror(k) for k in reversed(LEFT_THUMBS)]

for i, k in enumerate(LEFT_THUMBS):
    add({"matrix": [4, i], **k})
for i, k in enumerate(RIGHT_THUMBS):
    add({"matrix": [4, 5 + i], **k})

out = {"keyboard": "ergolite", "layouts": {"LAYOUT": {"layout": keys}}}
import sys
path = sys.argv[1] if len(sys.argv) > 1 else "/dev/stdout"
with open(path, "w") as f:
    json.dump(out, f, indent=1)
print(f"wrote {path}: {len(keys)} keys")
