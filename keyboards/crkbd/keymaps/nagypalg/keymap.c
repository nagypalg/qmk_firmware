#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

static uint32_t inactivity_timer = 0;

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
    _BASE,  // 0
    _NUM,   // 1
    _SYM,   // 2
    _NAV,   // 3
    _FUNC,  // 4
    _MOUSE  // 5
};

// Custom keycodes

#define FUNC_TAB_CKC LT(_FUNC, KC_TAB)

#define C_S_V LCTL(LSFT(KC_V))
#define C_S_C LCTL(LSFT(KC_C))
#define C_S_F LCTL(LSFT(KC_F))

// Copy-paste from nagypalg.c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT_split_3x6_3(TG(5), KC_Q, LGUI_T(KC_W), LCTL_T(KC_F), KC_P, KC_B, KC_J, KC_L, RCTL_T(KC_U), RGUI_T(KC_Y), KC_QUOT, KC_RSFT, KC_BSPC, KC_A, LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G, KC_M, RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I), KC_O, KC_SCLN, KC_CAPS, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_ESC, MO(3), MO(1), FUNC_TAB_CKC, KC_BSPC, KC_SPC, KC_ENT),
                                                              [1] = LAYOUT_split_3x6_3(KC_NO, LCTL(KC_Q), KC_LGUI, LCTL(KC_F), LCTL(KC_P), LCTL(KC_B), KC_NO, KC_7, KC_8, KC_9, KC_NO, KC_NO, KC_TRNS, KC_LSFT, KC_LALT, KC_LCTL, MO(2), LCTL(KC_G), KC_NO, KC_4, KC_5, KC_6, KC_0, KC_NO, KC_NO, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_D), LCTL(KC_V), KC_NO, KC_1, KC_2, KC_3, KC_MINS, KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_DEL, KC_TRNS, KC_TRNS),
                                                              [2] = LAYOUT_split_3x6_3(KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_LCBR, KC_RCBR, KC_GRV, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_LPRN, KC_RPRN, KC_SCLN, KC_EQL, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LBRC, KC_RBRC, KC_BSLS, KC_MINS, KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_DEL, KC_TRNS, KC_TRNS),
                                                              [3] = LAYOUT_split_3x6_3(KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_INS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSFT, KC_NO, KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_DEL, KC_TRNS, KC_TRNS),
                                                              [4] = LAYOUT_split_3x6_3(KC_NO, KC_NO, KC_TRNS, C_S_F, KC_NO, KC_NO, KC_NO, KC_F7, KC_F8, KC_F9, KC_F11, KC_NO, KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_F4, KC_F5, KC_F6, KC_F10, KC_NO, KC_NO, KC_NO, KC_NO, C_S_C, KC_NO, C_S_V, KC_NO, KC_F1, KC_F2, KC_F3, KC_F12, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_DEL, KC_TRNS, KC_TRNS),
                                                              [5] = LAYOUT_split_3x6_3(KC_TRNS, KC_MPRV, KC_LGUI, KC_MPLY, KC_MNXT, KC_NO, KC_NO, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, RESET, RGB_TOG, KC_LSFT, KC_LALT, KC_LCTL, KC_RSFT, KC_TRNS, KC_NO, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_NO, KC_NO, KC_NO, KC_ACL0, KC_ACL1, KC_ACL2, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_NO, KC_BTN3, KC_BTN1, KC_BTN2, KC_BTN2, KC_BTN1, KC_BTN3)};

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;

