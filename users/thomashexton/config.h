#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#ifdef TAPPING_TERM
#    undef TAPPING_TERM
#endif
// Base term is deliberately long (200) to curb accidental holds — chiefly GUI on
// the high-frequency E/S keys (a lingering E → Cmd+N etc). The Shift HRMs get a
// shorter term via get_tapping_term() in thomashexton.c so capitals stay snappy.
#define TAPPING_TERM 200
#ifndef TAPPING_TERM_PER_KEY
#    define TAPPING_TERM_PER_KEY
#endif
// Home-row-mod anti-misfire stack:
//   - CHORDAL_HOLD    : a tap-hold only becomes a mod/layer if the *next* key is
//                       on the opposite hand; same-hand rolls stay taps. Requires
//                       per-board handedness — see chordal_hold_layout in each
//                       board's keymap.c (thumbs are marked '*' so they always
//                       hold). Without that array the build fails to link.
//   - PERMISSIVE_HOLD : a cross-hand key pressed AND released while the tap-hold
//                       is down settles it as hold immediately, so intentional
//                       chords (e.g. HRM-shift + opposite-hand letter) work at
//                       any typing speed instead of waiting out TAPPING_TERM.
//   - FLOW_TAP_TERM   : within this many ms of a previous typing key, a tap-hold
//                       key is forced to tap — kills mod misfires during fast
//                       typing bursts. Shift mod-taps and the Space layer-tap
//                       are EXEMPT via get_flow_tap_term() in thomashexton.c:
//                       Shift is needed mid-stream for capitals, while Space
//                       must remain holdable after a word to reach layers.
#ifndef CHORDAL_HOLD
#    define CHORDAL_HOLD
#endif
#ifndef PERMISSIVE_HOLD
#    define PERMISSIVE_HOLD
#endif
#define FLOW_TAP_TERM 150
#ifndef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#    define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#endif

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
