// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include  "keymap_german.h"


// Globale Variablen für die Backspace-Wiederholung
/* static bool backspace_active = false;  // Status der Backspace-Taste */
/* static uint16_t backspace_timer = 0;   // Timer für die Wiederholung */
/* static bool first_repeat = true;       // Status der ersten Wiederholung */

enum layers {
    _BASE,
    _LOWER,
    _UPPER,
    _FUNCTION,
};

// https://docs.qmk.fm/features/combo
// Definiere die Combo-Events

enum combo_events {
  EM_EMAIL,
  BSPC_LSFT_CLEAR,
};

bool get_combo_must_tap(uint16_t combo_index, combo_t *combo) {
    // Prüfe, ob die Combo die Tap-Aktion benötigt
    switch (combo_index) {
        case BSPC_LSFT_CLEAR:  // Dein Combo-Name
            return true;       // Nur die Tap-Aktion erlauben
        default:
            return false;      // Andere Combos können normal funktionieren
    }
}
const uint16_t PROGMEM email_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM clear_line_combo[] = {MT(MOD_LGUI, KC_ENT), LT(MO(_UPPER), KC_BSPC), COMBO_END};

combo_t key_combos[] = {
  [EM_EMAIL] = COMBO_ACTION(email_combo),
  [BSPC_LSFT_CLEAR] = COMBO_ACTION(clear_line_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case EM_EMAIL:
      if (pressed) {
        SEND_STRING("john.doe@example.com");
      }
      break;
    case BSPC_LSFT_CLEAR:
      if (pressed) {
        tap_code16(S(KC_HOME));
        tap_code16(KC_BSPC);
      }
      break;
  }
}


#define LT_REP LT(_LOWER, KC_0)
// Use `LT_REP` in your layout...
// https://getreuer.info/posts/keyboards/faqs/index.html#layer-tap-repeat-key
bool remember_last_key_user(uint16_t keycode, keyrecord_t* record,
                            uint8_t* remembered_mods) {
  if (keycode == LT_REP) { return false; }
  return true;
}

// Key Override für Morph Umlaute
const key_override_t alt_a_to_ae = ko_make_basic(MOD_MASK_ALT, KC_A, DE_ADIA);
const key_override_t alt_o_to_oe = ko_make_basic(MOD_MASK_ALT, KC_O, DE_UDIA);
const key_override_t alt_u_to_ue = ko_make_basic(MOD_MASK_ALT, KC_U, DE_UDIA);
const key_override_t alt_s_to_ss = ko_make_basic(MOD_MASK_ALT, KC_S, DE_SS);



// Key Override für Windows LGUI
const key_override_t lgui_a_to_lctl_a = ko_make_basic(MOD_MASK_GUI, KC_A, C(KC_A));
const key_override_t lgui_c_to_lctl_c = ko_make_basic(MOD_MASK_GUI, KC_C, C(KC_C));
const key_override_t lgui_f_to_lctl_f = ko_make_basic(MOD_MASK_GUI, KC_F, C(KC_F));
const key_override_t lgui_s_to_lctl_s = ko_make_basic(MOD_MASK_GUI, KC_S, C(KC_S));
const key_override_t lgui_v_to_lctl_v = ko_make_basic(MOD_MASK_GUI, KC_V, C(KC_V));
const key_override_t lgui_x_to_lctl_x = ko_make_basic(MOD_MASK_GUI, KC_X, C(KC_X));
const key_override_t lgui_z_to_lctl_z = ko_make_basic(MOD_MASK_GUI, KC_Z, C(KC_Z));



const key_override_t lalt_backspace_to_lctl_backspace = ko_make_basic(MOD_BIT(KC_LALT), KC_BSPC, C(KC_BSPC));

const key_override_t lshift_lgui_space_to_lctl_enter = ko_make_basic(MOD_MASK_SHIFT | MOD_MASK_GUI, KC_SPACE, C(KC_ENT));

const key_override_t lgui_w_to_lalt_f4 = ko_make_basic(MOD_MASK_GUI, KC_W, A(KC_F4));


// Array von Key Overrides
const key_override_t *key_overrides[] = {
    // Key Override für Morph Umlaute
    &alt_a_to_ae,
    &alt_o_to_oe,
    &alt_u_to_ue,
    &alt_s_to_ss,

    // Key Override für Windows
    &lgui_a_to_lctl_a,
    &lgui_c_to_lctl_c,
    &lgui_f_to_lctl_f,
    &lgui_s_to_lctl_s,
    &lgui_v_to_lctl_v,
    &lgui_x_to_lctl_x,
    &lgui_z_to_lctl_z,

    &lalt_backspace_to_lctl_backspace,

    &lshift_lgui_space_to_lctl_enter,

    &lgui_w_to_lalt_f4,  // Neuer Key Override
    NULL // Array muss mit NULL enden
};


bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case LT_REP:  // NAV layer on hold, Repeat Key on tap.
      if (record->tap.count) {  // On tap.
        repeat_key_invoke(&record->event);  // Repeat the last key.
        return false;  // Skip default handling.
      }
      break;

    // Other macros...
  }
  return true;  // Continue default handling.
}

// Custom keycodes
/* enum custom_keycodes { */
/*     MORPH_AE = SAFE_RANGE, */
/*     MORPH_OE, */
/*     MORPH_UE, */
/*     MORPH_SS, */
/*     MORPH_SPACE, */
/*     MORPH_BSPC */
/* }; */

