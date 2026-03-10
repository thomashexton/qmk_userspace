#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#ifdef TAPPING_TERM
#    undef TAPPING_TERM
#endif
#define TAPPING_TERM 150
#ifdef CHORDAL_HOLD
#    undef CHORDAL_HOLD
#endif

#define COMBO_COUNT_AUTO
#define COMBO_TERM 60        // Time window for combo activation (default is 50ms, increased for easier timing)
#define COMBO_MUST_HOLD_MODS // Mods must be held during combo activation
#define COMBO_HOLD_TERM 150  // How long to hold combo for repeat/hold actions

// Mouse acceleration settings - only used when MACCEL_ENABLE is set by keyboard
#ifdef MACCEL_ENABLE
#   define MACCEL_TAKEOFF 2.0     // lower/higher value = curve takes off more smoothly/abruptly
#   define MACCEL_GROWTH_RATE 0.5 // lower/higher value = curve reaches its upper limit slower/faster
#   define MACCEL_OFFSET 2.75     // lower/higher value = acceleration kicks in earlier/later
#   define MACCEL_LIMIT 0.25      // lower limit of accel curve (minimum acceleration factor)
#endif
