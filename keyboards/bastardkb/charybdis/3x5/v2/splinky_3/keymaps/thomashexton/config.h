#pragma once

#ifdef VIA_ENABLE
  /* VIA configuration. */
  #define DYNAMIC_KEYMAP_LAYER_COUNT 7
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

#define TAPPING_TERM 100