// Custom behavior for morph keys
//
/* bool process_record_user(uint16_t keycode, keyrecord_t *record) { */
/*     if (record->event.pressed) { */
/*         bool alt_held = get_mods() & MOD_MASK_ALT;    // Prüfen, ob Alt gehalten wird */
/*         bool shift_held = get_mods() & MOD_BIT(KC_LSFT); // Prüfen, ob Shift gehalten wird */
        /* bool right_shift_held = get_mods() & MOD_BIT(KC_RSFT); // Prüfen, ob Shift gehalten wird */

/*         switch (keycode) { */
/*             case MORPH_AE: */
/*                 if (alt_held && shift_held) { */
/*                     uint8_t mods = get_mods(); // Aktuelle Modifikatoren speichern */
/*                     del_mods(MOD_MASK_ALT | MOD_BIT(KC_LSFT)); // Alt und Shift entfernen */
/*                     tap_code16(S(DE_ADIA)); // Shift DE_ADIA -> Ä */
/*                     set_mods(mods); // Modifikatoren wiederherstellen */
/*                 } else if (alt_held) { */
/*                     uint8_t mods = get_mods(); // Aktuelle Modifikatoren speichern */
/*                     del_mods(MOD_MASK_ALT); // Alt entfernen */
/*                     tap_code(DE_ADIA); // DE_ADIA -> ä */
/*                     set_mods(mods); // Modifikatoren wiederherstellen */
/*                 } else { */
/*                     tap_code(KC_A); // Standard: A */
/*                 } */
/*                 return false; */
/**/
/*         } */
    /* } else { */
    /*     switch (keycode) { */
    /*         case MORPH_BSPC: */
    /*             // Deaktivieren, wenn Taste losgelassen wird */
    /*             backspace_active = false; */
    /*             first_repeat = true; // Reset für die nächste Nutzung */
    /*             break; */
    /**/
    /*         default: */
    /*             break; */
    /**/
    /**/
    /*     } */
/*     } */
/*     return true; */
/* } */


/* void matrix_scan_user(void) { */
/*     if (backspace_active && timer_elapsed(backspace_timer) > 150) { */
/*         tap_code(KC_BSPC); // Wiederhole Backspace */
/*         backspace_timer = timer_read(); // Timer zurücksetzen */
/*     } */
/* } */


void matrix_scan_user(void) {
    if (layer_state_is(_LOWER) && layer_state_is(_UPPER)) {
        layer_on(_FUNCTION); // Aktiviere das Function-Layer
    } else {
        layer_off(_FUNCTION); // Deaktiviere das Function-Layer
    }
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        MT(MOD_HYPR, KC_TAB),   KC_Q,       KC_W,       KC_F,       KC_P,       KC_B,                                                               KC_J,           KC_L,           KC_U,KC_Z,    KC_RBRC,     KC_NUHS,
        MT(MOD_LSFT, KC_ESC),   KC_A,   KC_R,       KC_S,   KC_T,       KC_G,                                                               KC_M,           KC_N,           KC_E,    KC_I,    KC_O,     KC_RSFT,
        KC_LCTL,                KC_Y,       KC_X,       KC_C,       KC_D,       KC_V,                                                               KC_K,           KC_H,           KC_COMM, KC_DOT,  KC_SLSH,      KC_NUBS,
                                                                    MT(MOD_LALT, KC_DEL),    LT_REP,     MT(MOD_LGUI, KC_ENT),   KC_SPACE,       LT(MO(_UPPER), KC_BSPC),     KC_RALT
    ),

    [_LOWER] = LAYOUT_split_3x6_3(
        KC_GRV,   LSFT(KC_1), LSFT(KC_2), LSFT(KC_3),  LSFT(KC_4),  LSFT(KC_5),                                      LSFT(KC_6),         LSFT(KC_7),         LSFT(KC_8),     LSFT(KC_9), LSFT(KC_0), LSFT(KC_MINS),
        _______,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,                                                 KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_SCLN,    KC_EQL,
        _______,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,                                               LSFT(LGUI(KC_8)),   LSFT(LGUI(KC_9)),   LALT(KC_8),     LALT(KC_9), KC_NO,      KC_PIPE,
                                                        _______,     _______,    _______,                    _______, _______, _______
    ),
    [_UPPER] = LAYOUT_split_3x6_3(
        KC_NO,      KC_NO,     KC_NO,     KC_NO,     KC_NO,     QK_REP,                                        KC_NO,      KC_MPRV,    KC_COMM,    KC_DOT,   KC_NO,  QK_BOOT,
         _______,   KC_NO,       KC_NO,       KC_NO,        KC_NO,       KC_NO,                                KC_LEFT,            KC_DOWN,            KC_UP,          KC_RGHT,    KC_NO,      KC_NO,
         _______,   KC_NO,       KC_NO,       KC_NO,        KC_NO,       KC_NO,                                KC_HOME,       KC_PAGE_DOWN,        KC_PAGE_UP,        KC_END,    KC_MNXT,    KC_MPLY,

                                                        _______,    _______,    _______,                    _______,  _______,    _______
    ),
    [_FUNCTION] = LAYOUT_split_3x6_3(
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      QK_REP,                                            KC_NO,      KC_NO,      KC_NO,      KC_NO,     KC_NO,      KC_NO,
        _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,                                            KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_SCLN,    QK_BOOT,
        KC_NO,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,                                           KC_NO,      KC_MPRV,    KC_VOLD,    KC_VOLU,    KC_MNXT,    KC_MPLY,
        _______,    _______,    _______,                    _______,  _______,    _______


    )
};


