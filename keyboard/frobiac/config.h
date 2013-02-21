/*
Copyright 2013 Stefan Fröbe, <frobiac /at/ gmail [d0t] com>

Based on tmk_firmware code by
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#ifndef CONFIG_H
#define CONFIG_H

/* controller configuration */
// #include "controller_teensy.h"

/* Keyboard model: HYPERNANO or BLUECUBE
 * This is set as additional makefile argument
 */
#if defined (HYPERNANO)
#    define PRODUCT HyperNano
#elif defined (BLUECUBE)
#    define PRODUCT BlueCube
#else
#    error No kb type defined
#endif


/* USB Device descriptor parameter */
#warning Define_your_own_descriptor
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    frobiac
#define PRODUCT         HyperNano


#define DESCRIPTION     AdNW


/* matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6


/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if need no debouncing */
#define DEBOUNCE    5

/*
 * Boot magic keys
 * call some function by pressing key when pluging cable or powering on.
 */
/* key position on matrix(ROW:COL) */

#define KEY_FN          0x05
#define KEY_D           0x40
#define KEY_IS_ON(key)  matrix_is_on((key)>>4, (key)&0xF)
// kick up bootloader
#define IS_BOOTMAGIC_BOOTLOADER()       KEY_IS_ON(KEY_FN)
// debug on
#define IS_BOOTMAGIC_DEBUG()            KEY_IS_ON(KEY_D)


/* key combination for command */
#define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_LALT)))

/* mouse keys */
#ifdef MOUSEKEY_ENABLE
#   define MOUSEKEY_DELAY_TIME 100
#endif

/* period of tapping(ms) */
#define TAPPING_TERM    200
/* tap count needed for toggling a feature */
#define TAPPING_TOGGLE  2

/* PS/2 mouse */
#ifdef PS2_MOUSE_ENABLE

#   define PS2_CLOCK_PORT  PORTE
#   define PS2_CLOCK_PIN   PINE
#   define PS2_CLOCK_DDR   DDRE
#   define PS2_CLOCK_BIT   6
#   define PS2_DATA_PORT   PORTB
#   define PS2_DATA_PIN    PINB
#   define PS2_DATA_DDR    DDRB
#   define PS2_DATA_BIT    7

#endif

#endif
