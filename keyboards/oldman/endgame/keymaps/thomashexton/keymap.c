#include QMK_KEYBOARD_H
#include "thomashexton.h"

/* ────────────────────────────────────────────────────────────────────────── *
 *  KEYMAP HELPERS AND LAYER SETUP
 * ────────────────────────────────────────────────────────────────────────── */
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

// Home row mods - GACS order (GUI, ALT, SHIFT, CTRL)
#define ____GASC_L____(k01, k02, k03, k04) LGUI_T(KC_##k01), LALT_T(KC_##k02), LSFT_T(KC_##k03), LCTL_T(KC_##k04)
#define ____CSAG_R____(k01, k02, k03, k04) RCTL_T(KC_##k01), RSFT_T(KC_##k02), RALT_T(KC_##k03), RGUI_T(KC_##k04)

// Home row mods as full keycode definitions - used in combination with other keys
#define ______________HOME_ROW_GASC_L______________ KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX
#define ______________HOME_ROW_CSAG_R______________ XXXXXXX, KC_RCTL, KC_RSFT, KC_RALT, KC_RGUI

// Thumb key definitions
#define THUML1 LT(LAYER_LOWER, KC_SPC)
#define THUML2 LT(LAYER_RAISE, KC_ESC)

#define THUMR1 LT(LAYER_LOWER, KC_BSPC)
#define THUMR2 LT(LAYER_RAISE, KC_ENT)

/* ────────────────────────────────────────────────────────────────────────── *
 *  COMBO DEFINITIONS
 * ────────────────────────────────────────────────────────────────────────── */
const uint16_t PROGMEM o_curly_brace_combo[] = {RCTL_T(KC_N), RSFT_T(KC_E), COMBO_END};
const uint16_t PROGMEM c_curly_brace_combo[] = {RSFT_T(KC_E), RALT_T(KC_I), COMBO_END};
const uint16_t PROGMEM o_bracket_combo[]     = {KC_M, RCTL_T(KC_N), COMBO_END};
const uint16_t PROGMEM c_bracket_combo[]     = {RALT_T(KC_I), RGUI_T(KC_O), COMBO_END};
const uint16_t PROGMEM o_paren_combo[]       = {KC_H, COMMA_KEY, COMBO_END};
const uint16_t PROGMEM c_paren_combo[]       = {COMMA_KEY, DOT_KEY, COMBO_END};
const uint16_t PROGMEM o_angle_combo[]       = {KC_K, KC_H, COMBO_END};
const uint16_t PROGMEM c_angle_combo[]       = {DOT_KEY, KC_SLSH, COMBO_END};
const uint16_t PROGMEM plus_combo[]          = {KC_P, KC_L, COMBO_END};
const uint16_t PROGMEM minus_combo[]         = {LCTL_T(KC_T), RCTL_T(KC_N), COMBO_END};
const uint16_t PROGMEM equal_combo[]         = {KC_G, KC_M, COMBO_END};
const uint16_t PROGMEM under_combo[]         = {KC_D, KC_H, COMBO_END};
const uint16_t PROGMEM grave_combo[]         = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM tilde_combo[]         = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM bootloader_combo[]    = {KC_Q, KC_SCLN, COMBO_END};

combo_t key_combos[] = {
    COMBO(o_curly_brace_combo, KC_LEFT_CURLY_BRACE),
    COMBO(c_curly_brace_combo, KC_RIGHT_CURLY_BRACE),
    COMBO(o_bracket_combo, KC_LEFT_BRACKET),
    COMBO(c_bracket_combo, KC_RIGHT_BRACKET),
    COMBO(o_paren_combo, KC_LEFT_PAREN),
    COMBO(c_paren_combo, KC_RIGHT_PAREN),
    COMBO(o_angle_combo, KC_LEFT_ANGLE_BRACKET),
    COMBO(c_angle_combo, KC_RIGHT_ANGLE_BRACKET),
    COMBO(plus_combo, KC_PLUS),
    COMBO(minus_combo, KC_MINUS),
    COMBO(equal_combo, KC_EQUAL),
    COMBO(under_combo, KC_UNDERSCORE),
    COMBO(grave_combo, KC_GRAVE),
    COMBO(tilde_combo, S(KC_GRAVE)),
    COMBO(bootloader_combo, QK_BOOT),
};

/* ────────────────────────────────────────────────────────────────────────── *
 *  LAYER DEFINITIONS
 * ────────────────────────────────────────────────────────────────────────── */
#define COLEMAK_DH_LAYER                                                                  \
                   KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_QUOT,         \
               ____GASC_L____(A, R, S, T), KC_G, KC_M, ____CSAG_R____(N, E, I, O),        \
                   KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, COMMA_KEY, DOT_KEY, KC_SLSH, \
                         _______, THUML2, THUML1, THUMR1, THUMR2, _______

#define RAISE_LAYER                                                                           \
    XXXXXXX,    KC_7,   KC_8,    KC_9,  XXXXXXX, _______, _______, _______, _______, _______, \
    XXXXXXX,    KC_4,   KC_5,    KC_6,  XXXXXXX, ______________HOME_ROW_CSAG_R______________, \
    XXXXXXX,    KC_1,   KC_2,    KC_3,  XXXXXXX, _______, _______, _______, _______, _______, \
    XXXXXXX,                     KC_0,   KC_SPC, _______, _______,                   _______

#define LOWER_LAYER                                                                           \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, \
    ______________HOME_ROW_GASC_L______________, KC_VOLD, KC_LEFT, KC_UP,   KC_RGHT, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DOWN, XXXXXXX, XXXXXXX, \
    _______,                   _______, _______, _______, _______,                   _______

#define ADJ_LAYER                                                                             \
    _______, _______, _______, _______, QK_BOOT, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______,                   _______, _______, _______, _______,                   _______

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT_wrapper(COLEMAK_DH_LAYER),
    [LAYER_RAISE] = LAYOUT_wrapper(RAISE_LAYER),
    [LAYER_LOWER] = LAYOUT_wrapper(LOWER_LAYER),
    [LAYER_POINTER] = LAYOUT_wrapper(ADJ_LAYER)
};
// clang-format on

/* ────────────────────────────────────────────────────────────────────────── *
 *  KEYBOARD INITIALIZATION
 * ────────────────────────────────────────────────────────────────────────── */

// Initialize keyboard
void keyboard_post_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
        rgblight_setrgb_range(25, 0, 50, 0, 1);  // Purple
    #endif
}

/**
 * Process keymap-specific keycodes
 * This is called by process_record_user in thomashexton.c
 * Currently, all custom keycodes are handled in the user file.
 */
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    // Any keymap-specific code would go here
    return true; // Continue processing for all keycodes
}
