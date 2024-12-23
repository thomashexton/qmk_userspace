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
#endif // !POINTING_DEVICE_ENABLE

#define PT_TOGG TG(LAYER_POINTER)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
// #define POINTER_MOD(...) _POINTER_MOD(__VA_ARGS__)

#define ____GACS_L____(k01, k02, k03, k04) LGUI_T(KC_##k01), LALT_T(KC_##k02), LSFT_T(KC_##k03), LCTL_T(KC_##k04)
#define ____GACS_R____(k01, k02, k03, k04) RCTL_T(KC_##k01), RSFT_T(KC_##k02), RALT_T(KC_##k03), RGUI_T(KC_##k04)
#define ______________HOME_ROW_GASC_L______________ KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX
#define ______________HOME_ROW_CSAG_R______________ XXXXXXX, KC_RCTL, KC_RSFT, KC_RALT, KC_RGUI

#define THUML1 LT(LAYER_RAISE, KC_SPC)
#define THUML2 LT(LAYER_LOWER, KC_TAB)
#define THUML3 LT(LAYER_POINTER, KC_ESC)
#define THUMR1 LT(LAYER_RAISE, KC_ENT)
#define THUMR2 LT(LAYER_LOWER, KC_BSPC)
// #define THUMR3 KC_NO // LT(LAYER_FUNCTION, KC_DEL)

#define _L_PTR(KC) LT(LAYER_POINTER, KC)

/* ────────────────────────────────────────────────────────────────────────── *
 *  FIXED COMBOS
 * ────────────────────────────────────────────────────────────────────────── */
const uint16_t PROGMEM o_curly_brace_combo[] = {RCTL_T(KC_N), RSFT_T(KC_E), COMBO_END};
const uint16_t PROGMEM c_curly_brace_combo[] = {RSFT_T(KC_E), RALT_T(KC_I), COMBO_END};
const uint16_t PROGMEM o_bracket_combo[]     = {KC_M, RCTL_T(KC_N), COMBO_END};
const uint16_t PROGMEM c_bracket_combo[]     = {RALT_T(KC_I), RGUI_T(KC_O), COMBO_END};
const uint16_t PROGMEM o_paren_combo[]       = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM c_paren_combo[]       = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM o_angle_combo[]       = {KC_K, _L_PTR(KC_H), COMBO_END};
const uint16_t PROGMEM c_angle_combo[]       = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM plus_combo[]          = {KC_P, KC_L, COMBO_END};
const uint16_t PROGMEM minus_combo[]         = {LCTL_T(KC_T), RCTL_T(KC_N), COMBO_END};
const uint16_t PROGMEM equal_combo[]         = {KC_G, KC_M, COMBO_END};
const uint16_t PROGMEM under_combo[]         = {KC_D, _L_PTR(KC_H), COMBO_END};

/* ────────────────────────────────────────────────────────────────────────── *
 *  COMBO ARRAY
 * ────────────────────────────────────────────────────────────────────────── */
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
};

/* ────────────────────────────────────────────────────────────────────────── *
 *  Tell QMK how many combos we have
 * ────────────────────────────────────────────────────────────────────────── */
uint8_t COMBO_COUNT = sizeof(key_combos) / sizeof(key_combos[0]);

/* ────────────────────────────────────────────────────────────────────────── *
 *  LAYER ARRAYS
 * ────────────────────────────────────────────────────────────────────────── */
#define COLEMAK_DH_LAYER                                                                       \
                   KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_QUOT,              \
               ____GACS_L____(A, R, S, T), KC_G, KC_M, ____GACS_R____(N, E, I, O),             \
           KC_Z, KC_X, KC_C, _L_PTR(KC_D), KC_V, KC_K, _L_PTR(KC_H), KC_COMM, KC_DOT, KC_SLSH, \
                         THUML3, THUML1, THUML2, THUMR1, THUMR2

#define RAISE_LAYER                                                                           \
    _______, _______, _______, _______, _______, KC_VOLU, _______, _______, _______, _______, \
    ______________HOME_ROW_GASC_L______________, KC_VOLD, KC_LEFT, KC_UP,   KC_RGHT, _______, \
    _______, _______, _______, _______, _______, _______, _______, KC_DOWN, _______, _______, \
                      _______, _______, _______, _______, _______

#define LOWER_LAYER                                                                           \
    XXXXXXX,    KC_7,   KC_8,   KC_9,   XXXXXXX, _______, _______, _______, _______, _______, \
    XXXXXXX,    KC_4,   KC_5,   KC_6,   XXXXXXX, ______________HOME_ROW_CSAG_R______________, \
    XXXXXXX,    KC_1,   KC_2,   KC_3,   XXXXXXX, _______, _______, _______, _______, _______, \
                        KC_0,   KC_SPC, _______, _______, _______

#define POINTER_LAYER                                                                         \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, DRGSCRL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DRGSCRL, XXXXXXX, _______, \
                      KC_BTN2, KC_BTN1, KC_BTN3, KC_BTN3, KC_BTN1

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT_wrapper(COLEMAK_DH_LAYER),
    [LAYER_RAISE] = LAYOUT_wrapper(RAISE_LAYER),
    [LAYER_LOWER] = LAYOUT_wrapper(LOWER_LAYER),
    [LAYER_POINTER] = LAYOUT_wrapper(POINTER_LAYER)
};
// clang-format on

enum custom_keycodes {
    DRAG_SCROLL = SAFE_RANGE,
};

bool set_scrolling = false;

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 25.0
#define SCROLL_DIVISOR_V 25.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

#ifdef POINTING_DEVICE_ENABLE
    report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
        #ifdef MACCEL_ENABLE
            mouse_report = pointing_device_task_maccel(mouse_report);
        #endif // MACCEL_ENABLE

        if (set_scrolling) {
            // Calculate and accumulate scroll values based on mouse movement and divisors
            scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
            scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

            // Assign integer parts of accumulated scroll values to the mouse report
            mouse_report.h = (int8_t)scroll_accumulated_h;
            mouse_report.v = (int8_t)scroll_accumulated_v;

            // Update accumulated scroll values by subtracting the integer parts
            scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
            scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

            // Clear the X and Y values of the mouse report
            mouse_report.x = 0;
            mouse_report.y = 0;
        }

        return mouse_report;
    }
#endif // POINTING_DEVICE_ENABLE
