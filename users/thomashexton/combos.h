#pragma once

#include QMK_KEYBOARD_H

/* ────────────────────────────────────────────────────────────────────────── *
 *  Colemak-DH 3X5 COMBO DEFINITIONS
 * ────────────────────────────────────────────────────────────────────────── */
// Top row combos
    static const uint16_t PROGMEM bootloader_combo[]    = {KC_Q, KC_QUOT, COMBO_END};

// Middle row combos
    static const uint16_t PROGMEM escape_combo[]        = {KC_W, KC_F, COMBO_END};
    static const uint16_t PROGMEM tab_combo[]           = {KC_U, KC_Y, COMBO_END};

// Mouse button combos
    static const uint16_t PROGMEM right_click_combo[]   = {KC_BTN1, KC_BTN3, COMBO_END};

/* ────────────────────────────────────────────────────────────────────────── *
 *  SIMPLE COMBO TABLE MACRO
 * ────────────────────────────────────────────────────────────────────────── */
#define ALL_COMBOS \
    COMBO(bootloader_combo, QK_BOOT), \
    COMBO(escape_combo, KC_ESC), \
    COMBO(tab_combo, KC_TAB), \
    COMBO(right_click_combo, KC_BTN2)
