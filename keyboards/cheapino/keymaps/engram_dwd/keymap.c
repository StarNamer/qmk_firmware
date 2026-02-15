
#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

 enum custom_keycodes {
    MACRO_CUBE_ROOT_ONE = SAFE_RANGE,
#define M6 MACRO_CUBE_ROOT_ONE
    MACRO_EMRDT1402_SHARED,
#define M0 MACRO_EMRDT1402_SHARED
    MACRO_DEREK_DONGRAY,
#define M15 MACRO_DEREK_DONGRAY
    MACRO_ADMDDONGRAY,
#define M1 MACRO_ADMDDONGRAY
    MACRO_FORGE_LOGS,
#define M2 MACRO_FORGE_LOGS
    MACRO_1,
#define M10 MACRO_1
    MACRO_3,
#define M3 MACRO_3
    MACRO_FINLEYKNIGHT,
#define M5 MACRO_FINLEYKNIGHT
    MACRO_EMRSQL,
#define M8 MACRO_EMRSQL
    MACRO_9,
#define M9 MACRO_9
    MACRO_10,
    ARROW,
#define M14 ARROW
    BUILD_DATETIME,
    BRACES,
    POUND,
    ATSIGN,
};

void send_emrdt1402_shared(void) {
    SEND_STRING(SS_TAP(X_NUBS) SS_TAP(X_NUBS) "emrdt1402" SS_TAP(X_NUBS) "Shared");
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // Get current mod and one-shot mod states.
    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();

    switch (keycode) {

    case BRACES:  // Types [], {}, or <> and puts cursor between braces.
        if (record->event.pressed) {
            clear_oneshot_mods();  // Temporarily disable mods.
            unregister_mods(MOD_MASK_CSAG);
            if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
                SEND_STRING("{}");
                // } else if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
                // SEND_STRING("<>");
            } else {
                SEND_STRING("[]");
            }
            tap_code(KC_LEFT);  // Move cursor between braces.
            register_mods(mods);  // Restore mods.
        }
        return false;
    case MACRO_CUBE_ROOT_ONE:
        if (record->event.pressed) {
            SEND_STRING("-0.5-0.866i");
        }
        break;
    case MACRO_EMRDT1402_SHARED:
        if (record->event.pressed) {
            send_emrdt1402_shared();
        }
        break;
    case MACRO_DEREK_DONGRAY:
        if (record->event.pressed) {
            if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {  // Is shift held?
                // Temporarily delete shift.
                del_oneshot_mods(MOD_MASK_SHIFT);
                unregister_mods(MOD_MASK_SHIFT);
                send_emrdt1402_shared();
                register_mods(mods);            // Restore mods.
            } else {
                SEND_STRING("Derek.Dongray");
            }
        }
        break;
    case MACRO_1:
        if (record->event.pressed) {
            SEND_STRING("byou'");
            send_char('@');
            SEND_STRING("789:");
        }
        break;
    case MACRO_10:
        if (record->event.pressed) {
            SEND_STRING("st");
        }
        break;
    case MACRO_ADMDDONGRAY:
        if (record->event.pressed) {
            SEND_STRING("admddongray");
        }
        break;
    case MACRO_FORGE_LOGS:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_NUBS) SS_TAP(X_NUBS) "ukforge01" SS_TAP(X_NUBS) "logs");
        }
        break;
    case MACRO_3:
        if (record->event.pressed) {
            SEND_STRING("o-0.5dead-0.866pyathi\n");
        }
        break;
    case MACRO_FINLEYKNIGHT:
        if (record->event.pressed) {
            SEND_STRING("finley.knight\tP");
            send_char('%');
            SEND_STRING("D5{4+2W{#S!");
            send_char('"');
            SEND_STRING("nsVhIZyCxcGl{h_B");
        }
        break;
    case MACRO_EMRSQL:
        if (record->event.pressed) {
            SEND_STRING("EMRSQL\tIRvH73$2Q");
            send_char('"');
            SEND_STRING("10(");
            send_char('"');
            SEND_STRING("b)");
        }
        break;
    case MACRO_9:
        if (record->event.pressed) {
            SEND_STRING("fbkn&qA502Xopa");
        }
        break;
    case ARROW:  // Arrow macro, types -> or =>.
        if (record->event.pressed) {
            if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {  // Is shift held?
                // Temporarily delete shift.
                del_oneshot_mods(MOD_MASK_SHIFT);
                unregister_mods(MOD_MASK_SHIFT);
                SEND_STRING("=>");
                register_mods(mods);            // Restore mods.
            } else {
                SEND_STRING("->");
            }
        }
        return false;
    case BUILD_DATETIME:
        if (record->event.pressed) {
            SEND_STRING(__DATE__ " " __TIME__);
        }
        break;
    case POUND:
        if (record->event.pressed) {
            register_mods(MOD_BIT(KC_LALT)); // Register Alt
            tap_code(KC_KP_0);
            tap_code(KC_KP_1);
            tap_code(KC_KP_6);
            tap_code(KC_KP_3);
            unregister_mods(MOD_BIT(KC_LALT)); // Unregister Alt
        }
        break;
    }
    return true;
};

