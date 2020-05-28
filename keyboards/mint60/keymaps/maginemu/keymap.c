/* Copyright 2018 Eucalyn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include "rgb.h"

#define BASE 0
#define FNK 1
#define SHIFTED_BASE 4
#define MOVE 8
#define EASY_NUMS 20
#define EASY_SYMBOLS 21


enum custom_keycodes {
  RGBRST = SAFE_RANGE
};


typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

//Tap dance enums
enum {
  DANCE_EASY_NUMS = 0,
  DANCE_EASY_SYMBOLS,
  SOME_OTHER_DANCE
};

int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void dance_nums_finished (qk_tap_dance_state_t *state, void *user_data);
void dance_nums_reset (qk_tap_dance_state_t *state, void *user_data);
void dance_symbols_finished (qk_tap_dance_state_t *state, void *user_data);
void dance_symbols_reset (qk_tap_dance_state_t *state, void *user_data);


  /* [BASIC] = LAYOUT( \ */
  /*   XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX, \ */
  /*   XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \ */
  /*   XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, \ */
  /*   _______,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, \ */
  /*   XXXXXXX,   _______,    _______,    _______,    XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX \ */
  /* ), */

  /* [TRANSP] = LAYOUT( \ */
  /*   _______,  _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,  _______,  _______, \ */
  /*   _______,    _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, \ */
  /*   _______,     _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,         _______, \ */
  /*   _______,       _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, \ */
  /*   _______,   _______,    _______,    _______,    _______,       _______, _______, _______,                   _______, _______, _______ \ */
  /* ), */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(                                                         \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,   KC_BSLS,  \
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,  \
    KC_LCTL,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,        KC_ENT,   \
    KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT, SFT_T(KC_SLSH),KC_RSFT, KC_UP,  MO(FNK), \
    KC_GRV,    KC_CAPS,    KC_LALT,    KC_LGUI,    KC_SPC,  TD(DANCE_EASY_SYMBOLS), TD(DANCE_EASY_NUMS),  KC_RGUI,KC_LEFT,KC_DOWN,KC_RGHT \
  ),
  [SHIFTED_BASE] = LAYOUT(                                                         \
    KC_ESC,  KC_EXLM,  KC_AT,  KC_HASH, KC_DLR, KC_PERC,     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS,   KC_PIPE,\
    S(KC_TAB), S(KC_Q),  S(KC_W),S(KC_E), S(KC_R), S(KC_T),    S(KC_Y), S(KC_U), S(KC_I),S(KC_O), S(KC_P), KC_LCBR, KC_RCBR, KC_BSPC, \
    S(KC_LCTL),  S(KC_A),  S(KC_S), S(KC_D),S(KC_F),S(KC_G),     S(KC_H), S(KC_J), S(KC_K),S(KC_L), KC_COLN, KC_DQUO,        S(KC_ENT),   \
    S(KC_LSFT),    S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B),    S(KC_N), S(KC_M), KC_LABK, KC_RABK, KC_QUES,KC_RSFT,S(KC_UP), _______, \
    KC_TILD,  S(KC_CAPS), S(KC_LALT), S(KC_LGUI), XXXXXXX,    XXXXXXX, XXXXXXX,  S(KC_RGUI),         S(KC_LEFT),S(KC_DOWN), S(KC_RGHT) \
  ),
  [FNK] = LAYOUT( \
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,    KC_DEL, \
    RGB_TOG,   RGBRST,  RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX,     RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, \
    _______,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_PGUP, _______, \
    XXXXXXX,   _______,    _______,    _______,    XXXXXXX,       XXXXXXX, XXXXXXX, _______,                   KC_HOME, KC_PGDN, KC_END \
  ),
  [EASY_NUMS] = LAYOUT( \
    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX, \
    XXXXXXX,    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,   KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, \
    XXXXXXX,     KC_1,     KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_MINS,           KC_EQL, \
    _______,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_LBRC, KC_RBRC, _______, _______, _______, _______, XXXXXXX, _______, \
    XXXXXXX,   _______,    _______,    _______,    KC_LSFT,       XXXXXXX, KC_RSFT, _______,                   XXXXXXX, XXXXXXX, XXXXXXX \
  ),
  [EASY_SYMBOLS] = LAYOUT( \
    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX, \
    XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX,     S(KC_1),     S(KC_2),    S(KC_3),    S(KC_4),    S(KC_5),  S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0),S(KC_MINS), S(KC_EQL), \
    _______,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   S(KC_LBRC), S(KC_RBRC), _______, _______, _______, _______, XXXXXXX, _______, \
    XXXXXXX,   _______,    _______,    _______,    KC_LSFT,       XXXXXXX, KC_RSFT, _______,                   XXXXXXX, XXXXXXX, XXXXXXX \
  ),
  [MOVE] = LAYOUT( \
    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX, \
    XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_ENT, XXXXXXX,         XXXXXXX, \
    _______,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, \
    XXXXXXX,   _______,    _______,    _______,    XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX \
  ),
  [30] = LAYOUT( \
    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX, \
    XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, \
    _______,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, \
    XXXXXXX,   _______,    _______,    _______,    XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX \
  ),
};



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;
    default:
      break;
  }
  return true;
}

