#include QMK_KEYBOARD_H
#include "thomashexton.h"

/* ────────────────────────────────────────────────────────────────────────── *
 *  KEYMAP HELPERS AND LAYER SETUP
 * ────────────────────────────────────────────────────────────────────────── */
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

// On the oldman the INNER thumb keys sit physically under the thumbs, so the
// layer-taps live there (unlike the charybdis, where they're on the outer keys).
// The less-reachable OUTER thumbs carry the shift trial.
#define THUMB_L_INNER LT(LAYER_LOWER, KC_SPC)  // Left inner (under thumb) → LOWER (numbers) on hold, Space on tap
#define THUMB_L_OUTER LSFT_T(KC_TAB)           // Left outer → Shift on hold, Tab on tap

#define THUMB_R_INNER LT(LAYER_RAISE, KC_BSPC) // Right inner (under thumb) → RAISE (nav) on hold, Backspace on tap
#define THUMB_R_OUTER RSFT_T(KC_ENT)           // Right outer → Shift on hold, Enter on tap

/* ────────────────────────────────────────────────────────────────────────── *
 *  COMBO TABLE
 * ────────────────────────────────────────────────────────────────────────── */
// All combo definitions are now handled in users/thomashexton/combos.h.
combo_t key_combos[] = {
    ALL_COMBOS
};

/* ────────────────────────────────────────────────────────────────────────── *
 *  LAYER DEFINITIONS
 * ────────────────────────────────────────────────────────────────────────── */
#define BASE_LAYER                                                                               \
                      KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_QUOT,             \
                           TH_HRM_LEFT(A, R, S, T), KC_G, KC_M, TH_HRM_RIGHT(N, E, I, O),        \
                      KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH,        \
             _______, THUMB_L_OUTER, THUMB_L_INNER, THUMB_R_INNER, THUMB_R_OUTER, _______

// Oldman keeps its own (reversed-vs-charybdis) layer arrangement on purpose:
// LOWER = numbers (left inner thumb), RAISE = nav (right inner thumb).
#define LOWER_LAYER                                                                              \
    XXXXXXX, G(S(KC_LBRC)), XXXXXXX, G(S(KC_RBRC)), XXXXXXX, XXXXXXX, KC_7, KC_8, KC_9, XXXXXXX, \
                                  TH_HRM_LEFT_MODS, XXXXXXX, KC_4, KC_5, KC_6, KC_0,             \
 XXXXXXX, G(KC_LBRC), XXXXXXX, G(KC_RBRC), XXXXXXX, KC_0,    KC_1, KC_2, KC_3, XXXXXXX,          \
       XXXXXXX,                   _______, _______, _______, _______,          XXXXXXX

#define RAISE_LAYER                                                                              \
       XXXXXXX, KC_HOME,   KC_UP,  KC_END, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
       XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, TH_HRM_RIGHT_MODS,                           \
       XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
       XXXXXXX,                   _______, _______, _______, _______,                   XXXXXXX

#define SYMBOL_LAYER                                                                             \
       KC_GRV,  KC_BSLS, KC_MINS, KC_UNDS, XXXXXXX, XXXXXXX, KC_EQL,  KC_PLUS, KC_SLSH, KC_PIPE, \
                                  TH_HRM_LEFT_MODS, TH_HRM_RIGHT_MODS,                           \
       KC_LABK, KC_LBRC, KC_LCBR, KC_LPRN, XXXXXXX, XXXXXXX, KC_RPRN, KC_RCBR, KC_RBRC, KC_RABK, \
       XXXXXXX,                   _______, _______, _______, _______,                   XXXXXXX

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT_wrapper(BASE_LAYER),
    [LAYER_LOWER] = LAYOUT_wrapper(LOWER_LAYER),
    [LAYER_RAISE] = LAYOUT_wrapper(RAISE_LAYER),
    [LAYER_SYMBOL] = LAYOUT_wrapper(SYMBOL_LAYER)
};
// clang-format on

/* ────────────────────────────────────────────────────────────────────────── *
 *  CHORDAL HOLD HANDEDNESS
 *  Per-key hand for CHORDAL_HOLD (see users/thomashexton/config.h). Oldman is a
 *  4x10 unibody, so left/right is by column. 'L'/'R' mark the physical hand;
 *  thumbs are '*' so their layer-taps always hold.
 * ────────────────────────────────────────────────────────────────────────── */
#ifdef CHORDAL_HOLD
// clang-format off
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT_wrapper(
    'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R',
    '*',           '*', '*',   '*', '*',           '*'
);
// clang-format on
#endif

/* ────────────────────────────────────────────────────────────────────────── *
 *  KEYBOARD INITIALIZATION
 * ────────────────────────────────────────────────────────────────────────── */

#ifdef RGBLIGHT_ENABLE
static void set_layer_color(layer_state_t state) {
    const bool symbol_active  = state & (1UL << LAYER_SYMBOL);
    const bool pointer_active = state & (1UL << LAYER_POINTER);

    if (symbol_active) {
        rgblight_setrgb(80, 80, 80);   // White for the symbol layer
    } else if (pointer_active) {
        rgblight_setrgb(80, 0, 80);    // Purple for pointer/cursor mode
    } else {
        switch (get_highest_layer(state)) {
            case LAYER_LOWER:
                rgblight_setrgb(80, 0, 0);  // Red
                break;
            case LAYER_RAISE:
                rgblight_setrgb(0, 0, 80);  // Blue
                break;
            default:
                rgblight_setrgb(0, 80, 0);  // Green on the base layer
                break;
        }
    }
}
#endif

void keyboard_post_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
        set_layer_color(layer_state);
    #endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, LAYER_LOWER, LAYER_RAISE, LAYER_SYMBOL);

    #ifdef RGBLIGHT_ENABLE
        set_layer_color(state);
    #endif

    return state;
}

/**
 * Process keymap-specific keycodes
 * This is called by process_record_user in thomashexton.c
 * Currently, all custom keycodes are handled in the user file.
 */
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true; // Continue processing for all keycodes
}
