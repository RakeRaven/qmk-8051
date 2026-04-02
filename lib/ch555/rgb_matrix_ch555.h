#pragma once
#include <stdint.h>
#include "ch555.h"

/*
 * CH555 RGB LED controller driver — K580 Vata
 *
 * 18 COMs (datasheet COM16–COM33, i.e. P0.0–P0.7, P3.0–P3.7, P7.0–P7.1)
 * 6 PWM rows (P4.0–P4.5 red, P2.0–P2.5 green, P1.0–P1.5 blue)
 * DMA buffer: [108][4] = intensity, R, G, B per LED slot
 * Slot index = col * 6 + row  (col 0–17, row 0–5)
 *
 * Key scan is performed inside the LED ISR by briefly switching P4 to
 * input mode on each COM advance. Results stored in led_shadow_matrix[].
 * QMK matrix_scan_raw() reads from led_shadow_matrix[] instead of GPIO.
 */

#define RGB_CH555_COLS      18u
#define RGB_CH555_ROWS      8u   /* hardware has 8 PWM rows; rows 0-5 = keys, 6-7 = future */
#define RGB_CH555_LED_COUNT (RGB_CH555_COLS * RGB_CH555_ROWS)  /* 144 */

/* Shadow matrix: one entry per column, bits 0–5 = rows 0–5, 1 = pressed */
extern volatile uint8_t led_shadow_matrix[RGB_CH555_COLS];

/* DMA buffer in xRAM — [slot][channel]: 0=intensity, 1=R, 2=G, 3=B */
extern __xdata uint8_t rgb_dma_buf[RGB_CH555_LED_COUNT][4];

/* Call once from keyboard_post_init or protocol_post_init */
void rgb_matrix_ch555_init(void);
