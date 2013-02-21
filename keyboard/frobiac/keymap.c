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

/*
 * Keymap for frobiacs custom keyboards using modified AdNW layout
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"

#if defined (BLUECUBE)
#define KEYMAP( \
      K00, K01, K02, K03, K04, K05, K10, K11, K12, K13, K14, K15, \
      K20, K21, K22, K23, K24, K25, K30, K31, K32, K33, K34, K35, \
      K40, K41, K42, K43, K44, K45, K50, K51, K52, K53, K54, K55, \
 N30, K60, K61, K62, K63, K64, K65, K70, K71, K72, K73, K74, K75, N76 \
) \
{ \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05}, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25}, \
    { KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45}, \
    { KC_##K65, KC_##K64, KC_##K60, KC_##K61, KC_##K62, KC_##K63}, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15}, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35}, \
    { KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55}, \
    { KC_##K72, KC_##K73, KC_##K74, KC_##K75, KC_##K71, KC_##K70} \
}

#elif defined(HYPERNANO)

#define KEYMAP( \
  N00,K01,K02,K03,K04,K05,        K40,K41,K42,K43,K44,N45, \
  N10,K11,K12,K13,K14,K15,        K50,K51,K52,K53,K54,N55, \
  N20,K21,K22,K23,K24,K25,        K60,K61,K62,K63,K64,N65, \
  T30,T31,T32,T33,T34,T35,T20,T65,T70,T71,T72,T73,T74,T75  \
) { \
  {  KC_0,     KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05 },\
  {  KC_0,     KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15 },\
  {  KC_##T20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25 },\
  {  KC_##T35, KC_##N20, KC_##T31, KC_##T32, KC_##T33, KC_##T34 },\
\
  {  KC_0,     KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44 },\
  {  KC_0,     KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54 },\
  {  KC_##T65, KC_##K60, KC_##K61, KC_##K62, KC_##K63, KC_##K64 },\
  {  KC_##T70, KC_##T71, KC_##T72, KC_##T73, KC_##T74, KC_##N65 } \
}
#else
#   error Specify Keyboard Type (bluecube or hypernaN) on command line.
#endif

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/** Common thumb-row for all layers:
 *  
 *  Keycodes if tapped
 *             .    .              
 *   . . . ⇥ ␣ .    ⎋ ⌫ ⏎ . . .
 *
 *  Modifiers is held with other key:
 *             0    4
 *   . S A C ␣ G    3 S 2 A . .
 */


/** Layer 0: (lowercase char)
 *
 *     k u q . j    v g c l f
 *     h i e a o    d t r n s
 *     x y - , /    b p w m z
 */
 KEYMAP( \
    ESC, K,   U,   Q,   DOT, J,      V,   G,   C,   L,   F,   BSPC,  \
    TAB, H,   I,   E,   A,   O,      D,   T,   R,   N,   S,   ENT,   \
    LSFT,X,   Z,   SLSH,COMM,PSLS,   B  , P,   W,   M,   Y,   NO,    \
  0,LSFT,LALT,FN6 ,SPC, LGUI,FN0,    FN4, FN3, FN5,FN2,RALT,  FN4,  C  ),

/** Layer 1: (uppercase) Not used currently, as it is just shifted layer 0
 *
 *    K U Q : J    V G C L F
 *    H I E A O    D T R N S
 *    X Y _ ; /    B P W M Z
 */
  KEYMAP( \
    ESC, K,   U,   Q,   DOT, J,      V,   G,   C,   L,   F,   BSPC,  \
    TAB, H,   I,   E,   A,   O,      D,   T,   R,   N,   S,   ENT,   \
    LSFT,X,   Z,   SLSH,COMM,PSLS,   B  , P,   W,   M,   Y,   NO,    \
  0,LSFT,LALT,FN6 ,SPC, LGUI,FN0,    FN4, FN3, FN5,FN2,RALT,  FN4,  C  ),

