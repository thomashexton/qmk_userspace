# Keymap diagrams

Auto-generated visual references for the `thomashexton` keymaps, one SVG per
board. These are rendered from the live `keymap.c` sources — open them in a
browser (or any SVG viewer) to see each layer, the home-row mods (tap label
large / hold mod small), thumb layer-taps, and the combos (drawn as separate
mini-boards in a "Combos:" section).

| Board | Diagram |
|-------|---------|
| oldman/endgame | [oldman_endgame.svg](oldman_endgame.svg) |
| bastardkb/charybdis 3x5 | [bastardkb_charybdis_3x5_v2_splinky_3.svg](bastardkb_charybdis_3x5_v2_splinky_3.svg) |
| IFKB Ergolite (if_rec firmware) | [ergolite.svg](ergolite.svg) |

## Regenerating

```sh
./tools/draw_keymaps.sh
```

Pipeline: `keymap.c` → `tools/keymap_to_json.py` (expands the HRM / thumb /
combo macros into a plain QMK `keymap.json`) → `keymap parse` → `keymap draw`
(physical layout via `qmk info`, styling via `tools/keymap_drawer.config.yaml`).

Requires the [keymap-drawer](https://github.com/caksoylar/keymap-drawer) CLI
(`keymap`), the `qmk` CLI, and `python3`.

## IFKB Ergolite (if_rec firmware)

`if_rec` is the 2.4 GHz receiver/dongle — you type on the IFKB **Ergolite**, which
talks to it wirelessly. The receiver's own `LAYOUT` is a useless ~253-key
composite of three physical keyboards (ergo + corne + alice) padded with
`PAD_NOT_CONNECTED`; the real keymap is the embedded Ergolite block
(`LAYOUT_eglt`: 66 keys = 7 columns + 5 thumbs per hand).

So those 66 keys are emitted as-is and drawn against
[`../../tools/ergolite.layout.json`](../../tools/ergolite.layout.json) — a
hand-authored per-key physical layout — instead of `qmk info`. Layers drawn:
Base, Raise, Lower, Symbol, and the QWERTY Game layer; the empty Pointer layer is
skipped. To nudge key positions, edit the stagger / thumb-coordinate tables in
[`../../tools/gen_ergolite_layout.py`](../../tools/gen_ergolite_layout.py) and
re-run it (`python3 tools/gen_ergolite_layout.py tools/ergolite.layout.json`),
then `./tools/draw_keymaps.sh`.