enum LAYERS {
    _BASE,
    _MOUSE,
    _NAV,
    _SYMBOL,
    _MACRO,
    _NUMBER,
    _FUNCTION,
    _MOUSE2,
//    _SPECIAL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x5_3(
        KC_B,         KC_Y,         KC_O,         KC_U,         KC_QUOT, LSFT(KC_2), KC_L,         KC_D,         KC_W,         KC_V,
        LGUI_T(KC_C), LALT_T(KC_I), LCTL_T(KC_E), LSFT_T(KC_A), KC_COMM, KC_DOT,     RSFT_T(KC_H), RCTL_T(KC_T), LALT_T(KC_S), RGUI_T(KC_N),
        KC_G,         KC_X,         KC_J,         KC_K,         KC_MINS, KC_QUES,    KC_R,         KC_M,         KC_F,         KC_P,
        LT(_SYMBOL, KC_ENT), LT(_NUMBER, KC_DEL), LT(_MACRO, KC_ESC), LT(_MOUSE2, KC_TAB), LT(_FUNCTION, KC_BSPC), LT(_NAV,KC_SPC)),
    [_MOUSE] = LAYOUT_split_3x5_3(
        KC_NO,   MS_WHLD, MS_WHLU, MS_BTN4, MS_BTN2, KC_NO,   KC_NO,     KC_NO,    KC_NO,   KC_NO,
        MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, MS_BTN1, KC_NO,   KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
        KC_NO,   KC_NO,   KC_NO,   MS_BTN5, MS_BTN3, KC_NO, KC_NO,     KC_NO,    KC_NO,   KC_NO,
        KC_TRNS, KC_TRNS, QK_LAYER_LOCK, KC_NO, KC_TRNS, KC_TRNS),
    [_NAV] = LAYOUT_split_3x5_3(
        KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     LCTL(KC_F), KC_PWR,  KC_CALC, KC_MAIL, KC_MSEL, QK_REBOOT,
        KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, LCTL(KC_Y), KC_MYCM, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,
        LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_A), KC_WAKE, KC_PSCR, KC_SCRL, KC_SLEP, QK_BOOT,
        KC_TRNS, KC_TRNS, QK_LAYER_LOCK, KC_TRNS, KC_TRNS, KC_NO),
    [_SYMBOL] = LAYOUT_split_3x5_3(
        COMMUNITY_MODULE_HELLO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,          KC_GRV,        LSFT(KC_COMMA), LSFT(KC_DOT),  LSFT(KC_BSLS), KC_NUBS,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,          BRACES,        KC_QUES, LSFT(KC_QUOT),       LCA(KC_4),       KC_NUHS,
        CW_TOGG, KC_CAPS, KC_NO,   KC_NO,   BUILD_DATETIME, LSFT(KC_NUHS), KC_LBRC,  KC_RBRC, POUND,       KC_SLASH,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [_MACRO] = LAYOUT_split_3x5_3(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, M10,     M15,     M3,     M0,    M2,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO, M9,      M1,      KC_NO,  KC_NO, KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, M6,      M5,      M8,     KC_NO, KC_NO,
        KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS),
    [_NUMBER] = LAYOUT_split_3x5_3(
        KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,   KC_NO, KC_EQUAL, KC_7, KC_8, KC_9, KC_E,
        LGUI_T(KC_LEFT), LALT_T(KC_DOWN), LCTL_T(KC_UP), LSFT_T(KC_RIGHT), KC_COMM, KC_DOT,   KC_1, KC_2, KC_3, KC_MINUS,
        LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),   KC_MINS, KC_0,     KC_4, KC_5, KC_6, KC_SLASH,
        KC_TRNS, KC_NO, KC_TRNS, QK_LAYER_LOCK, KC_TRNS, KC_TRNS),
    [_FUNCTION] = LAYOUT_split_3x5_3(
        KC_F22, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_F23, KC_F4, KC_F5, KC_F6, KC_F11, KC_NO, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI,
        KC_F24, KC_F1, KC_F2, KC_F3, KC_F12, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_NO, KC_TRNS),
    [_MOUSE2] = LAYOUT_split_3x5_3(
        KC_NO,   OM_DBLS, OM_U,    OM_BTNS, OM_W_U,  KC_NO, KC_NO,   KC_NO,    KC_NO,  KC_NO,
        OM_SLOW, OM_L,    OM_D,    OM_R,    OM_W_D,  KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
        OM_SEL3, OM_SEL2, OM_SEL1, OM_HLDS, OM_RELS, KC_NO, KC_NO,   KC_NO,    KC_NO,  KC_NO,
        KC_TRNS, KC_TRNS, QK_LAYER_LOCK, KC_NO, KC_TRNS, KC_TRNS),
    // [_SPECIAL] = LAYOUT_split_3x5_3(
    //     CM_HELO, KC_TRNS, KC_COLN,     KC_ESC,       KC_TAB,      DF(5),   KC_CALC, KC_MAIL,         KC_TRNS,        KC_DEL,
    //     KC_TRNS, KC_PERC, KC_SLSH,     KC_ENT,       LCG(KC_SPC), DF(1),   KC_LGUI, KC_TRNS,         KC_TRNS,        KC_SLEP,
    //     KC_X,    KC_TRNS, LSA(KC_SPC), LSA(KC_SCLN), OS_LGUI,     DF(0),   KC_TRNS, RALT_T(KC_COMM), RCTL_T(KC_DOT), QK_BOOT,
    //                       KC_TRNS,     KC_TRNS,      KC_TRNS,     KC_TRNS, KC_TRNS, KC_NO)
};


