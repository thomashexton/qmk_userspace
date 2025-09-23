#include QMK_KEYBOARD_H
#include "thomashexton.h"

/* ────────────────────────────────────────────────────────────────────────── *
 *  KEYMAP HELPERS AND LAYER SETUP
 * ────────────────────────────────────────────────────────────────────────── */
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

// Bottom row mods - GACS order (GUI, ALT, SHIFT, CTRL)
// Now on bottom row: Z, X, C, D on left; H, comma, dot, slash on right
#define ____GASC_L____(k01, k02, k03, k04) LGUI_T(KC_##k01), LALT_T(KC_##k02), LSFT_T(KC_##k03), LCTL_T(KC_##k04)
#define ____CSAG_R____(k01, k02, k03, k04) RCTL_T(KC_##k01), RSFT_T(KC_##k02), RALT_T(KC_##k03), RGUI_T(KC_##k04)

// Bottom row mods as full keycode definitions - used in combination with other keys/layers
#define __________________GASC_L___________________ KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX
#define ___________________CSAG_R__________________ XXXXXXX, KC_RCTL, KC_RSFT, KC_RALT, KC_RGUI

#define THUML1 LT(LAYER_RAISE, KC_SPC)  // Left cluster, left button → RAISE (NUM)
#define THUML2 MO(LAYER_LOWER)          // Left cluster, right button → LOWER (NAV)

#define THUMR1 LT(LAYER_LOWER, KC_BSPC) // Right cluster, right button → LOWER (NAV)
#define THUMR2 LT(LAYER_RAISE, KC_ENT)  // Right cluster, left button → RAISE (NUM)

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
         KC_A, KC_R, KC_S, T_KEY, KC_G, KC_M, N_KEY, KC_E, KC_I, KC_O,               \
         ____GASC_L____(Z, X, C, D), KC_V, KC_K, ____CSAG_R____(H, COMM, DOT, SLSH), \
                  XXXXXXX, THUML1, THUML2, THUMR2, THUMR1

#define RAISE_LAYER                                                                        \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_7,   KC_8,   KC_9, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_4,   KC_5,   KC_6, XXXXXXX, \
    __________________GASC_L___________________,    KC_0,   KC_1,   KC_2,   KC_3, XXXXXXX, \
                      XXXXXXX, _______, XXXXXXX, _______, KC_BSPC

#define LOWER_LAYER                                                                           \
    XXXXXXX, KC_HOME, XXXXXXX,  KC_END, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, KC_LEFT,   KC_UP, KC_RGHT, KC_VOLD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, KC_MPRV, KC_DOWN, KC_MNXT, XXXXXXX, ___________________CSAG_R__________________, \
                      XXXXXXX, KC_MPLY, _______, XXXXXXX, _______

#define POINTER_LAYER                                                                          \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, XXXXXXX, RGB_SPD,  RGB_TOG, RGB_SPI, XXXXXXX, \
    XXXXXXX, XXXXXXX, DRGSCRL, XXXXXXX, XXXXXXX, XXXXXXX, RGB_RMOD, DRGSCRL, RGB_MOD, XXXXXXX, \
    __________________GASC_L___________________, XXXXXXX, DPI_RMOD, XXXXXXX, DPI_MOD, XXXXXXX, \
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
