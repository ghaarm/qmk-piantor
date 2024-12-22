// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include  "keymap_german.h"

// Globale Variablen für die Backspace-Wiederholung
static bool backspace_active = false;  // Status der Backspace-Taste
static uint16_t backspace_timer = 0;   // Timer für die Wiederholung
static bool first_repeat = true;       // Status der ersten Wiederholung

enum layers {
    _BASE,
    _LOWER,
    _UPPER
};

// Custom keycodes
enum custom_keycodes {
    MORPH_AE = SAFE_RANGE,
    MORPH_OE,
    MORPH_UE,
    MORPH_SS,
    MORPH_SPACE,
    MORPH_BSPC
};


// Key Override
const key_override_t lshift_lgui_space_to_lctl_enter = ko_make_basic(MOD_MASK_SHIFT | MOD_MASK_GUI, KC_SPACE, G(KC_ENT));


// Array von Key Overrides
const key_override_t *key_overrides[] = {
    &lshift_lgui_space_to_lctl_enter,

    NULL // Array muss mit NULL enden
};
// Custom behavior for morph keys
//
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        bool alt_held = get_mods() & MOD_BIT(KC_LALT);    // Prüfen, ob Alt gehalten wird
        bool shift_held = get_mods() & MOD_BIT(KC_LSFT); // Prüfen, ob Shift gehalten wird
        /* bool right_shift_held = get_mods() & MOD_BIT(KC_RSFT); // Prüfen, ob Shift gehalten wird */

        switch (keycode) {
            case MORPH_AE:
                if (alt_held && shift_held) {
                    uint8_t mods = get_mods(); // Aktuelle Modifikatoren speichern
                    del_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT)); // Alt und Shift entfernen
                    tap_code16(S(DE_ADIA)); // Shift DE_ADIA -> Ä
                    set_mods(mods); // Modifikatoren wiederherstellen
                } else if (alt_held) {
                    uint8_t mods = get_mods(); // Aktuelle Modifikatoren speichern
                    del_mods(MOD_BIT(KC_LALT)); // Alt entfernen
                    tap_code(DE_ADIA); // DE_ADIA -> ä
                    set_mods(mods); // Modifikatoren wiederherstellen
                } else {
                    tap_code(KC_A); // Standard: A
                }
                return false;

            case MORPH_OE:
                if (alt_held && shift_held) {
                    uint8_t mods = get_mods(); // Aktuelle Modifikatoren speichern
                    del_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT)); // Alt und Shift entfernen
                    tap_code16(S(DE_ODIA)); // Shift DE_ADIA -> Ä
                    set_mods(mods); // Modifikatoren wiederherstellen
                } else if (alt_held) {
                    uint8_t mods = get_mods(); // Aktuelle Modifikatoren speichern
                    del_mods(MOD_BIT(KC_LALT)); // Alt entfernen
                    tap_code(DE_ODIA); // DE_ADIA -> ä
                    set_mods(mods); // Modifikatoren wiederherstellen
                } else {
                    tap_code(KC_O); // Standard: A
                }
                return false;

            case MORPH_UE:
                if (alt_held && shift_held) {
                    uint8_t mods = get_mods(); // Aktuelle Modifikatoren speichern
                    del_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT)); // Alt und Shift entfernen
                    tap_code16(S(DE_UDIA)); // Shift DE_ADIA -> Ä
                    set_mods(mods); // Modifikatoren wiederherstellen
                } else if (alt_held) {
                    uint8_t mods = get_mods(); // Aktuelle Modifikatoren speichern
                    del_mods(MOD_BIT(KC_LALT)); // Alt entfernen
                    tap_code(DE_UDIA); // DE_ADIA -> ä
                    set_mods(mods); // Modifikatoren wiederherstellen
                } else {
                    tap_code(KC_U); // Standard: A
                }
                return false;

            case MORPH_SS:
                if (alt_held) {
                    uint8_t mods = get_mods(); // Aktuelle Modifikatoren speichern
                    del_mods(MOD_BIT(KC_LALT)| MOD_BIT(KC_LSFT)); // Alt und Shift entfernen
                    tap_code(DE_SS); // DE_ADIA -> ä
                    set_mods(mods); // Modifikatoren wiederherstellen
                } else {
                    tap_code(KC_S); // Standard: A
                }
                return false;

            /* case MORPH_SPACE: */
            /*     if (right_shift_held) { */
            /*         uint8_t mods = get_mods(); // Aktuelle Modifikatoren speichern */
            /*         del_mods(MOD_BIT(KC_RSFT)); // Alt und Shift entfernen */
            /*         tap_code(KC_RGUI); // DE_ADIA -> ä */
            /*         set_mods(mods); // Modifikatoren wiederherstellen */
            /*     } else { */
            /*         tap_code(KC_SPACE); // Standard: A */
            /*     } */
            /*     return false; */

            /* case MORPH_BSPC: */
            /*     if (shift_held) { */
            /*         uint8_t mods = get_mods(); // Aktuelle Modifikatoren speichern */
            /*         del_mods(MOD_BIT(KC_LSFT)); // Alt und Shift entfernen */
            /*         tap_code(KC_DEL); // DE_ADIA -> ä */
            /*         set_mods(mods); // Modifikatoren wiederherstellen */
            /*     } else { */
            /*         tap_code(KC_BSPC); // Standard: A */
            /*     } */
            /*     return false; */

            case MORPH_BSPC:
                if (shift_held) {
                    uint8_t mods = get_mods(); // Aktuelle Modifikatoren speichern
                    del_mods(MOD_BIT(KC_LSFT)); // Shift entfernen
                    tap_code(KC_DEL); // Shift + Backspace -> Delete
                    set_mods(mods); // Modifikatoren wiederherstellen
                } else {
                    // Aktivieren der Wiederholung für Backspace
                    backspace_active = true; // Markiere, dass Backspace gehalten wird
                    backspace_timer = timer_read(); // Timer für Wiederholung starten
                    first_repeat = true;            // Erste Wiederholung aktivieren
                    tap_code(KC_BSPC); // Backspace initial senden
                }
                return false;

            default:
                break;
        }
    } else {
        switch (keycode) {
            case MORPH_BSPC:
                // Deaktivieren, wenn Taste losgelassen wird
                backspace_active = false;
                first_repeat = true; // Reset für die nächste Nutzung
                break;

            default:
                break;


        }
    }
    return true;
}


