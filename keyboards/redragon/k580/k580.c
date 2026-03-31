/* SPDX-License-Identifier: GPL-2.0-or-later */

#include "k580.h"
#include "config.h"
#include "led.h"
#include "gpio.h"

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        setPinOutput(LED_NUM_LOCK_PIN);
        setPinOutput(LED_CAPS_LOCK_PIN);
        setPinOutput(LED_SCROLL_LOCK_PIN);
        writePin(LED_NUM_LOCK_PIN,    !led_state.num_lock);
        writePin(LED_CAPS_LOCK_PIN,   !led_state.caps_lock);
        writePin(LED_SCROLL_LOCK_PIN, !led_state.scroll_lock);
    }
    return res;
}
