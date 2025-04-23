#include "quantum.h"
#include "thomashexton.h"

#ifdef MACCEL_ENABLE
    #include "features/maccel/maccel.h"
#endif

/* ────────────────────────────────────────────────────────────────────────── *
 *  GLOBAL VARIABLES
 * ────────────────────────────────────────────────────────────────────────── */
// Drag scroll variables
bool set_scrolling = false;

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

/* ────────────────────────────────────────────────────────────────────────── *
 *  USER FUNCTIONS
 * ────────────────────────────────────────────────────────────────────────── */

/**
 * Handle custom keycode processing
 * This will handle all custom keycodes and then pass any other codes
 * to the keymap-specific process_record_keymap function
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Handle DRAG_SCROLL
    if (keycode == DRAG_SCROLL) {
        if (record->event.pressed) {
            set_scrolling = !set_scrolling; // Toggle scrolling mode
        }
        return false;
    }
    
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
 * Process mouse movement and implement drag scrolling
 * This handles the drag scrolling functionality, which will be 
 * consistent across all keyboards using this user space
 */
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
