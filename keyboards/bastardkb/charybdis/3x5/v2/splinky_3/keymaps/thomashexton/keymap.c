#include QMK_KEYBOARD_H
#include "thomashexton.h"

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;
#   include "timer.h"
#   ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#       define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#   endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#   ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#       define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#   endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL XXXXXXX
#    define DPI_MOD XXXXXXX
#    define S_D_MOD XXXXXXX
#    define SNIPING XXXXXXX
#endif // !POINTING_DEVICE_ENABLE

#define LAYER_COLEMAK_DH LAYER_BASE

#define PT_TOGG TG(LAYER_POINTER)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
// #define POINTER_MOD(...) _POINTER_MOD(__VA_ARGS__)

#define ___GACS_L___(k01, k02, k03, k04) LGUI_T(KC_##k01), LALT_T(KC_##k02), LSFT_T(KC_##k03), LCTL_T(KC_##k04)
#define ___GACS_R___(k01, k02, k03, k04) RCTL_T(KC_##k01), RSFT_T(KC_##k02), LALT_T(KC_##k03), RGUI_T(KC_##k04)
#define ______________HOME_ROW_GASC_L______________ KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX
#define ______________HOME_ROW_CSAG_R______________ XXXXXXX, KC_RCTL, KC_RSFT, KC_RALT, KC_RGUI

#define THUML1 LT(LAYER_RAISE, KC_SPC)
#define THUML2 LT(LAYER_LOWER, KC_TAB)
#define THUML3 LT(LAYER_POINTER, KC_ESC)
#define THUMR1 LT(LAYER_RAISE, KC_BSPC)
#define THUMR2 LT(LAYER_LOWER, KC_ENT)
// #define THUMR3 KC_NO // LT(LAYER_FUNCTION, KC_DEL)

// #define _L_PTR(KC) LT(LAYER_POINTER, KC)

const uint16_t PROGMEM o_paren_combo[] = {KC_N, KC_E, COMBO_END};
const uint16_t PROGMEM c_paren_combo[] = {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM plus_combo[] = {KC_P, KC_L, COMBO_END};
const uint16_t PROGMEM minus_combo[] = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM under_combo[] = {KC_D, KC_H, COMBO_END};
combo_t key_combos[] = {
    COMBO(o_paren_combo, KC_LEFT_PAREN),
    COMBO(c_paren_combo, KC_RIGHT_PAREN),
    COMBO(plus_combo, KC_PLUS),
    COMBO(minus_combo, KC_MINUS),
    COMBO(under_combo, KC_UNDERSCORE)
};

#define COLEMAK_DH_LAYER                                                \
    KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_QUOT,      \
    ___GACS_L___(A, R, S, T), KC_G, KC_M, ___GACS_R___(N, E, I, O),     \
    KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, \
                 THUML3, THUML1, THUML2, THUMR2, THUMR1

#define RAISE_LAYER                                                                           \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    ______________HOME_ROW_GASC_L______________, _______, KC_LEFT, KC_UP,   KC_RGHT, _______, \
    _______, _______, _______, _______, _______, _______, _______, KC_DOWN, _______, _______, \
                      _______, _______, _______, _______, _______

#define LOWER_LAYER                                                                            \
    XXXXXXX,    KC_7,    KC_8,   KC_9,   XXXXXXX, _______, _______, _______, _______, _______, \
    XXXXXXX,    KC_4,    KC_5,   KC_6,   XXXXXXX, ______________HOME_ROW_CSAG_R______________, \
    XXXXXXX,    KC_1,    KC_2,   KC_3,   XXXXXXX, _______, _______, _______, _______, _______, \
                         KC_0,   KC_SPC, _______, _______, _______

#define POINTER_LAYER                                                                         \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, DRGSCRL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, KC_BTN2, KC_BTN3, KC_BTN1, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN3, KC_BTN2, XXXXXXX, \
                      _______, KC_BTN1, KC_BTN3, XXXXXXX, XXXXXXX

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_COLEMAK_DH] = LAYOUT_wrapper(COLEMAK_DH_LAYER),
    [LAYER_RAISE] = LAYOUT_wrapper(RAISE_LAYER),
    [LAYER_LOWER] = LAYOUT_wrapper(LOWER_LAYER),
    [LAYER_POINTER] = LAYOUT_wrapper(POINTER_LAYER)
};
// clang-format on

