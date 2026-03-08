
#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#undef KC_DQUO
#define KC_DQUO LSFT(KC_2)
#undef KC_AT
#define KC_AT LSFT(KC_QUOTE)

#define TAP_KP(x) tap_code(KC_KP_##x);
#define W_ALT_1(a) TAP_KP(a)
#define W_ALT_2(a, b) W_ALT_1(a) TAP_KP(b)
#define W_ALT_3(a, b, c) W_ALT_2(a, b) TAP_KP(c)
#define W_ALT_4(a, b, c, d) W_ALT_3(a, b, c) TAP_KP(d)
#define W_ALT_5(a, b, c, d, e) W_ALT_4(a, b, c, d) TAP_KP(e)
#define W_ALT_6(a, b, c, d, e, f) W_ALT_5(a, b, c, d, e) TAP_KP(f)
#define W_ALT_7(a, b, c, d, e, f, g) W_ALT_6(a, b, c, d, e, f) TAP_KP(g)
#define W_ALT_8(a, b, c, d, e, f, g, h) W_ALT_7(a, b, c, d, e, f, g) TAP_KP(h)

#define GET_W_ALT_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME
#define W_ALT(...) do { \
    register_mods(MOD_BIT(KC_LEFT_ALT)); \
    GET_W_ALT_MACRO(__VA_ARGS__, W_ALT_8, W_ALT_7, W_ALT_6, W_ALT_5, W_ALT_4, W_ALT_3, W_ALT_2, W_ALT_1)(__VA_ARGS__) \
    unregister_mods(MOD_BIT(KC_LEFT_ALT)); \
} while (0)

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
    KC_POUND,
    KC_EURO,
    RTC_DATE,
    RTC_TIME,
};

void send_emrdt1402_shared(void) {
    SEND_STRING(SS_TAP(X_NUBS) SS_TAP(X_NUBS) "emrdt1402" SS_TAP(X_NUBS) "Shared");
}

