#include QMK_KEYBOARD_H
#include "enums.h"
#include "layer.h"

// [Init Variables] ----------------------------------------------------------//
extern uint8_t is_master;
// Oled timer similar to Drashna's
static uint32_t oled_timer = 0;
// Boolean to store LED state
bool user_led_enabled = true;
// Boolean to store the master LED clear so it only runs once.
bool master_oled_cleared = false;

// Tap Dance declarations
enum {
    TD_LRCBR, TD_LRBRC, TD_LRBK
};

  // Tap once for left curly brace ({), twice for right
  // Tap once for left bracket ([), twice for right
  // Tap once for left angle bracket (<), twice for right
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LRCBR] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
  [TD_LRBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
  [TD_LRBK] = ACTION_TAP_DANCE_DOUBLE(KC_LT, KC_GT),
};

// [Keymaps] -----------------------------------------------------------------//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      MT(MOD_LCTL, KC_ESC),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSPO,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSPC,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(_LOWER),  KC_SPC,     KC_ENT, MO(_RAISE),  KC_RALT \
                                      //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, XXXXXXX,    KC_7,    KC_8,    KC_9,    KC_0,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX,    KC_4,    KC_5,    KC_6, KC_PPLS,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX,    KC_1,    KC_2,    KC_3, KC_PENT,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_TRNS,  KC_SPC,     KC_ENT,  MO(_ADJUST), _______ \
                                      //`--------------------------'  `--------------------------'
    ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, XXXXXXX, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX,  KC_DLR, KC_PERC, KC_CIRC, _______,                     TD(TD_LRCBR), KC_MINS,  KC_EQL, TD(TD_LRBK), KC_PIPE,  KC_GRV,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, KC_EXLM,   KC_AT, KC_HASH, _______,                     TD(TD_LRBRC), KC_UNDS, KC_PLUS, XXXXXXX, KC_BSLS, KC_TILD,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, MO(_ADJUST),  KC_SPC,     KC_ENT, KC_TRNS, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX, KC_WHOM, KC_WREF, KC_WBAK,                      XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY, KC_VOLD, KC_VOLU,                      XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BRIU, KC_BRID, XXXXXXX, XXXXXXX, KC_MRWD, KC_MFFD,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_TRNS, TG(_GAME),\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,  KC_TRNS,  KC_SPC,     KC_ENT, KC_TRNS, _______ \
                                      //`--------------------------'  `--------------------------'
  ),
  [_GAME] = LAYOUT(
    KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T,                                   KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
    KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G,                                  KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, KC_NO,
    KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B,                               KC_PGUP, KC_PGDN, KC_NO, KC_NO, KC_NO, KC_TRNS,
                          KC_TAB, MO(_WEAPON), KC_SPC,              KC_ENT, KC_TRNS, KC_NO
    ),

  [_WEAPON] = LAYOUT(
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_LSFT, KC_A, KC_S, KC_D, KC_F,                               KC_6, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_LCTL, KC_Z, KC_X, KC_C, KC_V,                               KC_7, KC_TRNS, KC_TRNS, KC_TRNS, MO(_ADJUST), KC_TRNS,
                              KC_TRNS, KC_TAB, KC_TRNS,             KC_SPC, KC_TRNS, KC_TRNS
  )
};

// [Process User Input] ------------------------------------------------------//
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      default:
          // Use process_record_keymap to reset timer on all other keypresses to awaken from idle.
          if (record->event.pressed) {
              #ifdef OLED_DRIVER_ENABLE
                  oled_timer = timer_read32();
              #endif
          }
          return true;
    }
}

// [Matrix Scan] ------------------------------------------------------------//
void matrix_scan_user(void) {
     // Idle timer to return to default layer if left on game layer
     if (timer_elapsed32(oled_timer) > 380000 && timer_elapsed32(oled_timer) < 479999) {
         // Reset layer in case it got left on _GAME
         // This prevents the issue where the master side sometimes wont switch off as expected
         // in the next step.
         if (get_highest_layer(layer_state) == _GAME) {
             layer_off(_GAME);
             layer_on(_QWERTY);
         }
         return;
     }
}
// [OLED Configuration] ------------------------------------------------------//
#ifdef OLED_DRIVER_ENABLE
// Init Oled and Rotate....
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!has_usb())
      return OLED_ROTATION_180;  // flips the display 180 to see it from my side
    return rotation;
}

// Read logo from font file
const char *read_logo(void);

// {OLED helpers} -----------------------------------------------//
// Render Logo
void render_logo(void) {
    oled_write(read_logo(), false);
}

// Master OLED Screen (Right Hand )
void render_master_oled(void) {
    // Switch display based on Layer
    switch (get_highest_layer(layer_state)){
        case _GAME:
            render_separator();
            render_layer_state();
            render_separator();
            render_separator();
            break;
        case _WEAPON:
            render_separator();
            render_separator();
            render_layer_state();
            render_separator();
            break;
        default:
            render_separator();
            render_layer_state();
            render_separator();
            render_usb_state();
    }
}

// Slave OLED scren (Left Hand)
void render_slave_oled(void) {
    render_logo();
}

// {OLED Task} -----------------------------------------------//
void oled_task_user(void) {
    // First time out switches to logo as first indication of iddle.
    if (timer_elapsed32(oled_timer) > 100000 && timer_elapsed32(oled_timer) < 479999) {
        // Render logo on both halves before full timeout
        if (is_master && !master_oled_cleared) {
            // Clear master OLED once so the logo renders properly
            oled_clear();
            master_oled_cleared = true;
        }
        render_logo();
        return;
    }
    // Drashna style timeout for LED and OLED Roughly 8mins
    else if (timer_elapsed32(oled_timer) > 300000) {
        oled_off();
        return;
    }
    else {
        oled_on();
        // Reset OLED Clear flag
        master_oled_cleared = false;
        // Show logo when USB dormant
        switch (USB_DeviceState) {
            case DEVICE_STATE_Unattached:
            case DEVICE_STATE_Powered:
            case DEVICE_STATE_Suspended:
                render_logo();
                break;
            default:
                if (is_master) {
                    render_master_oled();
                } else {
                    render_slave_oled();
                }
        }
    }
}
#endif
