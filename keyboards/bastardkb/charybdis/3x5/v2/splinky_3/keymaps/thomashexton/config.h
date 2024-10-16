#pragma once

/* Charybdis-specific features. */
#define CHARYBDIS_MINIMUM_DEFAULT_DPI 1000
#define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 100
#define CHARYBDIS_MINIMUM_SNIPING_DPI 100
#define CHARYBDIS_SNIPING_DPI_CONFIG_STEP 100

#ifdef VIA_ENABLE
  /* VIA configuration. */
  #define DYNAMIC_KEYMAP_LAYER_COUNT 10
#endif

/* Disable unused features. */
#define NO_ACTION_ONESHOT

/* Charybdis-specific features. */
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

#ifdef POINTING_DEVICE_ENABLE
// Automatically enable the pointer layer when moving the trackball.
// See also:
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS`
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD`
#endif

// #define TAPPING_TERM 150

#ifdef MACCEL_ENABLE
#   define MACCEL_TAKEOFF 2.0      // lower/higher value = curve takes off more smoothly/abruptly
#   define MACCEL_GROWTH_RATE 0.25 // lower/higher value = curve reaches its upper limit slower/faster
#   define MACCEL_OFFSET 2.2       // lower/higher value = acceleration kicks in earlier/later
#   define MACCEL_LIMIT 0.2        // lower limit of accel curve (minimum acceleration factor)
#endif