/* #define LAYER_FUN                                                                 \
 * _______, _______, _______, _______, _______, XXXXXXX,   KC_F7,   KC_F8,   KC_F9,  KC_F12, \
 * ______________HOME_ROW_GASC_L______________, XXXXXXX,   KC_F4,   KC_F5,   KC_F6,  KC_F11, \
 * _______, _______, _______, _______, _______, XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F10, \
 *                   XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX
 */

/* #define LAYER_MEDIA                                                                  \
 *     _______, _______, _______, _______, _______, KC_VOLU, XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, \
 *     _______, _______, _______, _______, _______, KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, \
 *     XXXXXXX, KC_BTN2, KC_BTN3, KC_BTN1, XXXXXXX,     KC_MUTE, KC_BTN1, KC_BTN3, KC_BTN2, XXXXXXX, \
 *     _______, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX
 */

/* #define LAYER_NAV                                                             \
 *     _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
 *     ______________HOME_ROW_GASC_L______________, KC_CAPS, KC_LEFT, KC_UP,   KC_RGHT, XXXXXXX, \
 *     _______, _______, _______, _______, _______, KC_INS, XXXXXXX,  KC_DOWN, XXXXXXX, KC_END, \
 *                       XXXXXXX, _______, XXXXXXX, KC_ENT, KC_BSPC
 */

/* #define LAYER_NUM                                                                  \
 *     KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC, _______, _______, _______, _______, _______, \
 *     KC_SCLN,    KC_4,    KC_5,    KC_6,  KC_EQL, ______________HOME_ROW_CSAG_R______________, \
 *      KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS, _______, _______, _______, _______, _______, \
 *                        KC_DOT,    KC_0, KC_MINS, XXXXXXX, _______
 */

/* #define LAYER_SYM                                                                  \
 *     XXXXXXX, KC_AMPR, KC_ASTR, KC_LPRN, XXXXXXX, _______, _______, _______, _______, _______, \
 *     KC_COLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, ___GACS_R___(  LPRN, RPRN, LCBR, RCBR), \
 *     KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE, _______, _______, _______, _______, _______, \
 *                       KC_LPRN, KC_RPRN, KC_UNDS, _______, XXXXXXX
 */

/*
 * Expects a 10-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.
 *   POINTER_MOD(LAYER_ALPHAS_QWERTY)
 */
/* #define _POINTER_MOD(                                                 \
 *   L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
 *   L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
 *   L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
 *   ...)                                                               \
 *            L00,         L01,         L02,         L03,         L04,  \
 *            R05,         R06,         R07,         R08,         R09,  \
 *            L10,         L11,         L12,         L13,         L14,  \
 *             R15,         R16,         R17,         R18,         R19, \
 *     _L_PTR(L20),        L21,         L22,         L23,         L24,  \
 *            R25,         R26,         R27,         R28,  _L_PTR(R29), \
 *     __VA_ARGS__
 */


#ifdef POINTING_DEVICE_ENABLE
    report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
        #ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
            if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD ||
                abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {

                if (auto_pointer_layer_timer == 0) {
                    layer_on(LAYER_POINTER);

                    #ifdef RGB_MATRIX_ENABLE
                        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
                        rgb_matrix_sethsv_noeeprom(HSV_GREEN);
                    #endif // RGB_MATRIX_ENABLE
                }

                auto_pointer_layer_timer = timer_read();
            }
        #endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

        #ifdef MACCEL_ENABLE
            mouse_report = pointing_device_task_maccel(mouse_report);
        #endif // MACCEL_ENABLE

        return mouse_report;
    }
#endif // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
    // Forward-declare this helper function since it is defined in rgb_matrix.c.
    void rgb_matrix_update_pwm_buffers(void);
#endif // RGB_MATRIX_ENABLE
