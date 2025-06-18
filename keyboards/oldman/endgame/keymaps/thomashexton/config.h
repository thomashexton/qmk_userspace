#pragma once

// Combo settings
#define COMBO_COUNT 12
#define COMBO_TERM 30

// Layer tap settings for better modifier compatibility
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS

// Audio settings
#ifdef AUDIO_ENABLE
    #define AUDIO_CLICKY
#endif

// RGB settings
#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_STARTUP_ANIMATION
#endif 