#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#ifdef TAPPING_TERM
#    undef TAPPING_TERM
#endif
#define TAPPING_TERM 150
#ifdef CHORDAL_HOLD
#    undef CHORDAL_HOLD
#endif
#ifdef PERMISSIVE_HOLD
#    undef PERMISSIVE_HOLD
#endif
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#define COMBO_COUNT_AUTO
#define COMBO_TERM 60        // Time window for combo activation (default is 50ms, increased for easier timing)
#define COMBO_MUST_HOLD_MODS // Mods must be held during combo activation
#define COMBO_HOLD_TERM 150  // How long to hold combo for repeat/hold actions

// Pointing-device acceleration settings for keymaps that include the community module.
// The Charybdis originally used a gentler maccel curve than the later shared defaults.
#if defined(KEYBOARD_bastardkb_charybdis_3x5_v2_splinky_3)
#    define POINTING_DEVICE_ACCEL_TAKEOFF 2.0
#    define POINTING_DEVICE_ACCEL_GROWTH_RATE 0.25
#    define POINTING_DEVICE_ACCEL_OFFSET 2.2
#    define POINTING_DEVICE_ACCEL_LIMIT 0.2
#else
#    define POINTING_DEVICE_ACCEL_TAKEOFF 2.0
#    define POINTING_DEVICE_ACCEL_GROWTH_RATE 0.5
#    define POINTING_DEVICE_ACCEL_OFFSET 2.75
#    define POINTING_DEVICE_ACCEL_LIMIT 0.25
#endif
