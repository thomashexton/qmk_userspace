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
| if_rec (IFKB Ergolite, 2.4 GHz receiver) | [if_rec.svg](if_rec.svg) |

## Regenerating

```sh
./tools/draw_keymaps.sh
```

Pipeline: `keymap.c` → `tools/keymap_to_json.py` (expands the HRM / thumb /
combo macros into a plain QMK `keymap.json`) → `keymap parse` → `keymap draw`
(physical layout via `qmk info`, styling via `tools/keymap_drawer.config.yaml`).

Requires the [keymap-drawer](https://github.com/caksoylar/keymap-drawer) CLI
(`keymap`), the `qmk` CLI, and `python3`.

## if_rec (Ergolite via 2.4 GHz receiver)

`if_rec` is a 2.4 GHz receiver/dongle whose `LAYOUT` is a ~253-key composite of
three physical keyboards (ergo + corne + alice) padded with
`PAD_NOT_CONNECTED`. The real keymap is only the embedded Ergolite block (4 rows
× 14 + a 10-key thumb row per layer, wrapped by `LAYOUT_eglt`), so the composite
`info.json` would draw a useless sea of empty keys.

Instead, `keymap_to_json.py --eglt` reduces each layer to the 49 real Ergolite
keys (drops the inter-half pad columns: indices 0/6/7/13 of each main row and
index 8 of the thumb row), and the diagram is rendered against a **synthetic**
`cols+thumbs` layout (`44444+5 4+44444` — 5 columns × 4 rows per hand, 5 left /
4 right thumbs) rather than `qmk info`. Layers drawn: Base, Raise, Lower, Symbol,
and the QWERTY Game layer (which reduces cleanly); the empty Pointer layer is
skipped.
