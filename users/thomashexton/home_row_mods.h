#pragma once

/* ────────────────────────────────────────────────────────────────────────── *
 *  SHARED HOME ROW MOD ORDER
 * ────────────────────────────────────────────────────────────────────────── */
// Canonical order across Thomas's keyboards:
// - Left hand:  Ctrl, Alt, GUI/Cmd, Shift
// - Right hand: Shift, GUI/Cmd, Alt, Ctrl
#define TH_HRM_LEFT(k01, k02, k03, k04)  LCTL_T(KC_##k01), LALT_T(KC_##k02), LGUI_T(KC_##k03), LSFT_T(KC_##k04)
#define TH_HRM_RIGHT(k01, k02, k03, k04) RSFT_T(KC_##k01), RGUI_T(KC_##k02), RALT_T(KC_##k03), RCTL_T(KC_##k04)

// Plain modifiers in the same 3x5 column order, for layers where home row letters
// are replaced by navigation, symbols, pointer controls, etc.
#define TH_HRM_LEFT_MODS  KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX
#define TH_HRM_RIGHT_MODS XXXXXXX, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL
