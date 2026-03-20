#pragma once

/* ────────────────────────────────────────────────────────────────────────── *
 *  LAYER DEFINITIONS
 * ────────────────────────────────────────────────────────────────────────── */
// clang-format off
enum user_layers {
    LAYER_BASE = 0,
    LAYER_RAISE,
    LAYER_LOWER,
    LAYER_POINTER,
    LAYER_SYMBOL
};
// clang-format on

/* ────────────────────────────────────────────────────────────────────────── *
 *  SHARED LETTER DEFINITIONS
 * ────────────────────────────────────────────────────────────────────────── */
// T and N are plain letters again across both boards.
// combos.h still references these names, so keep the aliases in one place.
#define T_KEY KC_T
#define N_KEY KC_N

// Include the combos configuration and definitions
// MUST be included AFTER T_KEY and N_KEY are defined since combos.h uses them
#include "combos.h"

/* ────────────────────────────────────────────────────────────────────────── *
 *  CUSTOM KEYCODES
 * ────────────────────────────────────────────────────────────────────────── */
// Currently no custom keycodes needed at the user level
// Keymap-specific custom keycodes should start at SAFE_RANGE

// Function declarations for user and keymap callbacks
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
bool process_record_user(uint16_t keycode, keyrecord_t *record);
