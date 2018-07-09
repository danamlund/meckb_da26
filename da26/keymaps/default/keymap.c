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

#define ____ KC_NO

#define PREVENT_STUCK_MODIFIERS

#define F0_LFN1 1
#define F0_RFN1 2
#define F0_LFN2 3
#define F0_RFN2 4
#define F0_FN3 5
#define FTETRIS 6
#define FHELP 7
#define FBASIC 8
#define FMINESWEEPER 9

#define FN1L 1
#define FN1LB 2
#define FN1R 3
#define FN2L 4
#define FN2R 5
#define FN2B 6
#define FN3 7
#define FN3B 8
#define FNMINES 9

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
[FN1L] = LAYOUT(
  KC_ESC, ____, ____, ____, ____, ____, KC_LBRC, KC_RBRC, KC_BSLS, KC_BSPC, \
    KC_LSFT, KC_RSFT, MO(FN1LB), KC_TRNS, ____, KC_SPC, KC_SCLN, KC_QUOT, KC_ENT, \
      KC_LCTL, KC_LGUI, KC_LALT, KC_APP, KC_COMM, MT(MOD_RALT, KC_DOT), MT(MOD_RCTL, KC_SLSH) \
),
[FN1LB] = LAYOUT(
  ____, ____, ____, ____, ____, ____, ____, ____, ____, KC_DEL, \
    KC_LSFT, ____, KC_TRNS, KC_TRNS, ____, ____, KC_TRNS, ____, KC_RSFT, \
      KC_LCTL, KC_LGUI, KC_LALT, ____, ____, KC_RALT, KC_RCTL \
),
[FN1R] = LAYOUT(
  KC_ESC, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    MT(MOD_LSFT, KC_TAB), ____, ____, ____, KC_SPC, ____, KC_TRNS, ____, KC_RSFT, \
      KC_LCTL, KC_LGUI, KC_LALT, ____, ____, KC_RALT, KC_RCTL \
),
[FN2L] = LAYOUT(
  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, \
    MT(MOD_LSFT, KC_GRV), ____, KC_TRNS, MO(FN2B), ____, ____, ____, KC_MINS, MT(MOD_RSFT, KC_EQL), \
      KC_LCTL, KC_LGUI, KC_LALT, ____, ____, KC_RALT, KC_RCTL \
),
[FN2R] = LAYOUT(
  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, \
    MT(MOD_LSFT, KC_GRV), ____, ____, ____, ____, ____, MO(FN2B), KC_TRNS, MT(MOD_RSFT, KC_EQL), \
      KC_LCTL, KC_LGUI, KC_LALT, ____, ____, KC_RALT, KC_RCTL \
),
[FN2B] = LAYOUT(
  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, \
    KC_LSFT, ____, KC_TRNS, KC_TRNS, ____, ____, KC_TRNS, KC_F11, MT(MOD_RSFT, KC_F12), \
      KC_LCTL, KC_LGUI, KC_LALT, ____, ____, KC_RALT, KC_RCTL \
),
[FN3] = LAYOUT(
  KC_ESC, ____, ____, ____, F(FTETRIS), ____, F(FHELP), KC_UP, ____, ____, \
    KC_LSFT, KC_TRNS, ____, MO(FN3B), ____, ____, KC_LEFT, KC_DOWN, KC_RGHT, \
      KC_LCTL, KC_LGUI, KC_LALT, ____, F(FBASIC), KC_RALT, F(FMINESWEEPER)       \
),
[FN3B] = LAYOUT(
  ____, ____, ____, ____, ____, ____, ____, KC_PGUP, KC_INS, KC_PSCR, \
    KC_LSFT, KC_TRNS, ____, KC_TRNS, ____, ____, KC_HOME, KC_PGDN, KC_END, \
      KC_LCTL, KC_LGUI, KC_LALT, ____, ____, KC_RALT, KC_RCTL \
),
[FNMINES] = LAYOUT(
    KC_ESC, ____, ____, ____, ____, ____, ____, KC_UP, ____, ____, \
      ____, ____, KC_D, KC_F, ____, ____, KC_LEFT, KC_DOWN, KC_RGHT, \
        ____, ____, ____, ____, ____, ____, ____  \
),
};

const uint16_t PROGMEM fn_actions[] = {
  [F0_LFN1] = ACTION_LAYER_TAP_KEY(FN1L, KC_F),
  [F0_RFN1] = ACTION_LAYER_TAP_KEY(FN1R, KC_J),
  [F0_LFN2] = ACTION_LAYER_TAP_KEY(FN2L, KC_D),
  [F0_RFN2] = ACTION_LAYER_TAP_KEY(FN2R, KC_K),
  [F0_FN3] = ACTION_LAYER_TAP_KEY(FN3, KC_S),
  [FTETRIS] = ACTION_FUNCTION(FTETRIS),
  [FHELP] = ACTION_FUNCTION(FHELP),
  [FBASIC] = ACTION_FUNCTION(FBASIC),
  [FMINESWEEPER] = ACTION_FUNCTION(FMINESWEEPER),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    return MACRO_NONE;
};


void matrix_init_user(void) {
}

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (id == FTETRIS && record->event.pressed && !basic_is_running()) {
        tetris_qmk_start();
    }
    else if (id == FHELP && record->event.pressed) {
        SEND_STRING("http://github.com/danamlund/meckb_da26");
    }
    else if (id == FBASIC && record->event.pressed && !basic_is_running()) {
        basic_start();
    }
    else if (id == FMINESWEEPER && record->event.pressed && !basic_is_running()) {
        layer_on(FNMINES);
        minesweeper_start();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
    if (!is_layer_on(state, FN1L)) {
        state = without_layer(state, FN1LB);
    }

    if (!is_layer_on(state, FN2L) && !is_layer_on(state, FN2R)) {
        state = without_layer(state, FN2B);
    }

    if (!is_layer_on(state, FN3)) {
        state = without_layer(state, FN3B);
    }
    return state;
}
