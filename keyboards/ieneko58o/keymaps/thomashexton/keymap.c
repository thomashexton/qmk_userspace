/* Ieneko58O (5x12 unibody ortho) — Thomas's userspace keymap.
 *
 * Colemak-DH base with home-row mods. Thumb rule, shared by every board in
 * this userspace: the key under the resting thumb is RAISE (numbers) on the
 * left and LOWER (nav) on the right, with the layer's content always on the
 * opposite hand.
 *
 * LAYER_GAME is a sticky WoW layer (Del toggles GAME ↔ BASE): same Colemak
 * letters but plain (no HRM) so FRST can be held for movement. Primary
 * Ctrl/Shift/Alt live on the Swiftpoint Z3; the left-column Ctrl/Shift and
 * left-outer-thumb Alt are keyboard-side backups. Esc sits on grave.
 */
#include QMK_KEYBOARD_H
#include "thomashexton.h"

/* ────────────────────────────────────────────────────────────────────────── *
 *  KEYMAP HELPERS
 * ────────────────────────────────────────────────────────────────────────── */
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

// Naming and behaviour mirror oldman, the other unibody in this userspace.
#define THUMB_L_INNER LT(LAYER_RAISE, KC_SPC)  // Left 2U, under the resting thumb  → RAISE (numbers), Space on tap
#define THUMB_L_OUTER LSFT_T(KC_TAB)           // Left outboard of the 2U  → Shift on hold, Tab on tap
#define THUMB_R_INNER LT(LAYER_LOWER, KC_BSPC) // Right 2U, under the resting thumb → LOWER (nav), Backspace on tap
#define THUMB_R_OUTER RSFT_T(KC_ENT)           // Right outboard of the 2U → Shift on hold, Enter on tap

// 4,2 and 4,9 are a thumb stretch, used purely for hotkey chords, so they are plain
// modifiers rather than mod-taps: no TAPPING_TERM to misfire against. Hyper is
// Ctrl+Shift+Alt+GUI, Meh is the same without GUI — two distinct chord namespaces.
// The Gui/Alt they displace remain on the home row via TH_HRM_LEFT/RIGHT.

/* ────────────────────────────────────────────────────────────────────────── *
 *  COMBO TABLE (shared definitions from users/thomashexton/combos.h)
 * ────────────────────────────────────────────────────────────────────────── */
combo_t key_combos[] = {
    ALL_COMBOS
};

/* ────────────────────────────────────────────────────────────────────────── *
 *  CHORDAL HOLD
 * ────────────────────────────────────────────────────────────────────────── *
 * Required by CHORDAL_HOLD in users/thomashexton/config.h — the build fails to
 * link without it. Unibody handedness splits at the column boundary: cols 0-5
 * left, cols 6-11 right. The two 2U thumbs are '*' so they always hold.
 */
// clang-format off
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
    'L', 'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R', 'R',
    '*', '*', '*', '*',   '*',        '*',   '*', '*', '*', '*'
);
// clang-format on

/* ────────────────────────────────────────────────────────────────────────── *
 *  LAYER DEFINITIONS  (4 rows x 12, then 4 + 2U + 2U + 4)
 * ────────────────────────────────────────────────────────────────────────── */
// clang-format off
#define COLEMAK_DH_LAYER                                                                                  \
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    TO(LAYER_GAME), \
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, KC_BSPC, \
    KC_LCTL, TH_HRM_LEFT(A, R, S, T),          KC_G,    KC_M,    TH_HRM_RIGHT(N, E, I, O),          KC_ENT,  \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    XXXXXXX, XXXXXXX, KC_HYPR, THUMB_L_OUTER, THUMB_L_INNER,  THUMB_R_INNER, THUMB_R_OUTER, KC_MEH,  XXXXXXX, XXXXXXX

/* RAISE — numbers on the right hand, macOS tab/history nav on the left, reached with the
 * LEFT thumb. Same convention as every board in this userspace. Top row is F1-F12. */
#define RAISE_LAYER                                                                                       \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
    _______, XXXXXXX, G(S(KC_LBRC)), XXXXXXX, G(S(KC_RBRC)), XXXXXXX, XXXXXXX, KC_7, KC_8,  KC_9,    XXXXXXX, _______, \
    _______, TH_HRM_LEFT_MODS,                          XXXXXXX, KC_4,    KC_5,    KC_6,    KC_0,    _______, \
    _______, XXXXXXX, G(KC_LBRC),    XXXXXXX, G(KC_RBRC),    XXXXXXX, XXXXXXX, KC_1, KC_2,  KC_3,    XXXXXXX, _______, \
    _______, _______, _______, _______,       _______,        _______,      _______, _______, _______, _______

/* LOWER — arrows / home / end / media on the LEFT hand, reached with the RIGHT thumb.
 * Cross-hand, as on every board in this userspace. */
