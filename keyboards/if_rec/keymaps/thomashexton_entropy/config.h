/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

/* This definition is intentionally distinct from the vendor/generic if_rec
 * Vial build: it describes only Thomas's Ergolite layout. */
#define VIAL_KEYBOARD_UID {0x06, 0xD8, 0x0C, 0x90, 0xDF, 0xB2, 0xD4, 0x3F}

/* The compiled keymap uses layers 0-5. Keeping the dynamic map to those six
 * layers saves 2.5 KiB of wear-levelled EEPROM compared with the board's
 * generic ten-layer setting. */
#undef DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 6

/* Keep the editable surface deliberately small. */
#define DYNAMIC_KEYMAP_MACRO_COUNT 8
#define VIAL_COMBO_ENTRIES 4
