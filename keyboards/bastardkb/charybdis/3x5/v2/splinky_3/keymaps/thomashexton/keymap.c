#include QMK_KEYBOARD_H
#include "thomashexton.h"

/* ────────────────────────────────────────────────────────────────────────── *
 *  KEYMAP HELPERS AND LAYER SETUP
 * ────────────────────────────────────────────────────────────────────────── */
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

#define THUMB_L_OUTER LT(LAYER_RAISE, KC_SPC)  // Left outer thumb → RAISE (NUM)
#define THUMB_L_INNER MO(LAYER_LOWER)          // Left thumb near center → LOWER (NAV)

#define THUMB_R_OUTER LT(LAYER_LOWER, KC_BSPC) // Right outer thumb → LOWER (NAV)
#define THUMB_R_INNER LT(LAYER_RAISE, KC_ENT)  // Right thumb near center → RAISE (NUM)

/* ────────────────────────────────────────────────────────────────────────── *
 *  COMBO TABLE
 * ────────────────────────────────────────────────────────────────────────── */
// All combo definitions are now handled in users/thomashexton/combos.h
combo_t key_combos[] = {
    ALL_COMBOS
};

/* ────────────────────────────────────────────────────────────────────────── *
 *  LAYER DEFINITIONS
 * ────────────────────────────────────────────────────────────────────────── */
#define COLEMAK_DH_LAYER                                                             \
             KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_QUOT,          \
                TH_HRM_LEFT(A, R, S, T), KC_G, KC_M, TH_HRM_RIGHT(N, E, I, O),        \
             KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH,     \
                  XXXXXXX, THUMB_L_OUTER, THUMB_L_INNER, THUMB_R_INNER, THUMB_R_OUTER

#define RAISE_LAYER                                                                        \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_7,   KC_8,   KC_9, XXXXXXX, \
                                  TH_HRM_LEFT_MODS, XXXXXXX,   KC_4,   KC_5,   KC_6, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_0,   KC_1,   KC_2,   KC_3, XXXXXXX, \
                      XXXXXXX, _______, XXXXXXX, _______, KC_BSPC

#define LOWER_LAYER                                                                           \
    XXXXXXX, KC_HOME, XXXXXXX,  KC_END, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, KC_LEFT,   KC_UP, KC_RGHT, KC_VOLD, TH_HRM_RIGHT_MODS,                              \
    XXXXXXX, KC_MPRV, KC_DOWN, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                      XXXXXXX, KC_MPLY, _______, XXXXXXX, _______

#define POINTER_LAYER                                                                          \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, XXXXXXX, RGB_SPD,  RGB_TOG, RGB_SPI, XXXXXXX, \
    XXXXXXX, XXXXXXX, DRGSCRL, XXXXXXX, XXXXXXX, XXXXXXX, RGB_RMOD, DRGSCRL, RGB_MOD, XXXXXXX, \
    TH_HRM_LEFT_MODS, XXXXXXX, DPI_RMOD, XXXXXXX, DPI_MOD, XXXXXXX,                              \
                      XXXXXXX, KC_BTN1, KC_BTN3, KC_BTN3, KC_BTN1

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT_wrapper(COLEMAK_DH_LAYER),
    [LAYER_RAISE] = LAYOUT_wrapper(RAISE_LAYER),
    [LAYER_LOWER] = LAYOUT_wrapper(LOWER_LAYER),
    [LAYER_POINTER] = LAYOUT_wrapper(POINTER_LAYER)
};
// clang-format on

/* ────────────────────────────────────────────────────────────────────────── *
 *  KEYBOARD INITIALIZATION
 * ────────────────────────────────────────────────────────────────────────── */

// Initialize keyboard
void keyboard_post_init_user(void) {
    #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_enable();
        rgb_matrix_sethsv_noeeprom(HSV_GREEN);
        rgb_matrix_set_speed_noeeprom(255);
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DIGITAL_RAIN);
    #endif
}

/* ────────────────────────────────────────────────────────────────────────── *
 *  KEYMAP CALLBACK FUNCTIONS
 * ────────────────────────────────────────────────────────────────────────── */

/**
 * Process keymap-specific keycodes
 * This is called by process_record_user in thomashexton.c
 * Currently, custom punctuation shift behavior is handled at the user level
 */
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    // Any keymap-specific code would go here
    return true; // Continue processing for all keycodes
}
