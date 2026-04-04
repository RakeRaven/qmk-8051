#ifdef RGB_MATRIX_ENABLE

#include "rgb_matrix.h"
#include "rgb_matrix_ch555.h"

/*
 * QMK rgb_matrix driver for CH555 built-in LED controller.
 *
 * At init, we walk g_led_config.matrix_co to build led_dma_slot[]:
 *   led_dma_slot[led_index] = col * RGB_CH555_ROWS + row
 *
 * This way the driver doesn't need any K580-specific hardcoded tables —
 * g_led_config already knows which (row, col) each LED index belongs to.
 */

static __xdata uint8_t led_dma_slot[RGB_MATRIX_LED_COUNT];

static void ch555_init(void) {
    uint8_t row, col;
    for (row = 0; row < MATRIX_ROWS; row++) {
        for (col = 0; col < MATRIX_COLS; col++) {
            uint8_t idx = g_led_config.matrix_co[row][col];
            if (idx != NO_LED && idx < RGB_MATRIX_LED_COUNT) {
                led_dma_slot[idx] = (uint8_t)(col * RGB_CH555_ROWS + row);
            }
        }
    }
    rgb_matrix_ch555_init();
}

static void ch555_flush(void) {
    /* DMA is continuous — ISR feeds from rgb_dma_buf[] directly. */
}

static void ch555_set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t slot;
    uint8_t intensity;
    if ((uint8_t)index >= RGB_MATRIX_LED_COUNT) return;
    slot      = led_dma_slot[(uint8_t)index];
    intensity = r > g ? (r > b ? r : b) : (g > b ? g : b);
    rgb_dma_buf[slot][0] = intensity;
    rgb_dma_buf[slot][1] = r;
    rgb_dma_buf[slot][2] = g;
    rgb_dma_buf[slot][3] = b;
}

static void ch555_set_color_all(uint8_t r, uint8_t g, uint8_t b) {
    uint8_t i;
    uint8_t intensity = r > g ? (r > b ? r : b) : (g > b ? g : b);
    for (i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        uint8_t slot     = led_dma_slot[i];
        rgb_dma_buf[slot][0] = intensity;
        rgb_dma_buf[slot][1] = r;
        rgb_dma_buf[slot][2] = g;
        rgb_dma_buf[slot][3] = b;
    }
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = ch555_init,
    .flush         = ch555_flush,
    .set_color     = ch555_set_color,
    .set_color_all = ch555_set_color_all,
};

#endif /* RGB_MATRIX_ENABLE */
