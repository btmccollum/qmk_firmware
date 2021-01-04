#pragma once

/* Select hand configuration */

// #define MASTER_LEFT
#define MASTER_RIGHT
// #define EE_HANDS

#define SPLIT_USB_DETECT

#undef USE_I2C
#undef SSD1306OLED

#define USE_SERIAL_PD2

#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD
#define TAPPING_TERM 225

#define NO_ACTION_ONESHOT

#define OLED_FONT_H "keyboards/crkbd/keymaps/gotham/glcdfont.c"
