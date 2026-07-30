# Ergolite Entropy experiment

This is a deliberately small Vial companion to the plain `thomashexton`
keymap. It keeps the plain build available as a known-good fallback.

## Editable in Entropy

- Six layers (0-5)
- Eight macros
- Four combo slots

The first three combo slots can recreate the useful Ergolite defaults:

1. `Q` + `Quote` -> `Bootloader`
2. `W` + `F` -> `Escape`
3. `U` + `Y` -> `Tab`

The shared `Button 1` + `Button 3` mouse combo is not an Ergolite feature, so
the fourth slot is left spare.

Fresh Vial EEPROM starts with all combo slots empty. There is also a compiled
bootloader escape hatch: hold both layer thumbs to enter the Symbol layer, then
press the top-left physical key.

## Still compiled in firmware

- Colemak-DH defaults and the QWERTY game layer
- Chordal Hold, Flow Tap, per-key tapping terms, and per-key hold behaviour
- Home-row mods, custom punctuation, Caps Word, and the Symbol tri-layer
- The receiver's custom UART matrix implementation

## Intentionally omitted

- QMK Settings runtime overrides
- Tap Dance
- Key Overrides
- MIDI
- Mouse Keys
- Lighting

## Build

From the `vial-qmk` checkout:

```sh
make if_rec:thomashexton_entropy \
  QMK_USERSPACE=/Users/thomashexton/qmk/qmk_userspace
```

The UF2 is copied to:

```text
/Users/thomashexton/qmk/qmk_userspace/firmware/if_rec_thomashexton_entropy.uf2
```
