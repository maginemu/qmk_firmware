#include QMK_KEYBOARD_H
#include "version.h"

#define BASE 0 // default layer
#define L1 1 // L1ols
#define L2 2
#define L3 3
#define L4 4
#define L5 5

enum custom_keycodes {
  EPRM = SAFE_RANGE,
  VRSN,
  RGB_SLD
};

// Fillers to make layering clearer
#define _______ KC_TRNS
#define XXXXXXX KC_NO

/*
  all trans keymap
KEYMAP(
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______,
                                           _______, _______,
                                                    _______,
                                  _______, _______, _______,
    // right hand
       _______,  _______, _______, KC,TRNS, _______, _______, _______,
       _______,  _______, _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______, _______,
       _______,  _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______, _______,
       _______, _______,
       _______,
       _______, _______, _______
)
 */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |   1  |   2  |   3  |   4  |   5  |  L2  |           | L3   |   6  |   7  |   8  |   9  |   0  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   Q  |   W  |   E  |   R  |   T  |  `   |           |  [   |   Y  |   U  |   I  |   O  |   P  |   -    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCtrl  |  A   |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|  \   |           |  ]   |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |/ / L2| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Fn /L1|  '"  |AltShf| LAlt |LGui  |                                       | RGui | LEFT | DOWN | UP   | Right/L1|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | Esc  | PgUp |       | PgUp |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | PgDn |       | PgDn |        |      |
 *                                 |Ctrl  |Shift |------|       |------| Space  |Enter |
 *                                 |      |      | Tab  |       | BKSP |        |      |
 *                                 `------------------- '       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left han
        KC_ESC,         KC_1,     KC_2,    KC_3,    KC_4,   KC_5,   TG(L2),
        KC_TAB,         KC_Q,     KC_W,    KC_E,    KC_R,   KC_T,   KC_GRV,
        KC_LCTL,        KC_A,     KC_S,    KC_D,    KC_F,   KC_G,
        KC_LSFT,        KC_Z,     KC_X,    KC_C,    KC_V,   KC_B,   KC_BSLS,
        LT(L1,KC_FN1),  KC_QUOT,  KC_LEFT, KC_LALT, KC_LGUI,

                 KC_ESC,        KC_PGUP,
                                KC_PGDN,
        KC_LCTL, SFT_T(KC_SPC), KC_TAB,


        // right hand
        TG(L3),      KC_6,   KC_7,   KC_8,     KC_9,     KC_0,           KC_EQL,
        KC_LBRC,     KC_Y,   KC_U,   KC_I,     KC_O,     KC_P,           KC_MINS,
                     KC_H,   KC_J,   KC_K,     KC_L,     KC_SCLN,        KC_QUOT,
        KC_RBRC,     KC_N,   KC_M,   KC_COMM,  KC_DOT,   LT(L2, KC_SLSH),KC_RSFT,
        KC_RGUI,     KC_LEFT,KC_DOWN,KC_UP,    LT(L1, KC_RIGHT),
        KC_PGUP,     CTL_T(KC_ESC),
        KC_PGDN,
        KC_BSPC, KC_SPC, KC_ENT
    ),

/* Keymap 1:
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------| Left | Down | Up   | Right|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L1] = LAYOUT_ergodox(
       _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,
       _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,
       _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, KC_LGUI,
                                           _______, _______,
                                                    _______,
                                  _______, _______, _______,
    // right hand
       _______,  KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,
       _______,  KC_6   , KC_7,    KC_8,    KC_9,     KC_0,    KC_F12,
                 KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
       _______,  _______, _______, _______, _______,  _______, _______,
                          KC_RGUI, _______, _______,  _______, _______,
       _______, _______,
       _______,
       _______, _______, _______
),


/* Keymap 2: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |Version |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |Reset   |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// L1
[L2] = LAYOUT_ergodox(
       // left hand
       M(0),   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,
       RESET,  KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,_______,
       _______,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       _______,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,_______,
       _______,_______,_______,_______,_______,
                                       _______,_______,
                                               _______,
                               _______,_______,_______,
       // right hand
       _______, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       _______, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, _______,
       _______, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, _______,
                         _______,KC_DOT,  KC_0,    KC_EQL,  _______,
       _______, _______,
       _______,
       _______, _______, _______
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |VolUp |VolDn | Mute |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |  Up  |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      | Left |  Down| RIGHT|      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[L3] = LAYOUT_ergodox(
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, KC_MS_U, _______, _______, _______,
       _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, KC_BTN1, KC_BTN2,
                                           _______, _______,
                                                    _______,
                                  _______, _______, _______,
    // right hand
       _______,  _______, KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,
       _______,  _______, _______, KC_UP, _______, _______, _______,
                _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, KC_MPLY,
       _______,  _______, _______, KC_MPRV, KC_MNXT, _______, _______,
                          _______, _______, _______, _______, _______,
       _______, _______,
       _______,
       _______, _______, KC_WBAK
),


[L4] = LAYOUT_ergodox(
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, KC_LGUI,
                                           _______, _______,
                                                    _______,
                                  _______, _______, _______,
    // right hand
       _______,  _______, _______, _______, _______, _______, _______,
       _______,  _______, _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______, _______,
       _______,  _______, _______, _______, _______, _______, _______,
                          KC_RGUI, _______, _______, _______, _______,
       _______, _______,
       _______,
       _______, _______, _______
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case EPRM:
        eeconfig_init();
        return false;
      case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
      #ifdef RGBLIGHT_ENABLE
      case RGB_SLD:
        rgblight_mode(1);
        return false;
      #endif
    }
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};
