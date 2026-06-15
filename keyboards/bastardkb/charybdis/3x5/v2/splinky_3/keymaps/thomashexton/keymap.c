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

#define POINTER_HOLD_L LT(LAYER_POINTER, KC_D) // Hold D for pointer layer, tap for D
#define POINTER_HOLD_R LT(LAYER_POINTER, KC_H) // Hold H for pointer layer, tap for H

enum keymap_keycodes {
    P_SCROLL = SAFE_RANGE,
    P_DEBUG,
};

static bool  pointer_scroll_active         = false;
static bool  pointer_scroll_just_activated = false;
static bool  pointer_scroll_transitioning  = false;
static uint32_t pointer_scroll_changed_at  = 0;
static float pointer_scroll_remainder_h = 0.0f;
static float pointer_scroll_remainder_v = 0.0f;

// Scroll feel is mainly controlled by these two values.
// Lower DPI or higher divisor = slower scrolling.
#define POINTER_SCROLL_DPI 100
#define POINTER_SCROLL_DIVISOR 10.0f
#define POINTER_SCROLL_SETTLE_MS 30
#define POINTER_SCROLL_MAX_INPUT 30
#define POINTER_DEBUG_MOVE_THRESHOLD 8

#ifdef CONSOLE_ENABLE
static bool pointer_debug_enabled = false;
#endif

static bool pointer_scroll_is_settling(void) {
    return pointer_scroll_transitioning && timer_elapsed32(pointer_scroll_changed_at) < POINTER_SCROLL_SETTLE_MS;
}

static void clear_pointer_axes(report_mouse_t *mouse_report) {
    mouse_report->x = 0;
    mouse_report->y = 0;
    mouse_report->h = 0;
    mouse_report->v = 0;
}

static int8_t clamp_pointer_scroll_input(int8_t value) {
    if (value > POINTER_SCROLL_MAX_INPUT) {
        return POINTER_SCROLL_MAX_INPUT;
    }
    if (value < -POINTER_SCROLL_MAX_INPUT) {
        return -POINTER_SCROLL_MAX_INPUT;
    }
    return value;
}

static uint16_t pointer_normal_cpi(void) {
    if (charybdis_get_pointer_sniping_enabled()) {
        return charybdis_get_pointer_sniping_dpi();
    }
    return charybdis_get_pointer_default_dpi();
}

static void restore_pointer_cpi(void) {
    pointing_device_set_cpi(pointer_normal_cpi());
}

#ifdef CONSOLE_ENABLE
static int16_t pointer_scroll_remainder_x100(float remainder) {
    return (int16_t)(remainder * 100.0f);
}

static void pointer_debug_report(const char *stage, report_mouse_t in, report_mouse_t out) {
    if (!pointer_debug_enabled) {
        return;
    }

    if (in.x == 0 && in.y == 0 && in.h == 0 && in.v == 0 && out.x == 0 && out.y == 0 && out.h == 0 && out.v == 0) {
        return;
    }

    if (!pointer_scroll_active && !pointer_scroll_is_settling() && abs(in.x) < POINTER_DEBUG_MOVE_THRESHOLD && abs(in.y) < POINTER_DEBUG_MOVE_THRESHOLD) {
        return;
    }

    uprintf("PTR:%s t=%lu cpi=%u scroll=%u settle=%u in=%d,%d,%d,%d out=%d,%d,%d,%d rem=%d,%d\n",
            stage,
            timer_read32(),
            pointing_device_get_cpi(),
            pointer_scroll_active,
            pointer_scroll_is_settling(),
            (int)in.x,
            (int)in.y,
            (int)in.h,
            (int)in.v,
            (int)out.x,
            (int)out.y,
            (int)out.h,
            (int)out.v,
            (int)pointer_scroll_remainder_x100(pointer_scroll_remainder_h),
            (int)pointer_scroll_remainder_x100(pointer_scroll_remainder_v));
}
#else
#    define pointer_debug_report(stage, in, out) ((void)0)
#endif