//
// ------------- LED Light Implementation -------------
//

// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_SPRINGGREEN}
);

const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
     {0, 1, HSV_GOLD}
);

const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_PINK}
);

const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_MAGENTA}
);



// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer0_layer,
    my_layer1_layer,
    my_layer2_layer,
    my_layer3_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(0, layer_state_cmp(state, FNK));
    rgblight_set_layer_state(1, layer_state_cmp(state, MOVE));
    rgblight_set_layer_state(2, layer_state_cmp(state, EASY_NUMS));
    rgblight_set_layer_state(3, layer_state_cmp(state, EASY_SYMBOLS));
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

//
// ------------- Tap Dance Implementation -------------
//

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not tquickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

int cur_dance_ignore_interrupted (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not tquickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (!state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap dance_nums_state = {
  .is_press_action = true,
  .state = 0
};

void dance_nums_finished (qk_tap_dance_state_t *state, void *user_data) {
  dance_nums_state.state = cur_dance_ignore_interrupted(state);
  switch (dance_nums_state.state) {
    case SINGLE_TAP: register_code(KC_SPC); break;
    case SINGLE_HOLD: layer_on(EASY_NUMS); break;
    case DOUBLE_TAP: register_mods(MOD_BIT(KC_LSFT));register_code(KC_SLSH); break;
    case DOUBLE_HOLD: register_code(KC_LSFT); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_SPC); unregister_code(KC_SPC); register_code(KC_SPC);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void dance_nums_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (dance_nums_state.state) {
    case SINGLE_TAP: unregister_code(KC_SPC); break;
    case SINGLE_HOLD: layer_off(EASY_NUMS); break;
    case DOUBLE_TAP: unregister_mods(MOD_BIT(KC_LSFT)); unregister_code(KC_SLSH); break;
    case DOUBLE_HOLD: unregister_code(KC_LSFT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_SPC);
  }
  dance_nums_state.state = 0;
}

static tap dance_symbols_state = {
  .is_press_action = true,
  .state = 0
};

void dance_symbols_finished (qk_tap_dance_state_t *state, void *user_data) {
  dance_symbols_state.state = cur_dance_ignore_interrupted(state);
  switch (dance_symbols_state.state) {
    case SINGLE_TAP: register_code(KC_GRV); break;
    case SINGLE_HOLD: layer_on(EASY_SYMBOLS); break;
    case DOUBLE_TAP: register_code(KC_BSLS); break;
    case DOUBLE_HOLD: layer_on(MOVE); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_GRV); unregister_code(KC_GRV); register_code(KC_GRV);
    case TRIPLE_TAP: register_code(KC_GRV); unregister_code(KC_GRV); register_code(KC_GRV);unregister_code(KC_GRV); register_code(KC_GRV);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void dance_symbols_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (dance_symbols_state.state) {
    case SINGLE_TAP: unregister_code(KC_GRV); break;
    case SINGLE_HOLD: layer_off(EASY_SYMBOLS); break;
    case DOUBLE_TAP: unregister_code(KC_BSLS); break;
    case DOUBLE_HOLD: layer_off(MOVE);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_GRV);
    case TRIPLE_TAP: unregister_code(KC_GRV);
  }
  dance_symbols_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [DANCE_EASY_NUMS]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,dance_nums_finished, dance_nums_reset),
  [DANCE_EASY_SYMBOLS]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,dance_symbols_finished, dance_symbols_reset)
};