// const custom_shift_key_t custom_shift_keys[] = {
//     {KC_QUOT, KC_LPRN},
//     {LSFT(KC_2), KC_RPRN},
//     {KC_COMM, KC_SCLN},
//     {KC_DOT, LSFT(KC_SCLN)},
//     {KC_QUES, KC_EXLM},
//     {LT(_SPECIAL,KC_SPC), KC_TAB},
//     {RALT_T(KC_BSPC), KC_DEL}
// };


#define SHIFT_OVERRIDES \
O( shift_dquote_lpara ,KC_QUOT, KC_LPRN) \
O( shift_squote_rpara ,LSFT(KC_2), KC_RPRN) \
O( shift_dot_colon ,KC_DOT, LSFT(KC_SCLN)) \
O( shift_comma_semicolon ,KC_COMM, KC_SCLN) \
O( shift_ques_excl ,KC_QUES, LSFT(KC_1)) \
O( shift_tab_cword, LT(_MOUSE2, KC_TAB), CW_TOGG)

// O( shift_space_tab ,LT(_NAV,KC_SPC), KC_TAB)
// O( shift_backspace_del ,LT(_FUNCTION, KC_BSPC), KC_DEL)ee

#define O(name, key, shiftkey) const key_override_t name = ko_make_basic(MOD_MASK_SHIFT, key, shiftkey);
SHIFT_OVERRIDES
#undef O

#define O(name, key, shiftkey) &name,
const key_override_t *key_overrides[] = {
SHIFT_OVERRIDES
};
#undef O

// const key_override_t shift_dquote_rpara = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, KC_LPRN);
// const key_override_t shift_squote_lpara = ko_make_basic(MOD_MASK_SHIFT, LSFT(KC_2), KC_RPRN);
// const key_override_t shift_comma_semicolon = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
// const key_override_t shift_dot_colon = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, LSFT(KC_SCLN));
// const key_override_t shift_ques_excl = ko_make_basic(MOD_MASK_SHIFT, KC_QUES, LSFT(KC_1));
// const key_override_t shift_space_tab = ko_make_basic(MOD_MASK_SHIFT, LT(_SPECIAL,KC_SPC), KC_TAB);
// const key_override_t shift_backspace_del = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// // This globally defines all key overrides to be used
// const key_override_t *key_overrides[] = {
//     &shift_dquote_rpara,
//     &shift_squote_lpara,
//     &shift_comma_semicolon,
//     &shift_dot_colon,
//     &shift_ques_excl,
//     &shift_space_tab,
//     &shift_backspace_del,
// };

const uint16_t PROGMEM combo_ea[] = {LCTL_T(KC_E), LSFT_T(KC_A), COMBO_END};
const uint16_t PROGMEM combo_th[] = {RSFT_T(KC_H), RCTL_T(KC_T), COMBO_END};
combo_t key_combos[] = {
    COMBO(combo_ea, KC_Q),
    COMBO(combo_th, KC_Z),
};

