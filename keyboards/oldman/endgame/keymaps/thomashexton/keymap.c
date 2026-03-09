#include QMK_KEYBOARD_H
#include "thomashexton.h"

/* ────────────────────────────────────────────────────────────────────────── *
 *  KEYMAP HELPERS AND LAYER SETUP
 * ────────────────────────────────────────────────────────────────────────── */
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

enum keymap_keycodes {
    TH_SPC_LOW = SAFE_RANGE,
    TH_BSP_RSE,
};

typedef struct {
    bool     pressed;
    bool     interrupted;
    uint16_t timer;
} thumb_hold_state_t;

static thumb_hold_state_t th_spc_low_state = {0};
static thumb_hold_state_t th_bsp_rse_state = {0};

// Bottom row mods - CAGS on left (Ctrl, Alt, GUI/Cmd, Shift), mirrored SGAC on right
// Now on bottom row: Z, X, C, D on left; H, comma, dot, slash on right
#define ____CAGS_L____(k01, k02, k03, k04) LCTL_T(KC_##k01), LALT_T(KC_##k02), LGUI_T(KC_##k03), LSFT_T(KC_##k04)
#define ____SGAC_R____(k01, k02, k03, k04) RSFT_T(KC_##k01), RGUI_T(KC_##k02), RALT_T(KC_##k03), RCTL_T(KC_##k04)

// Bottom row mods as full keycode definitions - used in combination with other keys/layers
#define __________________CAGS_L___________________ KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX
#define ___________________SGAC_R__________________ XXXXXXX, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL

#define THUML1 TH_SPC_LOW               // Left large thumb near center → LOWER on hold, Space on tap
#define THUML2 MO(LAYER_RAISE)          // Left small thumb → RAISE

#define THUMR1 TH_BSP_RSE               // Right large thumb near center → RAISE on hold, Backspace on tap
#define THUMR2 LT(LAYER_LOWER, KC_ENT)  // Right small thumb → LOWER

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
#define COLEMAK_DH_LAYER                                                                   \
              KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_QUOT,         \
              KC_A, KC_R, KC_S, T_KEY, KC_G, KC_M, N_KEY, KC_E, KC_I, KC_O,          \
    ____CAGS_L____(Z, X, C, D), KC_V, KC_K, ____SGAC_R____(H, COMM, DOT, SLSH),      \
           _______,         THUML2, THUML1, THUMR1, THUMR2,          _______

#define RAISE_LAYER                                                                             \
    XXXXXXX, KC_HOME, XXXXXXX,  KC_END, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, KC_MPRV,   KC_UP, KC_MNXT, KC_VOLD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, ___________________SGAC_R__________________, \
    XXXXXXX,                   _______, _______, _______, _______,                   XXXXXXX

#define LOWER_LAYER                                                                    \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_7, KC_8, KC_9, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_4, KC_5, KC_6, XXXXXXX, \
    __________________CAGS_L___________________,    KC_0, KC_1, KC_2, KC_3, XXXXXXX, \
    XXXXXXX,                   _______, _______, _______, _______,          XXXXXXX

#define SYMBOL_LAYER                                                                                     \
    KC_GRV, KC_LABK, KC_LCBR, KC_LPRN, XXXXXXX, XXXXXXX, KC_RPRN, KC_RCBR, KC_RABK, KC_TILD,           \
    XXXXXXX, KC_BSLS, KC_LBRC, KC_MINS,  KC_EQL,  KC_PLUS, KC_UNDS, KC_RBRC, KC_SLSH, KC_PIPE,         \
    __________________CAGS_L___________________,   ___________________SGAC_R__________________,          \
    XXXXXXX,                     _______, _______, _______, _______,                     XXXXXXX

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT_wrapper(COLEMAK_DH_LAYER),
    [LAYER_RAISE] = LAYOUT_wrapper(RAISE_LAYER),
    [LAYER_LOWER] = LAYOUT_wrapper(LOWER_LAYER),
    [LAYER_SYMBOL] = LAYOUT_wrapper(SYMBOL_LAYER)
};
// clang-format on

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

// Initialize keyboard
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
    if (record->event.pressed) {
        if (keycode != TH_SPC_LOW && th_spc_low_state.pressed) {
            th_spc_low_state.interrupted = true;
        }
        if (keycode != TH_BSP_RSE && th_bsp_rse_state.pressed) {
            th_bsp_rse_state.interrupted = true;
        }
    }

    switch (keycode) {
        case TH_SPC_LOW:
            if (record->event.pressed) {
                th_spc_low_state.pressed = true;
                th_spc_low_state.interrupted = th_bsp_rse_state.pressed;
                th_spc_low_state.timer = timer_read();
                layer_on(LAYER_LOWER);
            } else {
                layer_off(LAYER_LOWER);

                if (!th_spc_low_state.interrupted && timer_elapsed(th_spc_low_state.timer) < TAPPING_TERM) {
                    tap_code(KC_SPC);
                }

                th_spc_low_state.pressed = false;
                th_spc_low_state.interrupted = false;
            }
            return false;

        case TH_BSP_RSE:
            if (record->event.pressed) {
                th_bsp_rse_state.pressed = true;
                th_bsp_rse_state.interrupted = th_spc_low_state.pressed;
                th_bsp_rse_state.timer = timer_read();
                layer_on(LAYER_RAISE);
            } else {
                layer_off(LAYER_RAISE);

                if (!th_bsp_rse_state.interrupted && timer_elapsed(th_bsp_rse_state.timer) < TAPPING_TERM) {
                    uint8_t mods = get_mods();
                    uint8_t oneshot_mods = get_oneshot_mods();

                    if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
                        clear_mods();
                        clear_oneshot_mods();
                        tap_code(KC_DEL);
                        set_mods(mods);
                        set_oneshot_mods(oneshot_mods);
                    } else {
                        tap_code(KC_BSPC);
                    }
                }

                th_bsp_rse_state.pressed = false;
                th_bsp_rse_state.interrupted = false;
            }
            return false;
    }

    return true; // Continue processing for all keycodes
}
