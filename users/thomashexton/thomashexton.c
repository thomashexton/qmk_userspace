#include "quantum.h"
#include "thomashexton.h"

#ifdef MACCEL_ENABLE
    #include "features/maccel/maccel.h"
#endif

/* ────────────────────────────────────────────────────────────────────────── *
 *  USER FUNCTIONS
 * ────────────────────────────────────────────────────────────────────────── */

/**
 * Handle custom keycode processing
 * This will handle all custom keycodes and then pass any other codes
 * to the keymap-specific process_record_keymap function
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Handle COMMA_KEY
    if (keycode == COMMA_KEY) {
        if (record->event.pressed) {
            // Get the current mods state
            uint8_t mods = get_mods();
            
            // If shift is being held, output semicolon
            if (mods & MOD_MASK_SHIFT) {
                // Temporarily disable shift so it doesn't modify the semicolon
                unregister_mods(MOD_MASK_SHIFT);
                tap_code(KC_SEMICOLON);
                register_mods(mods);  // Restore mods
            } else {
                // Just output a comma
                tap_code(KC_COMMA);
            }
        }
        return false;  // Skip default handling
    }
    
    // Handle DOT_KEY
    if (keycode == DOT_KEY) {
        if (record->event.pressed) {
            // Get the current mods state
            uint8_t mods = get_mods();
            
            // If shift is being held, output colon
            if (mods & MOD_MASK_SHIFT) {
                // Temporarily disable shift so it doesn't modify our keys
                unregister_mods(MOD_MASK_SHIFT);
                // To make a colon, we need to press shift+semicolon
                register_code(KC_LSFT);
                tap_code(KC_SEMICOLON);
                unregister_code(KC_LSFT);
                register_mods(mods);  // Restore mods
            } else {
                // Just output a dot
                tap_code(KC_DOT);
            }
        }
        return false;  // Skip default handling
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