static void set_pointer_scroll(bool active) {
    pointer_scroll_active        = active;
    pointer_scroll_changed_at    = timer_read32();
    pointer_scroll_transitioning = true;
    pointer_scroll_remainder_h = 0.0f;
    pointer_scroll_remainder_v = 0.0f;

    if (active) {
        pointer_scroll_just_activated = true;
        pointing_device_set_cpi(POINTER_SCROLL_DPI);
        return;
    }

    pointer_scroll_just_activated = false;
    restore_pointer_cpi();
}

#ifdef RGB_MATRIX_ENABLE
static RGB layer_rgb(layer_state_t state) {
    const bool symbol_active  = state & (1UL << LAYER_SYMBOL);
    const bool pointer_active = state & (1UL << LAYER_POINTER);

    if (symbol_active) {
        return (RGB){80, 80, 80};
    }

    if (pointer_active) {
        return (RGB){80, 0, 80};
    }

    switch (get_highest_layer(state)) {
        case LAYER_LOWER:
            return (RGB){80, 0, 0};
        case LAYER_RAISE:
            return (RGB){0, 0, 80};
        default:
            return (RGB){0, 80, 0};
    }
}
#endif

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
#define COLEMAK_DH_LAYER                                                                               \
                   KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_QUOT,                      \
                  TH_HRM_LEFT(A, R, S, T), KC_G, KC_M, TH_HRM_RIGHT(N, E, I, O),                       \
               KC_Z, KC_X, KC_C, POINTER_HOLD_L, KC_V, KC_K, POINTER_HOLD_R, KC_COMM, KC_DOT, KC_SLSH, \
          XXXXXXX, THUMB_L_OUTER, THUMB_L_INNER, THUMB_R_INNER, THUMB_R_OUTER

#define RAISE_LAYER                                                                        \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_7,   KC_8,   KC_9, XXXXXXX, \
                               TH_HRM_LEFT_MODS, XXXXXXX,   KC_4,   KC_5,   KC_6, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_0,   KC_1,   KC_2,   KC_3, XXXXXXX, \
                      XXXXXXX, _______, _______, _______, _______

#define LOWER_LAYER                                                                           \
    XXXXXXX, KC_HOME,   KC_UP,  KC_END, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, TH_HRM_RIGHT_MODS,                           \
    XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                      XXXXXXX, _______, _______, _______, _______

#define SYMBOL_LAYER                                                                          \
    KC_GRV,  KC_BSLS, KC_MINS, KC_UNDS, XXXXXXX, XXXXXXX, KC_EQL,  KC_PLUS, KC_SLSH, KC_PIPE, \
                               TH_HRM_LEFT_MODS, TH_HRM_RIGHT_MODS,                           \
    KC_LABK, KC_LBRC, KC_LCBR, KC_LPRN, XXXXXXX, XXXXXXX, KC_RPRN, KC_RCBR, KC_RBRC, KC_RABK, \
                      XXXXXXX, _______, _______, _______, _______

#define POINTER_LAYER                                                                                     \
    P_DEBUG, MA_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_SPD,  RGB_TOG, RGB_SPI, XXXXXXX,        \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_RMOD, XXXXXXX, RGB_MOD, XXXXXXX,        \
   XXXXXXX, XXXXXXX, P_SCROLL, XXXXXXX, XXXXXXX, XXXXXXX, DPI_RMOD, P_SCROLL, DPI_MOD, XXXXXXX, \
                      XXXXXXX, KC_BTN1, KC_BTN3, KC_BTN3, KC_BTN1

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT_wrapper(COLEMAK_DH_LAYER),
    [LAYER_RAISE] = LAYOUT_wrapper(RAISE_LAYER),
    [LAYER_LOWER] = LAYOUT_wrapper(LOWER_LAYER),
    [LAYER_SYMBOL] = LAYOUT_wrapper(SYMBOL_LAYER),
    [LAYER_POINTER] = LAYOUT_wrapper(POINTER_LAYER)
};
// clang-format on

