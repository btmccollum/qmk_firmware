#include QMK_KEYBOARD_H
#include "keycodes.h"

#ifdef OLED_DRIVER_ENABLE
#    include "oled.c"
#endif

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#    include "rgb.c"
#endif

// clang-format off
/* const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { */
/*   [_QWERTY] = LAYOUT( */
/*   //|-----------------------------------------------------|                    |-----------------------------------------------------| */
/*      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, */
/*   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
/*      SFT_EQ,  SFT_A,   KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    SFT_SCLN,SFT_QT, */
/*   //---------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
/*      KC_LCTL, CTL_Z,   KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  CTL_SLSH,ADJ_GRV, */
/*   //---------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------| */
/*                                          KC_LALT, LOW_SPC, RAI_EQ,     RAI_ENT, LOW_BSP, KC_LGUI */
/*                                       //|--------------------------|  |--------------------------| */


/*   ), */

/*   [_LOWER] = LAYOUT( */
/*   //|-----------------------------------------------------|                    |-----------------------------------------------------| */
/*      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, */
/*   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
/*      _______, KC_ANGL, KC_ANGR, KC_LPRN, KC_RPRN, KC_PGUP,                      KC_MINS, KC_LEFT, KC_UP,   KC_RIGHT,KC_PLUS, _______, */
/*   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
/*      _______, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_PGDOWN,                    KC_UNDS, KC_HOME, KC_DOWN, KC_END,  XXXXXXX, _______, */
/*   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------| */
/*                                          _______, _______, _______,    _______, LOW_DEL, _______ */
/*                                       //|--------------------------|  |--------------------------| */
/*   ), */

/*   [_RAISE] = LAYOUT( */
/*   //|-----------------------------------------------------|                    |-----------------------------------------------------| */
/*      KC_ESC,  KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, XXXXXXX,                      XXXXXXX, KC_AMPR, KC_PIPE, KC_EXLM, KC_ASTR, XXXXXXX, */
/*   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
/*      _______, KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, XXXXXXX,                      XXXXXXX, KC_UNDS, KC_EQL,  KC_ANGL, KC_ANGR, XXXXXXX, */
/*   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
/*      _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, XXXXXXX,                      XXXXXXX, KC_MINS, KC_PLUS, XXXXXXX, KC_BSLS, _______, */
/*   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------| */
/*                                           _______, _______, _______,    _______, _______, _______ */
/*                                       //|--------------------------|  |--------------------------| */
/*   ), */

/*   [_ADJUST] = LAYOUT( */
/*   //|-----------------------------------------------------|                    |-----------------------------------------------------| */
/*      XXXXXXX, CK_RST,  CK_DOWN, CK_UP,   CK_TOGG, RGB_TOG,                       MU_TOG, KC_F12,  KC_F7,   KC_F8,   KC_F9,   XXXXXXX,\ */
/*   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
/*      XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_MOD,                       MU_MOD, KC_F11,  KC_F4,   KC_F5,   KC_F6,   RESET,  \ */
/*   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
/*      XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, RGBRST,                        AU_TOG, KC_F10,  KC_F1,   KC_F2,   KC_F3,   _______,\ */
/*   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------| */
/*                                          _______, _______, _______,    _______, KC_VOLD, KC_VOLU \ */
/*                                       //|--------------------------|  |--------------------------| */
/*   ) */
/* }; */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      MT(MOD_LCTL, KC_ESC),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSPO,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSPC,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER,  KC_SPC,     KC_ENT,  RAISE,  KC_RALT \
                                      //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER,  KC_SPC,     KC_ENT,   RAISE, KC_RALT \
                                      //`--------------------------'  `--------------------------'
    ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LCBR,                      KC_RCBR, KC_MINS,  KC_EQL, XXXXXXX, KC_PIPE,  KC_GRV,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC,                      KC_RBRC, KC_UNDS, KC_PLUS, XXXXXXX, KC_BSLS, KC_TILD,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER,  KC_SPC,     KC_ENT,   RAISE, KC_RALT \
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX, KC_WHOM, KC_WREF, KC_WBAK,                      XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY, KC_VOLD, KC_VOLU,                      XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BRIU, KC_BRID, XXXXXXX, XXXXXXX, KC_MRWD, KC_MFFD,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER,  KC_SPC,     KC_ENT,   RAISE, KC_RALT \
                                      //`--------------------------'  `--------------------------'
  )
};
// clang-format off

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    return state;
}
/* #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE) */
/* layer_state_t layer_state_set_user(layer_state_t state) { */
/*     /1* For any layer other than default, save current RGB state and switch to layer-based RGB *1/ */
/*     if (layer_state_cmp(state, 0)) { */
/*         restore_rgb_config(); */
/*     } else { */
/*         uint8_t layer = get_highest_layer(state); */
/*         if (layer_state_cmp(layer_state, 0)) save_rgb_config(); */
/*         rgb_by_layer(layer); */
/*     } */
/*     return state; */
/* } */
/* #endif */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_DRIVER_ENABLE
    if (record->event.pressed) {
        oled_timer = timer_read();
        add_keylog(keycode);
    }
#endif

    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
            }
            return false;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            return false;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
        case RGB_MOD:
        case RGB_TOG:
        case RGB_HUI:
        case RGB_HUD:
        case RGB_SAI:
        case RGB_SAD:
        case RGB_VAI:
        case RGB_VAD:
        case RGB_SPI:
        case RGB_SPD:
            /* Override layer-based RGB and resume RGB effect to be able to preview changes */
            if (record->event.pressed) {
                restore_rgb_config();
                process_rgb(keycode, record);
                save_rgb_config();
            }
            return false;
        case RGBRST:
            if (record->event.pressed) {
#    ifdef RGBLIGHT_ENABLE
                eeconfig_update_rgblight_default();
                rgblight_enable();
#    elif RGB_MATRIX_ENABLE
                eeconfig_update_rgb_matrix_default();
                rgb_matrix_enable();
#    endif
                save_rgb_config();
            }
            return false;
#endif
    }
    return true;
}
