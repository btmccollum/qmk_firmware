#include QMK_KEYBOARD_H
#include "enums.h"

// Render Blank Space
void render_space(void) {
    oled_write_ln_P(PSTR("     "), false);
}

// Render separator lines for oled display
void render_separator(void) {
    switch (get_highest_layer(layer_state)){
        case _GAME:
        case _WEAPON:
            oled_write_ln_P(PSTR("===================="), false);
            break;
        default:
            oled_write_ln_P(PSTR("++++++++++++++++++++"), false);
    }
}

// Render current layer state
void render_layer_state(void){
	// If you want to change the display of OLED, you need to change here
    switch (get_highest_layer(layer_state)){
        case _QWERTY:
<<<<<<< HEAD
            oled_write_ln_P(PSTR("| MODE | QWERTY    |"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("| MODE | NUMS-NAV  |"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("| MODE | SYMS      |"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("| MODE | MSE-MED   |"), false);
            break;
        case _GAME:
            oled_write_ln_P(PSTR("|    G  A  M  E    |"), false);
            break;
        case _WEAPON:
            oled_write_ln_P(PSTR("| W  E  A  P  O  N |"), false);
            break;
        default:
            oled_write_ln_P(PSTR("| MODE | UNDEF     |"), false);
=======
            oled_write_ln_P(PSTR("| MODE | QWRTY     ]"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("| MODE | NUMS-NAV  ]"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("| MODE | SYMS      ]"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("| MODE | MSE-MED   ]"), false);
            break;
        case _GAME:
            oled_write_ln_P(PSTR("|    G  A  M  E    ]"), false);
            break;
        case _WEAPON:
            oled_write_ln_P(PSTR("| W  E  A  P  O  N ]"), false);
            break;
        default:
            oled_write_ln_P(PSTR("| MODE | UNDEF     ]"), false);
>>>>>>> 3d05d71c3a979200f475f37d041fda0e4780ed2a
    }
}

// Render USB State
void render_usb_state(void) {
    switch (USB_DeviceState) {
      case DEVICE_STATE_Unattached:
<<<<<<< HEAD
			    oled_write_ln_P(PSTR("| USB  | FREE      |"), false);
          break;
      case DEVICE_STATE_Suspended:
          oled_write_ln_P(PSTR("| USB  | SLEEP     |"), false);
          break;
      case DEVICE_STATE_Configured:
          oled_write_ln_P(PSTR("| USB  | READY     |"), false);
          break;
      case DEVICE_STATE_Powered:
          oled_write_ln_P(PSTR("| USB  | PWRD      |"), false);
          break;
      case DEVICE_STATE_Default:
          oled_write_ln_P(PSTR("| USB  | DFLT      |"), false);
          break;
      case DEVICE_STATE_Addressed:
          oled_write_ln_P(PSTR("| USB  | ADDRS     |"), false);
          break;
      default:
          oled_write_ln_P(PSTR("| USB  | INVALID   |"), false);
=======
			    oled_write_ln_P(PSTR("| USB  | FREE      ]"), false);
          break;
      case DEVICE_STATE_Suspended:
          oled_write_ln_P(PSTR("| USB  | SLEEP     ]"), false);
          break;
      case DEVICE_STATE_Configured:
          oled_write_ln_P(PSTR("| USB  | READY     ]"), false);
          break;
      case DEVICE_STATE_Powered:
          oled_write_ln_P(PSTR("| USB  | PWRD      ]"), false);
          break;
      case DEVICE_STATE_Default:
          oled_write_ln_P(PSTR("| USB  | DFLT      ]"), false);
          break;
      case DEVICE_STATE_Addressed:
          oled_write_ln_P(PSTR("| USB  | ADDRS     ]"), false);
          break;
      default:
          oled_write_ln_P(PSTR("| USB  | INVALID   ]"), false);
>>>>>>> 3d05d71c3a979200f475f37d041fda0e4780ed2a
    }
}
