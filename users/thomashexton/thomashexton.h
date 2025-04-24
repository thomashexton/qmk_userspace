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
 *  POINTER DEVICE SETTINGS
 * ────────────────────────────────────────────────────────────────────────── */
// Custom keycodes for all functionality
enum user_keycodes {
    COMMA_KEY = SAFE_RANGE, // Custom keycode for comma to handle shift manually
    DOT_KEY                 // Custom keycode for dot to handle shift manually
};

// Function declarations for user and keymap callbacks
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
bool process_record_user(uint16_t keycode, keyrecord_t *record);
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report);
