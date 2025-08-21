#include "quantum.h"
#include "thomashexton.h"

/* ────────────────────────────────────────────────────────────────────────── *
 *  USER FUNCTIONS
 * ────────────────────────────────────────────────────────────────────────── */

/**
 * Handle custom keycode processing
 * Provides logical shift behavior for punctuation across all keyboards:
 * - Comma + Shift = Semicolon (instead of <)
 * - Dot + Shift = Colon (instead of >)
 * - Slash alone = Question Mark, Slash + Shift = Exclamation Mark (inverted behavior)
 * - Backspace + Shift = Delete
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Extract base keycode from mod-tap keys
    uint16_t base_keycode = keycode;
    
    // Check if this is a mod-tap key being tapped (not held)
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) && record->tap.count) {
        base_keycode = keycode & 0xFF;
    }
    
    // Handle comma with custom shift behavior (works for both KC_COMM and mod-tap versions)
    if (base_keycode == KC_COMM) {
        // Only handle custom comma behavior when the key is actually being tapped (not held for mod)
        if (record->event.pressed && (keycode == KC_COMM || (record->tap.count && record->tap.interrupted == false))) {
            uint8_t mods = get_mods();
            if (mods & MOD_MASK_SHIFT) {
                // Output semicolon instead of less-than
                unregister_mods(MOD_MASK_SHIFT);
                tap_code(KC_SEMICOLON);
                register_mods(mods);
            } else {
                tap_code(KC_COMMA);
            }
            return false;  // Skip default handling
        }
    }
    
    // Handle dot with custom shift behavior (works for both KC_DOT and mod-tap versions)
    if (base_keycode == KC_DOT) {
        // Only handle custom dot behavior when the key is actually being tapped (not held for mod)
        if (record->event.pressed && (keycode == KC_DOT || (record->tap.count && record->tap.interrupted == false))) {
            uint8_t mods = get_mods();
            if (mods & MOD_MASK_SHIFT) {
                // Output colon instead of greater-than
                unregister_mods(MOD_MASK_SHIFT);
                register_code(KC_LSFT);
                tap_code(KC_SEMICOLON);
                unregister_code(KC_LSFT);
                register_mods(mods);
            } else {
                tap_code(KC_DOT);
            }
            return false;  // Skip default handling
        }
    }
    
    // Handle slash with inverted behavior: / alone = ?, shift+/ = ! (only for mod-tap version, not combos)
    if (base_keycode == KC_SLSH) {
        // Only handle custom slash behavior for the actual mod-tap key, not combo-generated KC_SLSH
        if (record->event.pressed && (keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) && record->tap.count && record->tap.interrupted == false) {
            uint8_t mods = get_mods();
            if (mods & MOD_MASK_SHIFT) {
                // Output exclamation mark instead of ?
                unregister_mods(MOD_MASK_SHIFT);
                register_code(KC_LSFT);
                tap_code(KC_1);  // Shift + 1 = !
                unregister_code(KC_LSFT);
                register_mods(mods);
            } else {
                // Output ? instead of /
                register_code(KC_LSFT);
                tap_code(KC_SLSH);  // Shift + / = ?
                unregister_code(KC_LSFT);
            }
            return false;  // Skip default handling
        }
    }
    
    // Handle backspace with custom shift behavior: Shift + Backspace = Delete
    // This works for ANY layer-tap key with KC_BSPC as the tap keycode
    if ((keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        // Extract the tap keycode from the layer-tap key
        uint16_t tap_keycode = keycode & 0xFF;
        if (tap_keycode == KC_BSPC) {
            if (record->event.pressed && record->tap.count) {
                uint8_t mods = get_mods() | get_oneshot_mods();
                if (mods & MOD_MASK_SHIFT) {
                    // Send delete instead of backspace
                    clear_mods();
                    clear_oneshot_mods();
                    tap_code(KC_DEL);
                    set_mods(mods);
                    return false;  // Skip default processing
                }
            }
        }
    }
    
    // Handle custom keycodes defined in the keymap
    if (!process_record_keymap(keycode, record)) {
        return false;
    }
    
    return true; // Continue processing for all other keycodes
}

/**
 * Process mouse movement
 * Applies mouse acceleration if MACCEL is enabled
 */
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    #ifdef MACCEL_ENABLE
        mouse_report = pointing_device_task_maccel(mouse_report);
    #endif // MACCEL_ENABLE

    return mouse_report;
}
