/* IFKB Ergolite (via if_rec 2.4G receiver) — Thomas's userspace keymap.
 *
 * Conventions follow keyboards/bastardkb/charybdis: Colemak-DH base with
 * TH_HRM home-row mods, RAISE (numbers) / LOWER (nav) with SYMBOL tri-layer,
 * plus LAYER_GAME (QWERTY gaming layer) toggled by TO().
 *
 * The receiver firmware's LAYOUT covers four IFKB boards; only the Ergolite
 * (eglt block) is connected, so the rest is padded with XXXXXXX.
 */
#include QMK_KEYBOARD_H
#include "thomashexton.h"

/* ────────────────────────────────────────────────────────────────────────── *
 *  KEYMAP HELPERS
 * ────────────────────────────────────────────────────────────────────────── */
#define THUMB_L_TAB   LT(LAYER_LOWER, KC_TAB)  // Left thumb outboard of Space → LOWER (NAV), tap for Tab
#define THUMB_L_OUTER LT(LAYER_RAISE, KC_SPC)  // Left outer thumb → RAISE (NUM)
#define THUMB_L_INNER OSM(MOD_LSFT)            // Left inner thumb → one-shot Shift (hold works as normal Shift)

#define THUMB_R_OUTER LT(LAYER_LOWER, KC_BSPC) // Right outer thumb → LOWER (NAV)
#define THUMB_R_INNER RSFT_T(KC_ENT)           // Right inner thumb → Shift on hold, Enter on tap

// Padding for the three IFKB boards that are not connected to this dongle.
#define XX7  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define XX6  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define XX14 XX7, XX7
#define PAD_NOT_CONNECTED \
    XX14, XX14, XX14, XX14, XX14, XX6,       /* ergo  (76) */ \
    XX14, XX14, XX14,                        /* corne (42) */ \
    XX14, XX14, XX14, XX14, XX7, XX6         /* alice (69) */

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
#define LAYOUT_eglt(...)    LAYOUT_wrapper(PAD_NOT_CONNECTED, __VA_ARGS__)

/* ────────────────────────────────────────────────────────────────────────── *
 *  COMBO TABLE (shared definitions from users/thomashexton/combos.h)
 * ────────────────────────────────────────────────────────────────────────── */
combo_t key_combos[] = {
    ALL_COMBOS
};

/* ────────────────────────────────────────────────────────────────────────── *
 *  LAYER DEFINITIONS  (eglt block: 4 rows x 14 + 10 thumbs)
 * ────────────────────────────────────────────────────────────────────────── */
#define COLEMAK_DH_LAYER                                                                                          \
    XXXXXXX,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,  XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX, \
    XXXXXXX,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    XXXXXXX,  XXXXXXX, KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, XXXXXXX, \
    XXXXXXX,            TH_HRM_LEFT(A, R, S, T),    KC_G,  XXXXXXX,  XXXXXXX, KC_M,    TH_HRM_RIGHT(N, E, I, O),           XXXXXXX, \
    XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_BSLS,   XXXXXXX, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX, \
    XXXXXXX, THUMB_L_TAB, THUMB_L_OUTER, THUMB_L_INNER, XXXXXXX,     TO(LAYER_GAME), THUMB_R_INNER, THUMB_R_OUTER, XXXXXXX, XXXXXXX

#define RAISE_LAYER                                                                                               \
    _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, \
    XXXXXXX, XXXXXXX, G(S(KC_LBRC)), XXXXXXX, G(S(KC_RBRC)), XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, KC_7,    KC_8,    KC_9,    XXXXXXX, XXXXXXX, \
    XXXXXXX, TH_HRM_LEFT_MODS,                            XXXXXXX,   XXXXXXX, XXXXXXX, KC_4,    KC_5,    KC_6,    KC_0,    XXXXXXX, \
    XXXXXXX, XXXXXXX, G(KC_LBRC),    XXXXXXX, G(KC_RBRC),    XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, KC_1,    KC_2,    KC_3,    XXXXXXX, XXXXXXX, \
    _______, _______, _______, _______, _______,                     XXXXXXX, _______, _______, _______, _______

#define LOWER_LAYER                                                                                               \
    _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, \
    XXXXXXX, XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_VOLU, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, XXXXXXX,   XXXXXXX, TH_HRM_RIGHT_MODS,                           XXXXXXX, \
    XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, _______, _______, _______, _______,                     XXXXXXX, _______, _______, _______, _______

#define SYMBOL_LAYER                                                                                              \
    _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, \
    XXXXXXX, KC_GRV,  KC_BSLS, KC_MINS, KC_UNDS, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, KC_EQL,  KC_PLUS, KC_SLSH, KC_PIPE, XXXXXXX, \
    XXXXXXX, TH_HRM_LEFT_MODS,                            XXXXXXX,   XXXXXXX, TH_HRM_RIGHT_MODS,                           XXXXXXX, \
    XXXXXXX, KC_LABK, KC_LBRC, KC_LCBR, KC_LPRN, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, KC_RPRN, KC_RCBR, KC_RBRC, KC_RABK, XXXXXXX, \
    _______, _______, _______, _______, _______,                     XXXXXXX, _______, _______, _______, _______

/* QWERTY gaming layer (layer 3). */
#define GAME_LAYER                                                                                                \
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,      KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_HOME, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,      KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_PGUP, \
    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,      KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_PGDN, \
    KC_INS,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,      KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_END,  \
    KC_LALT, KC_LCTL, KC_SPC,  KC_ESC,  KC_M,                        TO(LAYER_BASE), KC_ENT, KC_BSPC, KC_DEL, KC_RGUI

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE]   = LAYOUT_eglt(COLEMAK_DH_LAYER),
    [LAYER_RAISE]  = LAYOUT_eglt(RAISE_LAYER),
    [LAYER_LOWER]  = LAYOUT_eglt(LOWER_LAYER),
    [LAYER_SYMBOL] = LAYOUT_eglt(SYMBOL_LAYER),
    [LAYER_GAME]   = LAYOUT_eglt(GAME_LAYER)
};
// clang-format on

/* ────────────────────────────────────────────────────────────────────────── *
 *  CALLBACKS
 * ────────────────────────────────────────────────────────────────────────── */
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, LAYER_LOWER, LAYER_RAISE, LAYER_SYMBOL);
}

/* Keymap-specific keycodes (none yet) — called from users/thomashexton.c. */
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    (void)keycode;
    (void)record;
    return true;
}