char* rtc_read_date_str(void);
char* rtc_read_time_str(void);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // Get current mod and one-shot mod states.
    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();
    // Store the combined mod state once for readability
    const uint8_t all_mods = mods | oneshot_mods;

    switch (keycode) {

    case BRACES: // Types [], {}, or <> and puts cursor between braces.
        if (record->event.pressed) {
            clear_oneshot_mods(); // Temporarily disable mods.
            unregister_mods(MOD_MASK_CSAG);
            if (all_mods & MOD_MASK_SHIFT) {
                // Shift is held
                if (all_mods & MOD_MASK_CTRL) {
                    // BOTH Shift and Control are held
                    SEND_STRING("()");
                } else {
                    // ONLY Shift is held
                    SEND_STRING("{}");
                }
            } else if (all_mods & MOD_MASK_CTRL) {
                // Control is held (we know Shift is NOT)
                SEND_STRING("<>");
            } else {
                // Neither are held
                SEND_STRING("[]");
            }
            tap_code(KC_LEFT); // Move cursor between braces.
            register_mods(mods); // Restore mods.
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
            if ((all_mods & MOD_MASK_SHIFT) == MOD_MASK_SHIFT) { // Is shift held?
                // Temporarily delete shift.
                del_oneshot_mods(MOD_MASK_SHIFT);
                unregister_mods(MOD_MASK_SHIFT);
                send_emrdt1402_shared();
                register_mods(mods); // Restore mods.
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
    case ARROW: // Arrow macro, types -> or =>.
        if (record->event.pressed) {
            if ((all_mods & MOD_MASK_SHIFT) == MOD_MASK_SHIFT) { // Is shift held?
                // Temporarily delete shift.
                del_oneshot_mods(MOD_MASK_SHIFT);
                unregister_mods(MOD_MASK_SHIFT);
                SEND_STRING("=>");
                register_mods(mods); // Restore mods.
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
    case KC_POUND:
        if (record->event.pressed) {
            W_ALT(0, 1, 6, 3);
        }
        break;
    case KC_EURO:
        if (record->event.pressed) {
            W_ALT(0, 1, 2, 8);
        }
        break;
    case RTC_DATE:
        if (record->event.pressed) {
            char* d = rtc_read_date_str();
            SEND_STRING(d);
        }
        break;
    case RTC_TIME:
        if (record->event.pressed) {
            char* t = rtc_read_time_str();
            SEND_STRING(t);
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
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x5_3(
        KC_B, KC_Y, KC_O, KC_U, KC_QUOTE, KC_DOUBLE_QUOTE, KC_L, KC_D, KC_W, KC_V,
        LGUI_T(KC_C), LALT_T(KC_I), LCTL_T(KC_E), LSFT_T(KC_A), KC_COMMA, KC_DOT, RSFT_T(KC_H), RCTL_T(KC_T), LALT_T(KC_S), RGUI_T(KC_N),
        KC_G, KC_X, KC_J, KC_K, KC_MINUS, KC_QUESTION, KC_R, KC_M, KC_F, KC_P,
        LT(_SYMBOL, KC_ENTER), LT(_NUMBER, KC_DELETE), LT(_MACRO, KC_ESCAPE), LT(_MOUSE2, KC_TAB), LT(_FUNCTION, KC_BACKSPACE), LT(_NAV,KC_SPACE)),
    [_MOUSE] = LAYOUT_split_3x5_3(
        KC_NO, QK_MOUSE_WHEEL_DOWN, QK_MOUSE_WHEEL_UP, QK_MOUSE_BUTTON_4, QK_MOUSE_BUTTON_2, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        QK_MOUSE_CURSOR_LEFT, QK_MOUSE_CURSOR_DOWN, QK_MOUSE_CURSOR_UP, QK_MOUSE_CURSOR_RIGHT, QK_MOUSE_BUTTON_1, KC_NO, KC_LEFT_SHIFT, KC_LEFT_CTRL, KC_LEFT_ALT, KC_LEFT_GUI,
        KC_NO, KC_NO, KC_NO, QK_MOUSE_BUTTON_5, QK_MOUSE_BUTTON_3, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_TRANSPARENT, QK_LAYER_LOCK, KC_NO, KC_TRANSPARENT, KC_TRANSPARENT),
    [_NAV] = LAYOUT_split_3x5_3(
        KC_HOME, KC_PAGE_DOWN, KC_PAGE_UP, KC_END, LCTL(KC_F), KC_SYSTEM_POWER, KC_CALCULATOR, KC_MAIL, KC_MEDIA_SELECT, QK_REBOOT,
        KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, LCTL(KC_Y), KC_MY_COMPUTER, KC_RIGHT_SHIFT, KC_RIGHT_CTRL, KC_RIGHT_ALT, KC_RIGHT_GUI,
        LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_A), KC_SYSTEM_WAKE, KC_PRINT_SCREEN, KC_SCROLL_LOCK, KC_SYSTEM_SLEEP, QK_BOOTLOADER,
        KC_TRANSPARENT, KC_TRANSPARENT, QK_LAYER_LOCK, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO),
    [_SYMBOL] = LAYOUT_split_3x5_3(
        COMMUNITY_MODULE_HELLO, KC_NO, KC_NO, KC_NO, KC_NO, KC_GRAVE, KC_LEFT_ANGLE_BRACKET, KC_RIGHT_ANGLE_BRACKET, KC_PIPE, KC_NONUS_BACKSLASH,
        KC_LEFT_GUI, KC_LEFT_ALT, KC_LEFT_CTRL, KC_LEFT_SHIFT, KC_NO, BRACES, KC_QUESTION, KC_AT, KC_NONUS_HASH, KC_EURO,
        QK_CAPS_WORD_TOGGLE, KC_CAPS_LOCK, RTC_DATE, RTC_TIME, BUILD_DATETIME, LSFT(KC_NONUS_HASH), KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_POUND, KC_SLASH,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
    [_MACRO] = LAYOUT_split_3x5_3(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, M10, M15, M3, M0, M2,
        KC_LEFT_GUI, KC_LEFT_ALT, KC_LEFT_CTRL, KC_LEFT_SHIFT, KC_NO, M9, M1, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, M6, M5, M8, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_NO, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
    [_NUMBER] = LAYOUT_split_3x5_3(
        KC_HOME, KC_PAGE_DOWN, KC_PAGE_UP, KC_END, KC_NO, KC_EQUAL, KC_7, KC_8, KC_9, KC_E,
        LGUI_T(KC_LEFT), LALT_T(KC_DOWN), LCTL_T(KC_UP), LSFT_T(KC_RIGHT), KC_COMMA, KC_DOT, KC_1, KC_2, KC_3, KC_MINUS,
        LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_MINUS, KC_0, KC_4, KC_5, KC_6, KC_SLASH,
        KC_TRANSPARENT, KC_NO, KC_TRANSPARENT, QK_LAYER_LOCK, KC_TRANSPARENT, KC_TRANSPARENT),
    [_FUNCTION] = LAYOUT_split_3x5_3(
        KC_F22, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_F23, KC_F4, KC_F5, KC_F6, KC_F11, KC_NO, KC_RIGHT_SHIFT, KC_RIGHT_CTRL, KC_LEFT_ALT, KC_RIGHT_GUI,
        KC_F24, KC_F1, KC_F2, KC_F3, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO, KC_TRANSPARENT),
    [_MOUSE2] = LAYOUT_split_3x5_3(
        KC_NO, OM_DBLS, OM_U, OM_BTNS, OM_W_U, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        OM_SLOW, OM_L, OM_D, OM_R, OM_W_D, KC_NO, KC_LEFT_SHIFT, KC_LEFT_CTRL, KC_LEFT_ALT, KC_LEFT_GUI,
        OM_SEL3, OM_SEL2, OM_SEL1, OM_HLDS, OM_RELS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_TRANSPARENT, QK_LAYER_LOCK, KC_NO, KC_TRANSPARENT, KC_TRANSPARENT),
};

#define SHIFT_OVERRIDES \
SH( shift_dquote_lpara ,KC_QUOTE, KC_LEFT_PAREN ) \
SH( shift_squote_rpara ,KC_DOUBLE_QUOTE, KC_RIGHT_PAREN ) \
SH( shift_dot_colon ,KC_DOT, KC_COLON ) \
SH( shift_comma_semicolon ,KC_COMMA, KC_SEMICOLON ) \
SH( shift_ques_excl ,KC_QUESTION, KC_EXCLAIM ) \
SH( shift_tab_cword, LT(_MOUSE2, KC_TAB), QK_CAPS_WORD_TOGGLE )

#define ALT_OVERRIDES \
AL( alt_1,KC_1, KC_KP_1 ) \
AL( alt_2,KC_2, KC_KP_2 ) \
AL( alt_3,KC_3, KC_KP_3 ) \
AL( alt_4,KC_4, KC_KP_4 ) \
AL( alt_5,KC_5, KC_KP_5 ) \
AL( alt_6,KC_6, KC_KP_6 ) \
AL( alt_7,KC_7, KC_KP_7 ) \
AL( alt_8,KC_8, KC_KP_8 ) \
AL( alt_9,KC_9, KC_KP_9 ) \
AL( alt_0,KC_0, KC_KP_0 ) 


#define SH(name, key, shiftkey) const key_override_t name = ko_make_basic(MOD_MASK_SHIFT, key, shiftkey);
#define AL(name, key, shiftkey) const key_override_t name = ko_make_basic(MOD_MASK_ALT, key, shiftkey);
SHIFT_OVERRIDES
ALT_OVERRIDES
#undef SH
#undef AL

#define SH(name, key, shiftkey) &name,
#define AL(name, key, shiftkey) &name,
const key_override_t *key_overrides[] = {
SHIFT_OVERRIDES
ALT_OVERRIDES
};
#undef SH
#undef AL

const uint16_t PROGMEM combo_ea[] = {LCTL_T(KC_E), LSFT_T(KC_A), COMBO_END};
const uint16_t PROGMEM combo_th[] = {RSFT_T(KC_H), RCTL_T(KC_T), COMBO_END};
combo_t key_combos[] = {
    COMBO(combo_ea, KC_Q),
    COMBO(combo_th, KC_Z),
};