/** Layer 2: (symbol)
 *
 *    @ € [ ] #    ! < > = &    See special note on QWERTZ remapping in README
 *    \   { } *    ? ( ) +      or FNxx definitions below
 *      $ | ~ `    ^ % " '
 */
  KEYMAP( \
    NO,  FN23,FN24,FN28,FN29,NUHS,   FN11,NUBS,FN13,PEQL,FN16,NO,    \
    NO,  FN26,NO,  FN27,FN20,PAST,   FN17,FN18,FN19,PPLS,NO,  NO,    \
    NO,  NO,  FN14,FN22,FN21,FN25,   GRV, FN15,FN12,FN10,NO,  NO,    \
  0,LSFT,LALT,FN6 ,SPC, LGUI,FN0,    FN4, FN3, FN5, FN2, RALT,FN4,  C  ),

/** Layer 3: (navigation & numbers)
 *
 *    ⇞ ⌫ ↑ ⌦ ⇟    ß 7 8 9 ä
 *    « ← ↓ → »    . 4 5 6 ö
 *    ⎋ ⇥ i ⏎      0 1 2 3 ü
 */
  KEYMAP( \
    TAB, PGUP,BSPC,UP,  DEL, PGDN,   MINS,7,   8,   9,   QUOT,BSPC,  \
    LCTL,HOME,LEFT,DOWN,RGHT,END,    DOT, 4,   5,   6,   SCLN,ENT,   \
    LSFT,ESC, TAB, INS, ENT, NO,     0,   1,   2,   3,   LBRC,NO,    \
  0,LSFT,LALT,FN6 ,SPC, LGUI,FN0,    FN4, FN3, FN5, FN2, RALT,FN4,  C  ),

/** Layer 4: (mouse keys)
 *
 *
 *
 *
 */
  KEYMAP( \
    ESC, VOLU,  WH_U,MS_U,WH_D,NO,   NO,  NO,  NO,  NO,  NO,  NO,    \
    TAB, VOLD,  MS_L,MS_D,MS_R,NO,   BTN5,BTN1,BTN2,BTN3,BTN4,NO,    \
    TAB, MUTE,  WH_L,NO  ,WH_R,NO,   NO,  ACL0,ACL1,ACL2,NO,  NO,    \
  0,LSFT,LALT,FN6 ,SPC, LGUI,FN0,    FN4, FN3, FN5, FN2, RALT,FN4,  C  ),
};


/* id for user defined functions */
enum function_id {
    LSHIFT_LPAREN,
    RSHIFT_RPAREN,
    QWERTZ,
    MACRO                   = 0xff
};



/*
 * Fn action definition
 */