/* ────────────────────────────────────────────────────────────────────────── *
 *  CHORDAL HOLD HANDEDNESS
 *  Per-key hand for CHORDAL_HOLD (see users/thomashexton/config.h). 'L'/'R' mark
 *  the physical hand; thumbs are '*' so their layer-taps always hold rather than
 *  being forced to tap by a same-hand chord.
 * ────────────────────────────────────────────────────────────────────────── */
#ifdef CHORDAL_HOLD
// clang-format off
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT_wrapper(
    'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R',
              '*', '*', '*',   '*', '*'
);
// clang-format on
#endif

/* ────────────────────────────────────────────────────────────────────────── *
 *  KEYBOARD INITIALIZATION
 * ────────────────────────────────────────────────────────────────────────── */

// Initialize keyboard
void keyboard_post_init_user(void) {
    #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_enable_noeeprom();
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(HSV_OFF);
    #endif
}

#ifdef POINTING_DEVICE_ENABLE
bool pointing_device_accel_should_process(void) {
    return !pointer_scroll_active && !pointer_scroll_is_settling();
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    const report_mouse_t input_report = mouse_report;

    if (pointer_scroll_is_settling()) {
        clear_pointer_axes(&mouse_report);
        pointer_debug_report("settle", input_report, mouse_report);
        return mouse_report;
    }

    const bool was_transitioning = pointer_scroll_transitioning;
    pointer_scroll_transitioning = false;

    if (was_transitioning && !pointer_scroll_active) {
        restore_pointer_cpi();
    }

    if (pointer_scroll_active) {
        if (pointer_scroll_just_activated) {
            pointer_scroll_just_activated = false;
            clear_pointer_axes(&mouse_report);
            pointer_debug_report("first", input_report, mouse_report);
            return mouse_report;
        }

        const int8_t scroll_x = clamp_pointer_scroll_input(mouse_report.x);
        const int8_t scroll_y = clamp_pointer_scroll_input(mouse_report.y);

        pointer_scroll_remainder_h += (float)scroll_x / POINTER_SCROLL_DIVISOR;
        pointer_scroll_remainder_v -= (float)scroll_y / POINTER_SCROLL_DIVISOR;

        mouse_report.h = (int8_t)pointer_scroll_remainder_h;
        mouse_report.v = (int8_t)pointer_scroll_remainder_v;

        pointer_scroll_remainder_h -= (int8_t)pointer_scroll_remainder_h;
        pointer_scroll_remainder_v -= (int8_t)pointer_scroll_remainder_v;

        mouse_report.x = 0;
        mouse_report.y = 0;

        pointer_debug_report("scroll", input_report, mouse_report);
        return mouse_report;
    }

    pointer_debug_report("move", input_report, mouse_report);
    return mouse_report;
}
#endif

/* ────────────────────────────────────────────────────────────────────────── *
 *  KEYMAP CALLBACK FUNCTIONS
 * ────────────────────────────────────────────────────────────────────────── */

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, LAYER_LOWER, LAYER_RAISE, LAYER_SYMBOL);

    if (pointer_scroll_active && !(state & (1UL << LAYER_POINTER))) {
        set_pointer_scroll(false);
    }

    return state;
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    const RGB color = layer_rgb(layer_state | default_layer_state);

    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, color.r, color.g, color.b);
    }

    return false;
}
#endif

/**
 * Process keymap-specific keycodes
 * This is called by process_record_user in thomashexton.c
 * Currently, custom punctuation shift behavior is handled at the user level
 */
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case P_SCROLL:
            set_pointer_scroll(record->event.pressed);
            return false;
        case P_DEBUG:
#ifdef CONSOLE_ENABLE
            if (record->event.pressed) {
                pointer_debug_enabled = !pointer_debug_enabled;
                debug_enable          = false;
                debug_mouse           = false;
                uprintf("PTR:debug %u\n", pointer_debug_enabled);
            }
#endif
            return false;
        default:
            return true;
    }
}
