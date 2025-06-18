#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

#define COMBO_COUNT_AUTO

// Mouse acceleration settings - only used when MACCEL_ENABLE is set by keyboard
#ifdef MACCEL_ENABLE
#   define MACCEL_TAKEOFF 2.0     // lower/higher value = curve takes off more smoothly/abruptly
#   define MACCEL_GROWTH_RATE 0.5 // lower/higher value = curve reaches its upper limit slower/faster
#   define MACCEL_OFFSET 2.75     // lower/higher value = acceleration kicks in earlier/later
#   define MACCEL_LIMIT 0.25      // lower limit of accel curve (minimum acceleration factor)
#endif
