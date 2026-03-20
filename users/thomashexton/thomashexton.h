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

// Shared home row mod order across all boards in this userspace.
#include "home_row_mods.h"

// Shared combo definitions across all boards in this userspace.
#include "combos.h"

/* ────────────────────────────────────────────────────────────────────────── *
 *  CUSTOM KEYCODES
 * ────────────────────────────────────────────────────────────────────────── */
// Currently no custom keycodes needed at the user level
// Keymap-specific custom keycodes should start at SAFE_RANGE

// Function declarations for user and keymap callbacks
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
bool process_record_user(uint16_t keycode, keyrecord_t *record);
