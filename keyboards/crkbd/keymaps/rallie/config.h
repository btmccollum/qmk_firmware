/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2019 Lucas Moreira

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

/* #define MASTER_LEFT */
#define MASTER_RIGHT
// #define EE_HANDS

//#define SSD1306OLED

#define USE_SERIAL_PD2

#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD
#define TAPPING_TERM 175
#undef PRODUCT
#define PRODUCT         CRKBD Loose Transistor Ed.

// Custom Font path
<<<<<<< HEAD
/* #define OLED_FONT_H "keyboards/crkbd/keymaps/kidbrazil/glcdfont.c" */
=======
#define OLED_FONT_H "keyboards/crkbd/keymaps/kidbrazil/glcdfont.c"
>>>>>>> 3d05d71c3a979200f475f37d041fda0e4780ed2a
#define OLED_DISABLE_TIMEOUT
