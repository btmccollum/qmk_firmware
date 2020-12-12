/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#include <stdio.h>
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

char wpm_str[10];

enum layers {
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
    Qwerty = SAFE_RANGE,
    Colemak
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | TAB |   Q  |   W  |   E  |   R  |   T     |                              |   Y  |   U  |   I  |   O  |   P  |  BKSP  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | CTRL/ESC|   A  |   S  |  D   |   F  |   G |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   | 
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LSFT/(  |   Z  |   X  |   C  |   V  |   B |      |  DEL |  | CAPS |      |   N  |   M  | ,  < | . >  | /  ? |  RSFT/)|
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | MPlay| GUI  | lower|      | BKSP |  | SWAP | enter| Raise| alt  | WKSPC |
 *                        |      |      |      |  spc |      |  |      |      |      |      | TOGGLE|
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
      KC_TAB,    KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,                                                   KC_Y,    KC_U,    KC_I,    KC_O,       KC_P, KC_BSPC,
      MT(MOD_LCTL, KC_ESC),    KC_A,    KC_S,   KC_D,   KC_F,   KC_G,                                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSPO,   KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,  _______,  KC_DEL,        KC_CAPS, _______,    KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
                           KC_MPLY, KC_LGUI, MO(_LOWER), KC_SPC,  KC_BSPC,       SH_MON, KC_ENT, MO(_RAISE),  KC_RALT, LGUI(KC_B)
    ),
/*
 * Base Layer: Colemak
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   TAB  |   Q  |   W  |   F  |   P  |   G  |                              |   J  |   L  |   U  |   Y  | ;  : |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   NAV  |   A  |   R  |  S   |   T  |   D  |                              |   H  |   N  |   E  |   I  |   O  |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | spc  | DEL  |  |      | CAPS |   K  |   M  | ,  < | . >  | /  ? |  Del   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | MPlay | GUI  |lower| spc  | BKSP |  | BKSP | ENTR | SYMB | NAV  |LEADER|
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_COLEMAK] = LAYOUT(
      KC_TAB  , KC_Q ,  KC_W   ,  KC_F  ,   KC_P ,   KC_G ,                                                  KC_J,   KC_L ,  KC_U ,   KC_Y ,KC_SCLN, KC_BSPC,
      MT(MOD_LCTL, KC_ESC), KC_A ,  KC_R   ,  KC_S  ,   KC_T ,   KC_D ,                                      KC_H,   KC_N ,  KC_E ,   KC_I ,  KC_O , KC_QUOT,
      KC_LSPO , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B ,    KC_SPC,   KC_DEL,       _______, KC_CAPS, KC_K,  KC_M, KC_COMM, KC_DOT ,KC_SLSH, KC_RSPC,
                                 KC_MPLY, KC_LGUI, MO(_LOWER), KC_SPC,  KC_BSPC,       KC_BSPC, KC_ENT, MO(_RAISE),  KC_RALT, LGUI(KC_B)
    ),
/*
 * Lower Layer: numpad and arrow
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   *  |   7  |   8  |  9   |  -   |                              |      |      |      |      |      |   Del
   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |   /  |   4  |   5  |  6   |  +   |                              | LEFT | DOWN |   UP | Right|      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | P-ENT  |   =  |   1  |  2   |  3   |  .   |      | TAB  |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | MUTE |  0   |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
     [_LOWER] = LAYOUT(
        _______, KC_PAST,    KC_7,    KC_8,    KC_9,  KC_PMNS,                                            _______, _______,  _______, _______, _______,  KC_DEL,
        _______, KC_PSLS,    KC_4,    KC_5,    KC_6,  KC_PPLS,                                            KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______,
        KC_PENT,  KC_EQL,    KC_1,    KC_2,    KC_3,   KC_DOT, KC_TRNS,   KC_TAB,     _______, _______, _______, _______, _______, _______, _______, _______,
                                   KC_MUTE,    KC_0,  _______, KC_TRNS,  _______,     KC_TRNS, KC_TRNS, _______, _______, _______
    ),
/*
 * Raise Layer: F keys and media
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   !  |  @   |  #   |  $   |   %  |                              |  ^  |   &  |   *   |   (  |   )  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |   {  |                              |  }   |  -   |  =   |      |   |  |   `    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |   [  |      |      |  |      |      |  ]   |  _   |  +   |      |   /  |   ~    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_RAISE] = LAYOUT(
      _______, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                                          KC_CIRC,  KC_AMPR,  KC_ASTR, KC_LPRN, KC_RPRN, _______,
      _______, _______, _______, _______, _______, KC_LCBR,                                       KC_RCBR,   KC_MINS,   KC_EQL,  _______, KC_PIPE, KC_GRV,
      KC_TRNS, _______, _______, _______, _______, KC_LBRC, _______, _______, _______, _______,   KC_RBRC,   KC_UNDS,   KC_PLUS, _______, KC_BSLS, KC_TILD,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_TRNS
    ),
/*
 * Adjust Layer: Function keys, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | F1   |  F2  | F3   | F4   | F5   |                              | F6   | F7   |  F8  | F9   | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |RGB  TOG| VAI  | SAI  | HUI  | SPI  | MOD  |                              |      |      |      | F11  | F12  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | VAD  | SAD  | HUD  | SPD  | RMOD |      |      |  |      |      |      |      |      |      |qwerty| colemak|
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      RGB_TOG, RGB_VAI, RGB_SAI, RGB_HUI, RGB_SPI, RGB_MOD,                                     _______, _______, _______, KC_F11,  KC_F12,  _______,
      _______, RGB_VAD, RGB_SAD, RGB_HUD, RGB_SPD, RGB_RMOD,_______, _______, _______, _______, _______, _______, _______, _______, Qwerty, Colemak,
                                 KC_TRNS, _______, _______, _______, _______, _______, _______,  KC_TRNS, _______, _______
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case Qwerty:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            break;
        case Colemak:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            break;
    }
    return true;
};

#ifdef OLED_DRIVER_ENABLE

void suspend_power_down_user() {
    oled_clear();
    oled_off();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

// clang-format off
static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

    oled_write_P(qmk_logo, false);
}
// clang-format on

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.3\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("QWERTY"), false);
            break;
        case _COLEMAK:
            oled_write_P(PSTR("COLEMAK"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Numpad"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Symbols"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("RGB-FN"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined"), false);
    }

    //Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("       "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS ") : PSTR("       "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCRL") : PSTR("       "), false);
}


void oled_task_user(void) {
    if (is_keyboard_master()) {
        // Renders the current keyboard state (layer, lock, caps, scroll, etc)
        render_status();
        oled_set_cursor(0,6);
        sprintf(wpm_str, "       WPM: %03d", get_current_wpm());
        oled_write(wpm_str, false);
    } else {
        render_kyria_logo();
    }
}
#endif

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (biton32(layer_state)) {
            case _LOWER:
                // Skip/Prev song
                if (clockwise) {
                    tap_code(KC_MNXT);
                } else {
                    tap_code(KC_MPRV);
                }
                break;
            default:
                // Volume control
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
        }
    } else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case _RAISE:
                // Credit to Thomas Baart for this
                // See https://docs.splitkb.com/hc/en-us/articles/360010513760-How-can-I-use-a-rotary-encoder-
                if (clockwise) {
                    tap_code16(C(KC_TAB));
                } else {
                    tap_code16(S(C(KC_TAB)));
                }
                break;
            default:
                // Scrolling
                if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
                break;
        }

    }
}
#endif