/* void matrix_scan_user(void) { */
/*     if (backspace_active && timer_elapsed(backspace_timer) > 150) { */
/*         tap_code(KC_BSPC); // Wiederhole Backspace */
/*         backspace_timer = timer_read(); // Timer zurücksetzen */
/*     } */
/* } */


void matrix_scan_user(void) {
    static bool first_repeat = true; // Markiere, ob es die erste Wiederholung ist

    if (backspace_active) {
        if (first_repeat && timer_elapsed(backspace_timer) > 150) { // Initiale Verzögerung: 150 ms
            tap_code(KC_BSPC);          // Sende erste Wiederholung
            backspace_timer = timer_read();
            first_repeat = false;       // Wechsel zur schnelleren Wiederholung
        } else if (!first_repeat && timer_elapsed(backspace_timer) > 50) { // Wiederholrate: 50 ms
            tap_code(KC_BSPC);
            backspace_timer = timer_read();
        }
    }
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        KC_TAB,                 KC_Q,       KC_W,       KC_F,       KC_P,       KC_B,                                                               KC_J,           KC_L,           MORPH_UE,KC_Z,    KC_RBRC,     KC_NUHS,
        MT(MOD_LSFT, KC_ESC),   MORPH_AE,   KC_R,       MORPH_SS,   KC_T,       KC_G,                                                               KC_M,           KC_N,           KC_E,    KC_I,    MORPH_OE,     KC_RSFT,
        KC_LCTL,                KC_Y,       KC_X,       KC_C,       KC_D,       KC_V,                                                               KC_K,           KC_H,           KC_COMM, KC_DOT,  KC_SLSH,      KC_GRV,
                                                                    KC_LALT,    MO(_LOWER),     MT(MOD_LGUI, KC_ENT),               KC_SPACE,    MORPH_BSPC,     MO(_UPPER)
    ),

    [_LOWER] = LAYOUT_split_3x6_3(
        KC_NUBS,   LSFT(KC_1), LSFT(KC_2), LSFT(KC_3),  LSFT(KC_4),  LSFT(KC_5),                                      LSFT(KC_6),         LSFT(KC_7),         LSFT(KC_8),     LSFT(KC_9), LSFT(KC_0), LSFT(KC_MINS),
        _______,   KC_1,       KC_2,       KC_3,        KC_4,        KC_5,                                            KC_LEFT,            KC_DOWN,            KC_UP,          KC_RGHT,    KC_NO,      KC_EQL,
        _______,   KC_6,       KC_7,       KC_8,        KC_9,       KC_0,                                            LSFT(LGUI(KC_8)),   LSFT(LGUI(KC_9)),   LALT(KC_8),     LALT(KC_9), KC_NO,      KC_PIPE,
                                                        _______,     _______,    _______,                    _______, _______, _______
    ),
    [_UPPER] = LAYOUT_split_3x6_3(
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,                                            KC_NO,      KC_NO,      KC_NO,      KC_NO,     KC_NO,      KC_NO,
        _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,                                            KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_SCLN,    QK_BOOT,
        KC_NO,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,                                           KC_NO,      KC_MPRV,    KC_VOLD,    KC_VOLU,    KC_MNXT,    KC_MPLY,
                                                        _______,    _______,    _______,                    _______,  _______,    _______


    )
};