// TODO: use [1] = KEYMAP(...) to prevent from changing index of element?
static const uint16_t PROGMEM fn_actions[] = {
    ACTION_LAYER_DEFAULT,                           // FN0 = L0 default
    ACTION_LAYER_SET(1),                            // FN1      not used due to shift/backspace FN5 below
    ACTION_LAYER_SET_TAP_KEY(2, KC_ENT),            // FN2 = L2 programming
    ACTION_LAYER_SET_TAP_KEY(3, KC_ESC),            // FN3 = L3 navigtion
    ACTION_LAYER_SET(4),                            // FN4 = L4 mouse
    ACTION_RMOD_TAP_KEY(KC_RSFT, KC_BSPC),          // FN5 = L1  Shift with tap Backspace
    ACTION_RMOD_TAP_KEY(KC_RCTL, KC_TAB),           // FN6 Ctrl  with tap Tab

/// FN7 - FN9 dummy free for testing
    // ACTION_LAYER_SET(0),                            // FN7
    // ACTION_LAYER_SET(0),                            // FN8
    // ACTION_LAYER_SET(0),                            // FN9
    ACTION_FUNCTION_TAP(QWERTZ),                    // FN7
    ACTION_FUNCTION_TAP(RSHIFT_RPAREN),             // FN8
    ACTION_FUNCTION(MACRO, 0),                      // FN9 Macro:

/// FN10..19: Shifted special chars on Qwertz
    ACTION_RMOD_KEY(KC_RSFT, KC_NUHS), // Shift+# = '
    ACTION_RMOD_KEY(KC_RSFT, KC_1),    // Shift+1 = !
    ACTION_RMOD_KEY(KC_RSFT, KC_2),    // Shift+2 = "
    ACTION_RMOD_KEY(KC_RSFT, KC_NUBS), // Shift+< = >
    ACTION_RMOD_KEY(KC_RSFT, KC_4),    // Shift+4 = $
    ACTION_RMOD_KEY(KC_RSFT, KC_5),    // Shift+5 = %
    ACTION_RMOD_KEY(KC_RSFT, KC_6),    // Shift+6 = &
    ACTION_RMOD_KEY(KC_RSFT, KC_MINS), // Shift+ß = ?
    ACTION_RMOD_KEY(KC_RSFT, KC_8),    // Shift+8 = (
    ACTION_RMOD_KEY(KC_RSFT, KC_9),    // Shift+9 = )

/// FN20..29: AltGr special chars on Qwertz
    ACTION_RMOD_KEY(KC_RALT, KC_0),    // AltGr+0 = }
    ACTION_RMOD_KEY(KC_RALT, KC_RBRC), // AltGr++ = ~
    ACTION_RMOD_KEY(KC_RALT, KC_NUBS), // AltGr+< = |
    ACTION_RMOD_KEY(KC_RALT, KC_Q),    // AltGr+q = @
    ACTION_RMOD_KEY(KC_RALT, KC_E),    // AltGr+e = €
    ACTION_RMOD_KEY(KC_RALT, KC_NUHS), // AltGr+# = ` (same as Shift+´)
    ACTION_RMOD_KEY(KC_RALT, KC_MINS), // AltGr+ß = '\'
    ACTION_RMOD_KEY(KC_RALT, KC_7),    // AltGr+7 = {
    ACTION_RMOD_KEY(KC_RALT, KC_8),    // AltGr+8 = [
    ACTION_RMOD_KEY(KC_RALT, KC_9),    // AltGr+9 = ]

/// FN31
    ACTION_LAYER_SET(0)
};


/*
 * Macro definition
 */
#define MACRO(...) ({ static const prog_macro_t _m[] PROGMEM = { __VA_ARGS__ }; _m; })
#define MACRO_NONE  0
static const prog_macro_t *get_macro(uint8_t id, bool pressed)
{
    switch (id) {
        case 0:
            return (pressed ?
                    MACRO( I(255), T(H), T(E), T(L), T(L), W(255), T(O), END ) :
                    MACRO_NONE );
        case 1:
            return (pressed ?
                    MACRO( I(255), T(H), T(E), T(L), T(L), W(255), T(O), END ) :
                    MACRO_NONE );
    }
    return 0;
}



/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, key_t key)
{
    return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
}

/* translates Fn index to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
    action_t action;
    if (FN_INDEX(keycode) < sizeof(fn_actions) / sizeof(fn_actions[0])) {
        action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    } else {
        action.code = ACTION_NO;
    }
    return action;
}

/* convert key to action */
action_t action_for_key(uint8_t layer, key_t key)
{
    uint8_t keycode = keymap_key_to_keycode(layer, key);
    switch (keycode) {
        case KC_FN0 ... KC_FN31:
            return keymap_fn_to_action(keycode);
        default:
            return keymap_keycode_to_action(keycode);
    }
}



/*
 * user defined action function
 */
//void keymap_call_function(keyrecord_t *record, uint8_t id, uint8_t opt)
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    print_enable = true;

    keyevent_t event = record->event; // keyevent with key (row,col), pressed, time
    uint8_t tap_count = record->tap_count;
    uint8_t tapped = 0;
