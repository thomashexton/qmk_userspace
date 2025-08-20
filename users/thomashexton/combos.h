#pragma once

#include QMK_KEYBOARD_H

/* ────────────────────────────────────────────────────────────────────────── *
 *  Colemak-DH 3X5 COMBO DEFINITIONS
 * ────────────────────────────────────────────────────────────────────────── */
// Top row combos
    static const uint16_t PROGMEM bootloader_combo[]    = {KC_Q, KC_QUOT, COMBO_END};

// Middle row combos
    static const uint16_t PROGMEM escape_combo[]        = {KC_R, KC_S, COMBO_END};

    // Bracket pairs
    static const uint16_t PROGMEM o_curly_brace_combo[] = {KC_N, KC_E, COMBO_END};
    static const uint16_t PROGMEM c_curly_brace_combo[] = {KC_E, KC_I, COMBO_END};
    static const uint16_t PROGMEM o_bracket_combo[]     = {KC_M, KC_N, COMBO_END};
    static const uint16_t PROGMEM c_bracket_combo[]     = {KC_I, KC_O, COMBO_END};

    // Navigation
    static const uint16_t PROGMEM tab_combo[]           = {KC_I, KC_O, COMBO_END};

// Bottom row combose
    static const uint16_t PROGMEM o_paren_combo[]       = {RCTL_T(KC_H), RSFT_T(KC_COMM), COMBO_END};
    static const uint16_t PROGMEM c_paren_combo[]       = {RSFT_T(KC_COMM), RALT_T(KC_DOT), COMBO_END};
    static const uint16_t PROGMEM o_angle_combo[]       = {KC_K, RCTL_T(KC_H), COMBO_END};
    static const uint16_t PROGMEM c_angle_combo[]       = {RALT_T(KC_DOT), RGUI_T(KC_SLSH), COMBO_END};

    // Punctuation and symbols
    static const uint16_t PROGMEM plus_combo[]          = {KC_P, KC_L, COMBO_END};
    static const uint16_t PROGMEM minus_combo[]         = {T_KEY, N_KEY, COMBO_END};
    static const uint16_t PROGMEM equal_combo[]         = {KC_G, KC_M, COMBO_END};
    static const uint16_t PROGMEM under_combo[]         = {LCTL_T(KC_D), RCTL_T(KC_H), COMBO_END};
    static const uint16_t PROGMEM grave_combo[]         = {KC_Q, KC_W, COMBO_END};
    static const uint16_t PROGMEM tilde_combo[]         = {LGUI_T(KC_Z), LALT_T(KC_X), COMBO_END};

// Mouse button combos
static const uint16_t PROGMEM right_click_combo[]       = {KC_BTN1, KC_BTN3, COMBO_END};

/* ────────────────────────────────────────────────────────────────────────── *
 *  SIMPLE COMBO TABLE MACRO
 * ────────────────────────────────────────────────────────────────────────── */
// This creates the complete combo table - much cleaner than the old system
#define ALL_COMBOS \
    COMBO(bootloader_combo, QK_BOOT), \
    COMBO(escape_combo, KC_ESC), \
    COMBO(o_curly_brace_combo, KC_LEFT_CURLY_BRACE), \
    COMBO(c_curly_brace_combo, KC_RIGHT_CURLY_BRACE), \
    COMBO(o_bracket_combo, KC_LEFT_BRACKET), \
    COMBO(c_bracket_combo, KC_RIGHT_BRACKET), \
    COMBO(tab_combo, KC_TAB), \
    COMBO(plus_combo, KC_PLUS), \
    COMBO(minus_combo, KC_MINUS), \
    COMBO(equal_combo, KC_EQUAL), \
    COMBO(o_paren_combo, KC_LEFT_PAREN), \
    COMBO(c_paren_combo, KC_RIGHT_PAREN), \
    COMBO(o_angle_combo, KC_LEFT_ANGLE_BRACKET), \
    COMBO(c_angle_combo, KC_RIGHT_ANGLE_BRACKET), \
    COMBO(under_combo, KC_UNDERSCORE), \
    COMBO(grave_combo, KC_GRAVE), \
    COMBO(tilde_combo, S(KC_GRAVE)), \
    COMBO(right_click_combo, KC_BTN2)
