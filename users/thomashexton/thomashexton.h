#pragma once

#ifdef MACCEL_ENABLE
#    include "features/maccel/maccel.h"
#endif

/* ────────────────────────────────────────────────────────────────────────── *
 *  LAYER DEFINITIONS
 * ────────────────────────────────────────────────────────────────────────── */
// clang-format off
enum user_layers {
    LAYER_BASE = 0,
    LAYER_RAISE,
    LAYER_LOWER,
    LAYER_POINTER
};
// clang-format on

/* ────────────────────────────────────────────────────────────────────────── *
 *  KEYBOARD-SPECIFIC KEY DEFINITIONS
 * ────────────────────────────────────────────────────────────────────────── */
// Define what the T and N keys actually are on each keyboard
// This allows combos.h to work across both keyboards with different layer behaviors
#ifdef KEYBOARD_bastardkb_charybdis_3x5_v2_splinky_3
    // Charybdis has a trackball, so T and N activate the pointer layer when held
    #define T_KEY LT(LAYER_POINTER, KC_T)
    #define N_KEY LT(LAYER_POINTER, KC_N)
#elif defined(KEYBOARD_oldman_endgame)
    // Endgame doesn't have a trackball, so T and N are just regular keys
    #define T_KEY KC_T
    #define N_KEY KC_N
#else
    // Fallback for any other keyboards
    #define T_KEY KC_T
    #define N_KEY KC_N
#endif

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
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report);