/*
    debug("action_call_function: ");
    if (event.pressed) debug("pressed"); else debug("released");
    debug(" id: "); debug_hex(id);
    debug(" tap_count: "); debug_dec(tap_count);
    debug("\n");
*/
    switch (id) {
        case QWERTZ:
            //print("\nQWERTZ: "); pdec(event.key.col); pdec(event.key.row);
            if (waiting_buffer_has_anykey_pressed()) {
                tapped = get_tapping_key();
                print_S("\n2nd: "); print_hex8(tapped);
            }
            if (event.pressed) {
                if (tap_count == 0) {
                    // no other key pressed yet, wait...
                    /*if(event.key.col < 4)
                        add_mods(MOD_BIT(KC_LSHIFT));
                    else
                        add_mods(MOD_BIT(KC_RALT));
                        */
                    //add_mods(MOD_BIT(KC_LSHIFT));
                } else {
                    if (waiting_buffer_has_anykey_pressed()) {
                        // modify according to qwertz mapping now!
                        // ad hoc: set 0 to cancel tap
                        // debug_hex((event.key.row<<4)| event.key.col);
                        record->tap_count = 0;
                        if(tapped < 4)
                            add_mods(MOD_BIT(KC_LSHIFT));
                        else
                            add_mods(MOD_BIT(KC_RALT));

                        // add_mods(MOD_BIT(KC_LSHIFT));
                    } else {
                        // released FNx as only key, no other key had been pressed additionally
                    }
                }
            } else {
                if (tap_count == 0) {
                    if(tapped < 4)
                        del_mods(MOD_BIT(KC_LSHIFT));
                    else
                        del_mods(MOD_BIT(KC_RALT));
                    //del_mods(MOD_BIT(KC_LSHIFT));
                } else {
                    /*
                    //unregister_code(KC_9);
                    //unregister_code(KC_LSHIFT);
                    host_del_mods(MOD_BIT(KC_LSHIFT));
                    host_del_key(KC_9);
                    host_send_keyboard_report();
                    */
                }
            }
            break;
        case LSHIFT_LPAREN:
            // LShft + tap '('
            if (event.pressed) {
                if (tap_count == 0) {
                    add_mods(MOD_BIT(KC_LSHIFT));
                } else {
                    if (waiting_buffer_has_anykey_pressed()) {
                        // ad hoc: set 0 to cancel tap
                        record->tap_count = 0;
                        add_mods(MOD_BIT(KC_LSHIFT));
                    } else {
                        // NOTE to avoid conflicting command key bind(LShift+RShift)
                        //register_code(KC_LSHIFT);
                        register_code(KC_9);
                        /*
                        host_add_mods(MOD_BIT(KC_LSHIFT));
                        host_add_key(KC_9);
                        host_send_keyboard_report();
                        */
                    }
                }
            } else {
                if (tap_count == 0) {
                    del_mods(MOD_BIT(KC_LSHIFT));
                } else {
                    //unregister_code(KC_9);
                    //unregister_code(KC_LSHIFT);
                    host_del_mods(MOD_BIT(KC_LSHIFT));
                    host_del_key(KC_9);
                    host_send_keyboard_report();
                }
            }
            break;
        case RSHIFT_RPAREN:
            // RShift + tap ')'
            if (event.pressed) {
                if (tap_count == 0) {
                    add_mods(MOD_BIT(KC_RSHIFT));
                } else {
                    if (waiting_buffer_has_anykey_pressed()) {
                        // ad hoc: set 0 to cancel tap
                        record->tap_count = 0;
                        add_mods(MOD_BIT(KC_RSHIFT));
                    } else {
                        //register_code(KC_RSHIFT);
                        //register_code(KC_0);
                        host_add_mods(MOD_BIT(KC_RSHIFT));
                        host_add_key(KC_0);
                        host_send_keyboard_report();
                    }
                }
            } else {
                if (tap_count == 0) {
                    del_mods(MOD_BIT(KC_RSHIFT));
                } else {
                    //unregister_code(KC_0);
                    //unregister_code(KC_RSHIFT);
                    host_del_mods(MOD_BIT(KC_RSHIFT));
                    host_del_key(KC_0);
                    host_send_keyboard_report();
                }
            }
            break;
        case MACRO:
            action_macro_play(get_macro(opt, event.pressed));
            break;
    }
}

