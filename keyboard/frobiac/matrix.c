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


   Debounce code in matrix_scan() based on code from
        Peter Dannegger [danni/At/specs/d0t/de]
        described in German at bottom of page
            http://www.mikrocontroller.net/articles/Entprellung
        and discussed at
            http://www.mikrocontroller.net/topic/48465
   Array extensions inspired by Pult.zip
            http://www.mikrocontroller.net/topic/48465#1489399
   */

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"


#ifndef DEBOUNCE
#   define DEBOUNCE	10
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static uint16_t *matrix;
static uint16_t *matrix_debouncing;
static uint16_t matrix0[MATRIX_ROWS];
static uint16_t matrix1[MATRIX_ROWS];
static bool is_modified;

static uint16_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);


inline uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
    // initialize row and col
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    matrix = matrix0;
    matrix_debouncing = matrix1;
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
    is_modified = false;
}


/// debounce variables
volatile uint8_t kb_state[MATRIX_ROWS];    // debounced and inverted key state: bit = 1: key pressed
volatile uint8_t kb_press[MATRIX_ROWS];    // key press detect
volatile uint8_t kb_release[MATRIX_ROWS];  // key release detect
volatile uint8_t kb_rpt[MATRIX_ROWS];      // key long press and repeat

static uint8_t ct0[MATRIX_ROWS], ct1[MATRIX_ROWS];
static int32_t rpt[MATRIX_ROWS];

#define ALL_COLS_MASK ((1<<MATRIX_COLS)-1)  // 0x63 or all lower 6 bits
#define REPEAT_MASK    ALL_COLS_MASK // repeat: key0 = 0x3F = 63
#define REPEAT_START   31            // 61 = 1000ms
#define REPEAT_NEXT    15


uint8_t get_kb_release( uint8_t key_mask, uint8_t col)
{
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        key_mask &= kb_release[col];                      // read key(s)
        kb_release[col] ^= key_mask;                      // clear key(s)
    }
    return key_mask;
}

uint8_t get_kb_press( uint8_t key_mask, uint8_t col )
{
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        key_mask &= kb_press[col];                      // read key(s)
        kb_press[col] ^= key_mask;                      // clear key(s)
    }
    return key_mask;
}
uint8_t get_kb_rpt( uint8_t key_mask, uint8_t col )
{
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        key_mask &= kb_rpt[col];                        // read key(s)
        kb_rpt[col] ^= key_mask;                        // clear key(s)
    }
    return key_mask;
}

uint8_t matrix_scan(void)
{
    uint8_t i,data;
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        select_row(row);

        // Insert NOPs for synchronization
        _delay_us(20);

        // Place data on all column pins for active row
        // into a single 32 bit value.
        data = read_cols();
        /// @see top comment for source of debounce magic
        // Needs to be adjusted for more than 8 columns
        i = kb_state[row] ^ (~data);                    // key changed ?
        ct0[row] = ~( ct0[row] & i );                   // reset or count ct0
        ct1[row] = ct0[row] ^ (ct1[row] & i);           // reset or count ct1
        i &= ct0[row] & ct1[row];                       // count until roll over ?
        kb_state[row] ^= i;                             // then toggle debounced state

        kb_press  [row] |=  kb_state[row] & i;          // 0->1: key press detect
        kb_release[row] |= ~kb_state[row] & i;          // 1->0: key press detect
        /*
                if( (kb_state[row] & REPEAT_MASK) == 0 ) {      // check repeat function
                    rpt[row] = idle_count + REPEAT_START;       // start delay
                }
                if(  rpt[row] <= idle_count ) {
                    rpt[row] = idle_count + REPEAT_NEXT;        // repeat delay
                    kb_rpt[row] |= kb_state[row] & REPEAT_MASK;
                }
        */
        // Now evaluate results
        uint8_t p,r,h;
        p=get_kb_press  (ALL_COLS_MASK, row);
        h=get_kb_rpt    (ALL_COLS_MASK, row);
        r=get_kb_release(ALL_COLS_MASK, row);

        matrix[row] = ((matrix[row]|(p|h)) & ~r);
    }

    return 1;
}

bool matrix_is_modified(void)
{
    return is_modified;
}

inline bool matrix_has_ghost(void)
{
    return false;
}

inline bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

inline uint8_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

matrix_row_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop(matrix[i]);
    }
    return count;
}

/* Column pin configuration
 */
static void  init_cols(void)
{
    // teensy 2.0: 2&3 unused, F 01  4567
    // Columns are inputs
    DDRF  &= ((1<<2) | (1<<3)); // 192 or upper 2 bits
    // Enable pull-up resistors on inputs
    PORTF |= (0b11110011);
}

static uint16_t read_cols(void)
{

    uint8_t res = PINF;

#ifdef BLUECUBE
    return ( ~((1<<7)-1) | ( res & 0b11) | ((res & 0b11110000)>>2 ));
#elif defined HYPERNANO
    return ( ~((1<<7)-1) |
             ((res & 0b00000001) << 5) |
             ((res & 0b00000010) << 3) |
             ((res & 0b00010000) >> 1) |
             ((res & 0b00100000) >> 3) |
             ((res & 0b01000000) >> 5) |
             ((res & 0b10000000) >> 7)
           );
#endif
}


static void unselect_rows(void)
{
#ifdef BLUECUBE
    DDRD  &= 0b00001011;
    PORTD &= 0b00001011;
    DDRB  &= 0b10001111;
    PORTB &= 0b10001111;
#elif defined HYPERNANO
    DDRD  &= 0b00000000;
    PORTD &= 0b00000000;
#endif
}

static void select_row(uint8_t row)
{
    unselect_rows();

#if defined BLUECUBE
    // swap upper and lower ports to have left half first in matrix
    (row<4) ? (row+=4) : (row-=4);

    // B6 B5 B4 D7
    // D6 D4 D2 D5
    switch(row) {
        case 0: DDRB |= (1<<6); break;
        case 1: DDRB |= (1<<5); break;
        case 2: DDRB |= (1<<4); break;
        case 3: DDRD |= (1<<7); break;
        case 4: DDRD |= (1<<6); break;
        case 5: DDRD |= (1<<4); break;
        case 6: DDRD |= (1<<2); break;
        case 7: DDRD |= (1<<5); break;
    }
#elif defined HYPERNANO
    // Row 7 on pin 0
    DDRD |= (1<<(7-row));
#endif
}