layer_state_t layer_state_set_user(layer_state_t state) {
    if (rgblight_is_enabled()) {
        rgblight_enable_noeeprom();
    }
    switch (get_highest_layer(state)) {
        case 1:
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        case 2:
            rgblight_sethsv_noeeprom(HSV_PINK);
            break;
        case 3:
            rgblight_sethsv_noeeprom(HSV_ORANGE);
            break;
        case 4:
            rgblight_sethsv_noeeprom(HSV_BLUE);
            break;
        case 5:
            rgblight_sethsv_noeeprom(HSV_YELLOW);
            break;
        default:
            // base layer
            rgblight_sethsv_noeeprom(HSV_TEAL);
            break;
    }
    return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    // rgblight_config.raw = eeconfig_read_rgblight();
    if (rgblight_is_enabled()) {
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom(HSV_TEAL);
    }
    return state;
}
#endif

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_space(void) { oled_write_P(PSTR("     "), false); }

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[]  = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[]  = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[]  = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[]  = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[]  = {0xc7, 0};
    static const char PROGMEM on_off_2[]  = {0xc8, 0};
    static const char PROGMEM off_on_1[]  = {0xc9, 0};
    static const char PROGMEM off_on_2[]  = {0xca, 0};
    static const char PROGMEM on_on_1[]   = {0xcb, 0};
    static const char PROGMEM on_on_2[]   = {0xcc, 0};

    if (modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if (modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if (modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if (modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if (modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if (modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if (modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if (modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[]  = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[]  = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[]  = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[]  = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[]  = {0xc7, 0};
    static const char PROGMEM on_off_2[]  = {0xc8, 0};
    static const char PROGMEM off_on_1[]  = {0xc9, 0};
    static const char PROGMEM off_on_2[]  = {0xca, 0};
    static const char PROGMEM on_on_1[]   = {0xcb, 0};
    static const char PROGMEM on_on_2[]   = {0xcc, 0};

    if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_logo(void) {
    static const char PROGMEM corne_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    oled_write_P(PSTR("corne"), false);
}

void render_layer_state(void) {
    static const char PROGMEM base_layer[] = {0x20, 0x94, 0x95, 0x96, 0x20, 0x20, 0xb4, 0xb5, 0xb6, 0x20, 0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};

    static const char PROGMEM num_layer[] = {0x20, 0x94, 0x95, 0x96, 0x20, 0x20, 0xb4, 0xb5, 0xb6, 0x20, 0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};

    static const char PROGMEM sym_layer[] = {0x20, 0x94, 0x95, 0x96, 0x20, 0x20, 0xb4, 0xb5, 0xb6, 0x20, 0x20, 0xda, 0xdb, 0xdc, 0x20, 0};

    static const char PROGMEM nav_layer[] = {0x20, 0x94, 0x95, 0x96, 0x20, 0x20, 0xb7, 0xb8, 0xb9, 0x20, 0x20, 0xda, 0xdb, 0xdc, 0x20, 0};

    static const char PROGMEM func_layer[] = {0x20, 0x94, 0x95, 0x96, 0x20, 0x20, 0xba, 0xbb, 0xbc, 0x20, 0x20, 0xda, 0xdb, 0xdc, 0x20, 0};

    static const char PROGMEM mouse_layer[] = {0x20, 0x97, 0x98, 0x99, 0x20, 0x20, 0xba, 0xbb, 0xbc, 0x20, 0x20, 0xda, 0xdb, 0xdc, 0x20, 0};

    static const char PROGMEM other_layer[] = {0x20, 0x9d, 0x9e, 0x9f, 0x20, 0x20, 0xbd, 0xbe, 0xbf, 0x20, 0x20, 0xdd, 0xde, 0xdf, 0x20, 0};

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(base_layer, false);
            break;
        case _NUM:
            oled_write_P(num_layer, false);
            break;
        case _SYM:
            oled_write_P(sym_layer, false);
            break;
        case _NAV:
            oled_write_P(nav_layer, false);
            break;
        case _FUNC:
            oled_write_P(func_layer, false);
            break;
        case _MOUSE:
            oled_write_P(mouse_layer, false);
            break;
        default:
            oled_write_P(other_layer, false);
            break;
    }
}

void render_status_main(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods() | get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods() | get_oneshot_mods());
}

void render_status_secondary(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods() | get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods() | get_oneshot_mods());
}

void oled_task_user(void) {
    if (timer_elapsed32(inactivity_timer) > 30000) {
        oled_off();
        return;
    }
#    ifndef SPLIT_KEYBOARD
    else {
        oled_on();
    }
#    endif

    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}

#endif

void matrix_scan_user(void) {
#ifdef RGBLIGHT_ENABLE
    if (timer_elapsed32(inactivity_timer) > 30000) {
        rgblight_disable_noeeprom();
    }
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        inactivity_timer = timer_read32();
    }
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef RGBLIGHT_ENABLE
    rgblight_config.raw = eeconfig_read_rgblight();
    if (rgblight_is_enabled() && IS_LAYER_ON(0)) {
        rgblight_enable_noeeprom();
    }
#endif
    return;
}

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_config.raw = eeconfig_read_rgblight();
    if (rgblight_is_enabled()) {
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom(HSV_TEAL);
    }
#endif
}
