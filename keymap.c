#include QMK_KEYBOARD_H

#include "swapper.h"

#define WORK_UP LCA(KC_K)
#define WORK_DW LCA(KC_J)
#define WN_WK_UP LSA(KC_K)
#define WN_WK_DW LSA(KC_J)
#define UNDO LCTL(KC_Z)
#define REDO LCTL(KC_Y)

enum layers{
  BASE,
  SYM,
  NAV,
  NUM
};

enum keycodes {
    SW_WIN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
    KC_Q,      KC_W,      KC_F,      KC_P,       KC_B,      KC_MPLY,   KC_J,      KC_L,      KC_U,      KC_Y,      KC_QUOT,
    KC_A,      KC_R,      KC_S,      KC_T,       KC_G,                 KC_M,      KC_N,      KC_E,      KC_I,      KC_O,
    KC_Z,      KC_X,      KC_C,      KC_D,       KC_V,                 KC_K,      KC_H,      KC_COMM,   KC_DOT,    KC_SCLN,
                                     MO(NAV),    KC_LSFT,              KC_SPC,    MO(SYM)
  ),
  [SYM]  = LAYOUT(
    KC_ESC,   KC_LBRC,   KC_LCBR,   KC_LPRN,    KC_TILD,    KC_MPLY,   KC_CIRC,   KC_RPRN,   KC_RCBR,   KC_RBRC,   KC_GRV,
    KC_MINS,  KC_PAST,   KC_EQL,    KC_UNDS,    KC_DLR,                KC_HASH,   KC_RGUI,   KC_RALT,   KC_RCTL,   KC_RSFT,
    KC_PLUS,  KC_PIPE,   KC_AT,     KC_SLSH,    KC_PERC,               _______,   KC_BSLS,   KC_AMPR,   KC_QUES,   KC_EXLM,
                                    MO(NUM),    _______,               _______,   _______
  ),
  [NAV]  = LAYOUT(
    KC_TAB,    SW_WIN,    _______,   _______,    _______,   KC_MPLY,   KC_PGUP,   KC_HOME,   KC_UP,    KC_END,    KC_DEL,
    KC_LSFT,   KC_LCTL,   KC_LALT,   KC_LGUI,    _______,              KC_PGDN,   KC_LEFT,   KC_DOWN,  KC_RGHT,   KC_BSPC,
    UNDO,      KC_CUT,    KC_COPY,   KC_PASTE,   REDO,                 WN_WK_DW,  WORK_DW,   WORK_UP,  WN_WK_UP,   KC_ENT,
                                     _______,    _______,              _______,   MO(NUM)
  ),
  [NUM]  = LAYOUT(
    KC_1,      KC_2,      KC_3,      KC_4,       KC_5,      KC_MPLY,   KC_6,     KC_7,      KC_8,      KC_9,      KC_0,
    KC_LSFT,   KC_LCTL,   KC_LALT,   KC_LGUI,    KC_F11,               KC_F12,   KC_RGUI,   KC_RALT,   KC_RCTL,   KC_RSFT,
    KC_F1,     KC_F2,     KC_F3,     KC_F4,      KC_F5,                KC_F6,    KC_F7,     KC_F8,     KC_F9,     KC_F10,
                                     _______,    _______,              _______,  _______
  ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        if (get_highest_layer(layer_state) > 0){
            if (clockwise) {
                tap_code(KC_BRIU);
            } else {
                tap_code(KC_BRID);
            }
        } else {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        }
    }
    return true;
}

bool sw_win_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LALT, KC_TAB, SW_WIN,
        keycode, record
    );
    return true;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;
}

void render_lechiffre_logo(void) {

    static const char PROGMEM lechiffre_logo[] = {
        0x00, 0x80, 0x7c, 0x02, 0x01, 0x01, 0x80, 0x00, 0xe0, 0x50, 0x28, 0x98, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0xc1, 0x21, 0x11, 0x09, 0x09, 0x09, 0x08, 0x18, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x07, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x00, 0xf0, 0x8c, 0x44, 0xc2, 0x02, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x01, 0x00, 0x0e, 0x09, 0x04, 0xa0, 0x74, 0x02, 
        0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x00, 
        0xc0, 0x39, 0x07, 0x01, 0x01, 0x90, 0x7e, 0x11, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
        0x00, 0x00, 0x00, 0x10, 0x0c, 0x03, 0x00, 0x04, 0x72, 0x0e, 0x04, 0xc2, 0xa2, 0x50, 0x30, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x02, 0x01, 0x00
    };
    
    oled_write_raw_P(lechiffre_logo, sizeof(lechiffre_logo));
}

static void render_layer_status(void) {
    switch (get_highest_layer(layer_state)) {
        case BASE:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case SYM:
            oled_write_ln_P(PSTR("Sym"), false);
            break;
        case NAV:
            oled_write_ln_P(PSTR("Nav"), false);
            break;
        case NUM:
            oled_write_ln_P(PSTR("Num"), false);
            break;
        default:
            oled_write_ln_P(PSTR("?????"), false);
    }
}

void render_mod_status(uint8_t modifiers) {
    oled_write_ln_P(PSTR("Shft"), (modifiers & MOD_MASK_SHIFT));
    oled_write_ln_P(PSTR("Ctrl"), (modifiers & MOD_MASK_CTRL));
    oled_write_ln_P(PSTR("Gui"), (modifiers & MOD_MASK_GUI));
    oled_write_ln_P(PSTR("Alt"), (modifiers & MOD_MASK_ALT));
}

bool oled_task_user(void) {
    render_lechiffre_logo();
    oled_set_cursor(0,9);
    render_layer_status();
    oled_set_cursor(0,12);
	render_mod_status(get_mods()|get_oneshot_mods());
    return false;
}
#endif
