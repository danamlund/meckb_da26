/* Copyright 2018 dan amlund
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

#include "tinybasic_qmk.h"
#include "tetris_qmk.h"
#include "minesweeper_qmk.h"
#include "dynmacro.h"
#include "sudoku_qmk.h"

#undef DYNMACRO_BUFFER
#define DYNMACRO_BUFFER 256

#define PREVENT_STUCK_MODIFIERS

enum my_keycodes {
  HELP = SAFE_RANGE,
  TETRIS,
  BASIC,
  MINES,
  SUDOKU,
  QUICKCALC,
  DYNMACRO_RECORD,
  DYNMACRO_STOP,
  DYNMACRO_REPLAY,
};

#define F0_LFN1 1
#define F0_RFN1 2
#define F0_LFN2 3
#define F0_RFN2 4
#define F0_FN3 5

#define _1L 1
#define _1LB 2
#define _1R 3
#define _2L 4
#define _2R 5
#define _2B 6
#define _3 7
#define _3B 8
#define _MINES 9

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * ,-----------------------------------------------------------.
 * |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |
 * `-----------------------------------------------------------'
 *   |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |
 *   `-----------------------------------------------------'
 *     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |
 *     `-----------------------------------------'
 */
[0] = LAYOUT( /* Base */
  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, \
    MT(MOD_LSFT, KC_A), F(F0_FN3), F(F0_LFN2), F(F0_LFN1), KC_G, KC_H, F(F0_RFN1), F(F0_RFN2), MT(MOD_RSFT, KC_L), \
      MT(MOD_LCTL, KC_Z), MT(MOD_LGUI, KC_X), MT(MOD_LALT, KC_C), MT(MOD_LALT, KC_V), MT(MOD_RGUI, KC_B), MT(MOD_RALT, KC_N), MT(MOD_RCTL, KC_M) \
),
[_1L] = LAYOUT(
  KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS, KC_BSPC, \
    MT(MOD_LSFT, KC_TAB), KC_RSFT, MO(_1LB), KC_TRNS, XXXXXXX, KC_SPC, KC_SCLN, KC_QUOT, KC_ENT, \
      KC_LCTL, KC_LGUI, KC_LALT, KC_APP, KC_COMM, MT(MOD_RALT, KC_DOT), MT(MOD_RCTL, KC_SLSH) \
),
[_1LB] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL, \
    KC_LSFT, XXXXXXX, KC_TRNS, KC_TRNS, XXXXXXX, XXXXXXX, KC_TRNS, XXXXXXX, KC_RSFT, \
      KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX, XXXXXXX, KC_RALT, KC_RCTL \
),
[_1R] = LAYOUT(
  KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    MT(MOD_LSFT, KC_TAB), XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC, XXXXXXX, KC_TRNS, XXXXXXX, KC_RSFT, \
      KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX, XXXXXXX, KC_RALT, KC_RCTL \
),
[_2L] = LAYOUT(
  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, \
    MT(MOD_LSFT, KC_GRV), XXXXXXX, KC_TRNS, MO(_2B), XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, MT(MOD_RSFT, KC_EQL), \
      KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX, XXXXXXX, KC_RALT, KC_RCTL \
),
[_2R] = LAYOUT(
  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, \
    MT(MOD_LSFT, KC_GRV), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(_2B), KC_TRNS, MT(MOD_RSFT, KC_EQL), \
      KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX, XXXXXXX, KC_RALT, KC_RCTL \
),
[_2B] = LAYOUT(
  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, \
    KC_LSFT, XXXXXXX, KC_TRNS, KC_TRNS, XXXXXXX, XXXXXXX, KC_TRNS, KC_F11, MT(MOD_RSFT, KC_F12), \
      KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX, XXXXXXX, KC_RALT, KC_RCTL \
),
[_3] = LAYOUT(
  QUICKCALC, DYNMACRO_RECORD, DYNMACRO_STOP, DYNMACRO_REPLAY, TETRIS, XXXXXXX, HELP, KC_UP, SUDOKU, XXXXXXX, \
    KC_LSFT, KC_TRNS, XXXXXXX, MO(_3B), XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, \
      KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX, BASIC, KC_RALT, MINES       \
),
[_3B] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_INS, KC_PSCR, \
    KC_LSFT, KC_TRNS, XXXXXXX, KC_TRNS, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_END, \
      KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX, XXXXXXX, KC_RALT, KC_RCTL \
),
[_MINES] = LAYOUT(
    KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UP, XXXXXXX, XXXXXXX, \
      XXXXXXX, XXXXXXX, KC_D,  KC_F,  KC_L, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
)
};

const uint16_t PROGMEM fn_actions[] = {
  [F0_LFN1] = ACTION_LAYER_TAP_KEY(_1L, KC_F),
  [F0_RFN1] = ACTION_LAYER_TAP_KEY(_1R, KC_J),
  [F0_LFN2] = ACTION_LAYER_TAP_KEY(_2L, KC_D),
  [F0_RFN2] = ACTION_LAYER_TAP_KEY(_2R, KC_K),
  [F0_FN3] = ACTION_LAYER_TAP_KEY(_3, KC_S),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    return MACRO_NONE;
};


void matrix_init_user(void) {
}

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        if (keycode == TETRIS && !basic_is_running()) {
            layer_on(_MINES);
            tetris_qmk_start();
        }
        if (keycode == HELP) {
            SEND_STRING("http://github.com/danamlund/meckb_da26");
        }
        if (keycode == BASIC && !basic_is_running()) {
            basic_start();
        }
        if (keycode == MINES && !basic_is_running()) {
            layer_on(_MINES);
            minesweeper_start();
        }
        if (keycode == QUICKCALC && !basic_is_running()) {
            basic_quickcalc();
        }
        if (keycode == SUDOKU && !basic_is_running()) {
            sudoku_start();
        }
        if (keycode == DYNMACRO_RECORD) {
            dynmacro_record();
        }
        if (keycode == DYNMACRO_STOP) {
            dynmacro_stop();
        }
        if (keycode == DYNMACRO_REPLAY) {
            dynmacro_replay();
        }
    }
    if (!tetris_process_record_user(keycode, record)) {
        return false;
    }
    if (!minesweeper_process_record_user(keycode, record)) {
        return false;
    }
    return true;
}

/* Called when sending a keycode press. Do not send code if false. */
bool register_code_user(uint8_t code) {
    if (!basic_register_code_user(code)) {
        return false;
    }
    if (!dynmacro_register_code_user(code)) {
        return false;
    }
    if (!sudoku_register_code_user(code)) {
        return false;
    }
    return true;
}

/* Called when sending a keycode release. Do not send code if false. */
bool unregister_code_user(uint8_t code) {
    return true;
}

void matrix_scan_user(void) {
    da_util_matrix_scan_user();
    tetris_matrix_scan_user();
    basic_matrix_scan_user();
    dynmacro_matrix_scan_user();
}

void led_set_user(uint8_t usb_led) {

}

bool is_layer_on(uint32_t state, uint8_t layer) {
    return state & (1UL << layer);
}
uint32_t without_layer(uint32_t state, uint8_t layer) {
    return state & ~(1UL << layer);
}

uint32_t layer_state_set_user(uint32_t state) {
    // dont get stuck on layers depending on two held keys
    if (!is_layer_on(state, _1L)) {
        state = without_layer(state, _1LB);
    }

    if (!is_layer_on(state, _2L) && !is_layer_on(state, _2R)) {
        state = without_layer(state, _2B);
    }

    if (!is_layer_on(state, _3)) {
        state = without_layer(state, _3B);
    }
    return state;
}
