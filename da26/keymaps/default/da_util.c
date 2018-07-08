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
#include "da_util.h"

#define BUFFER_SIZE 16
static uint16_t keycodes_buffer[BUFFER_SIZE];
static uint8_t keycodes_buffer_index = 0;
static bool keycodes_buffer_sending = false;

bool keycodes_buffer_is_sending(void) {
    return keycodes_buffer_sending;
}

uint16_t keycode_without_shift(uint16_t keycode) {
    return keycode & ~QK_LSFT;
}
bool keycode_has_shift(uint16_t keycode) {
    return keycode & QK_LSFT;
}

void send_keycode_now(uint16_t keycode) {
    if (keycode_has_shift(keycode)) {
        keycode = keycode_without_shift(keycode);
        register_code(KC_LSFT);
        register_code(keycode);
        unregister_code(keycode);
        unregister_code(KC_LSFT);
    } else {
        register_code(keycode);
        unregister_code(keycode);
    }
}

void send_next_buffer(void) {
    if (keycodes_buffer_index > 0) {
        keycodes_buffer_sending = true;
        send_keycode_now(keycodes_buffer[0]);
        keycodes_buffer_sending = false;
        
        for (int i = 0; i < BUFFER_SIZE - 1; i++) {
            keycodes_buffer[i] = keycodes_buffer[i+1];
        }
        keycodes_buffer_index--;
    }
}

void da_util_matrix_scan_user(void) {
    send_next_buffer();
}

void send_keycode(uint16_t keycode) {
    // if buffer full, send first keycode
    if (keycodes_buffer_index >= BUFFER_SIZE) {
        send_next_buffer();
    }
    
    keycodes_buffer[keycodes_buffer_index] = keycode;
    keycodes_buffer_index++;
}

void send_keycode_shift(uint16_t keycode) {
    send_keycode(LSFT(keycode));
}

// ascii to keycodes (US layout)
uint16_t ascii_to_keycode(char c) {
    if (c >= 'a' && c <= 'z') {
        return KC_A + (c - 'a');
    } else if (c >= 'A' && c <= 'Z') {
        return LSFT((KC_A + (c - 'A')));
    } else if (c >= '1' && c <= '9') {
        return KC_1 + (c - '1');
    } else {
        switch (c) {
        case '0': return KC_0;
        case '\n': return KC_ENTER;
        case ' ': return KC_SPACE;
        case '!': return LSFT(KC_1);
        case '"': return LSFT(KC_QUOT);
        case '#': return LSFT(KC_3);
        case '$': return LSFT(KC_4);
        case '%': return LSFT(KC_5);
        case '&': return LSFT(KC_7);
        case '\'': return KC_QUOT;
        case '(': return LSFT(KC_9);
        case ')': return LSFT(KC_0);
        case '*': return LSFT(KC_8);
        case '+': return LSFT(KC_EQL);
        case ',': return KC_COMM;
        case '-': return KC_MINS;
        case '.': return KC_DOT;
        case '/': return KC_SLSH;
        case ':': return LSFT(KC_SCLN);
        case ';': return KC_SCLN;
        case '<': return LSFT(KC_COMM);
        case '=': return KC_EQL;
        case '>': return LSFT(KC_DOT);
        case '?': return LSFT(KC_SLSH);
        case '@': return LSFT(KC_2);
        case '[': return KC_LBRC;
        case '\\': return KC_BSLS;
        case ']': return KC_RBRC;
        case '^': return LSFT(KC_6);
        case '_': return LSFT(KC_MINS);
        case '`': return KC_GRV;
        case '{': return LSFT(KC_LBRC);
        case '|': return LSFT(KC_BSLS);
        case '}': return LSFT(KC_RBRC);
        case '~': return LSFT(KC_GRV);
        }
    }
    return KC_NO;
}

char keycode_to_ascii(uint16_t keycode) {
    for (char c = 0; c <= 126; c++) {
        if (ascii_to_keycode(c) == keycode) {
            return c;
        }
    }
    return 0;
}

void send_i(int i) {
    if (i == 0) {
        send_keycode_now(KC_0);
    } else if (i <= 9) {
        send_keycode_now(KC_1 + i - 1);
    } else {
        send_keycode_now(KC_A + (i - 10));
    }
}
void send_integer(uint16_t i) {
    if (i >= 16*16*16) {
        send_i((i / (16*16*16)) % 16);
    } else {
        send_i(0);
    }
    if (i >= 16*16) {
        send_i((i / (16*16)) % 16);
    } else {
        send_i(0);
    }
    if (i >= 16) {
        send_i((i / 16) % 16);
    } else {
        send_i(0);
    }
    send_i(i % 16);
}
