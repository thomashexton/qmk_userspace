### OLD LAYERS

/* #define LAYER_FUN                                                                 \
 * _______, _______, _______, _______, _______, XXXXXXX,   KC_F7,   KC_F8,   KC_F9,  KC_F12, \
 * ______________HOME_ROW_GASC_L______________, XXXXXXX,   KC_F4,   KC_F5,   KC_F6,  KC_F11, \
 * _______, _______, _______, _______, _______, XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F10, \
 *                   XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX
 */

/* #define LAYER_MEDIA                                                                  \
 *     _______, _______, _______, _______, _______, KC_VOLU, XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, \
 *     _______, _______, _______, _______, _______, KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, \
 *     XXXXXXX, KC_BTN2, KC_BTN3, KC_BTN1, XXXXXXX,     KC_MUTE, KC_BTN1, KC_BTN3, KC_BTN2, XXXXXXX, \
 *     _______, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX
 */

/* #define LAYER_NAV                                                             \
 *     _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
 *     ______________HOME_ROW_GASC_L______________, KC_CAPS, KC_LEFT, KC_UP,   KC_RGHT, XXXXXXX, \
 *     _______, _______, _______, _______, _______, KC_INS, XXXXXXX,  KC_DOWN, XXXXXXX, KC_END, \
 *                       XXXXXXX, _______, XXXXXXX, KC_ENT, KC_BSPC
 */

/* #define LAYER_NUM                                                                  \
 *     KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC, _______, _______, _______, _______, _______, \
 *     KC_SCLN,    KC_4,    KC_5,    KC_6,  KC_EQL, ______________HOME_ROW_CSAG_R______________, \
 *      KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS, _______, _______, _______, _______, _______, \
 *                        KC_DOT,    KC_0, KC_MINS, XXXXXXX, _______
 */

/* #define LAYER_SYM                                                                  \
 *     XXXXXXX, KC_AMPR, KC_ASTR, KC_LPRN, XXXXXXX, _______, _______, _______, _______, _______, \
 *     KC_COLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, ___GACS_R___(  LPRN, RPRN, LCBR, RCBR), \
 *     KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE, _______, _______, _______, _______, _______, \
 *                       KC_LPRN, KC_RPRN, KC_UNDS, _______, XXXXXXX
 */

/*
 * Expects a 10-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.
 *   POINTER_MOD(LAYER_ALPHAS_QWERTY)
 */
/* #define _POINTER_MOD(                                                 \
 *   L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
 *   L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
 *   L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
 *   ...)                                                               \
 *            L00,         L01,         L02,         L03,         L04,  \
 *            R05,         R06,         R07,         R08,         R09,  \
 *            L10,         L11,         L12,         L13,         L14,  \
 *             R15,         R16,         R17,         R18,         R19, \
 *     _L_PTR(L20),        L21,         L22,         L23,         L24,  \
 *            R25,         R26,         R27,         R28,  _L_PTR(R29), \
 *     __VA_ARGS__
 */