#define LOWER_LAYER                                                                                       \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
    _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, TH_HRM_RIGHT_MODS,                            _______, \
    _______, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
    _______, _______, _______, _______,       _______,        _______,      _______, _______, _______, _______

/* SYMBOL — tri-layer, reached by holding both 2U thumbs. */
#define SYMBOL_LAYER                                                                                      \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, KC_GRV,  KC_BSLS, KC_MINS, KC_UNDS, XXXXXXX, XXXXXXX, KC_EQL,  KC_PLUS, KC_SLSH, KC_PIPE, _______, \
    _______, TH_HRM_LEFT_MODS,                          TH_HRM_RIGHT_MODS,                            _______, \
    _______, KC_LBRC, KC_LCBR, KC_LABK, KC_LPRN, XXXXXXX, XXXXXXX, KC_RPRN, KC_RABK, KC_RCBR, KC_RBRC, _______, \
    _______, _______, _______, _______,       _______,        _______,      _______, _______, _______, _______

/* GAME — sticky WoW layer. Plain Colemak so FRST holds are instant movement;
 * no raise/lower thumbs. Del returns to base. */
#define GAME_LAYER                                                                                        \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    TO(LAYER_BASE), \
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, KC_BSPC, \
    KC_LCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,  \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT, KC_SPC,           KC_BSPC,          KC_ENT,  XXXXXXX, XXXXXXX, XXXXXXX

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE]   = LAYOUT_wrapper(COLEMAK_DH_LAYER),
    [LAYER_RAISE]  = LAYOUT_wrapper(RAISE_LAYER),
    [LAYER_LOWER]  = LAYOUT_wrapper(LOWER_LAYER),
    [LAYER_SYMBOL] = LAYOUT_wrapper(SYMBOL_LAYER),
    [LAYER_GAME]   = LAYOUT_wrapper(GAME_LAYER)
};
// clang-format on

/* ────────────────────────────────────────────────────────────────────────── *
 *  CALLBACKS
 * ────────────────────────────────────────────────────────────────────────── */
#ifdef RGB_MATRIX_ENABLE
// WoW logo gold (#C8A951 → HSV) at a gentle brightness so it marks the layer
// without lighting the desk. Hue/sat match the metallic wordmark; val is dimmed.
static const hsv_t GAME_LAYER_HSV = {31, 152, 88};

static bool    game_leds_active;
static uint8_t saved_rgb_mode;
static uint8_t saved_rgb_speed;
static hsv_t   saved_rgb_hsv;

static void game_leds_on(void) {
    if (!game_leds_active) {
        saved_rgb_mode   = rgb_matrix_get_mode();
        saved_rgb_speed  = rgb_matrix_get_speed();
        saved_rgb_hsv    = rgb_matrix_get_hsv();
        game_leds_active = true;
    }
    // Mode and color changes are ignored while the matrix is disabled, and enabling
    // it resumes the EEPROM effect (the bright rainbow). Enable first, then replace it.
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(GAME_LAYER_HSV.h, GAME_LAYER_HSV.s, GAME_LAYER_HSV.v);
}

static void game_leds_off(void) {
    if (!game_leds_active) {
        return;
    }
    rgb_matrix_mode_noeeprom(saved_rgb_mode);
    rgb_matrix_set_speed_noeeprom(saved_rgb_speed);
    rgb_matrix_sethsv_noeeprom(saved_rgb_hsv.h, saved_rgb_hsv.s, saved_rgb_hsv.v);
    game_leds_active = false;
}
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, LAYER_LOWER, LAYER_RAISE, LAYER_SYMBOL);
#ifdef RGB_MATRIX_ENABLE
    // LEDs are a layer indicator only: dark on base, lit on any other layer.
    // The game layer is painted WoW gold and restores the previous effect after.
    const uint8_t layer = get_highest_layer(state);
    if (layer == LAYER_BASE) {
        game_leds_off();
        rgb_matrix_disable_noeeprom();
    } else if (layer == LAYER_GAME) {
        game_leds_on();
    } else {
        game_leds_off();
        rgb_matrix_enable_noeeprom();
    }
#endif
    return state;
}

#ifdef RGB_MATRIX_ENABLE
// Boot into the base layer, so start dark rather than inheriting the EEPROM state.
void keyboard_post_init_user(void) {
    rgb_matrix_disable_noeeprom();
}

// Paint over whatever effect is running. The EEPROM rainbow otherwise shows
// through on the game layer, because enabling the matrix resumes that effect.
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (get_highest_layer(layer_state) != LAYER_GAME) {
        return true;
    }

    const rgb_t rgb = hsv_to_rgb(GAME_LAYER_HSV);
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return false;
}
#endif

/* Keymap-specific keycodes (none yet) — called from users/thomashexton.c. */
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    (void)keycode;
    (void)record;
    return true;
}
