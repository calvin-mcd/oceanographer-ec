#include "oceanographer_ec.h"

extern ecsm_config_t ecsm_config;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    #ifdef EC_MATRIX
    if (record->event.pressed) {
        switch(keycode) {
            case EC_AP_I:
                ecsm_ap_inc();
                return false;
            case EC_AP_D:
                ecsm_ap_dec();
                return false;
            case EC_CLR:
                ecsm_eeprom_clear();
                return false;
        }
    }
    #endif

    return process_record_user(keycode, record);
};

void keyboard_post_init_kb(void) {
    #ifdef ECSM_TUNE_ON_BOOT
        ecsm_config.configured = 0;
        eeconfig_update_kb_datablock(&ecsm_config);
    #endif
    keyboard_post_init_user();
}


/*oled orientation and logo*/

#ifdef OLED_ENABLE

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_90;
}

void render_logo(void) {
    // QMK Logo
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(qmk_logo, false);
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    render_logo();
    return false;
}
#endif
