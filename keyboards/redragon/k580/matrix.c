/*
 * Custom matrix scan for K580 — reads from LED ISR shadow matrix
 * instead of driving GPIO directly (pins are shared with LED controller).
 *
 * CUSTOM_MATRIX = lite means QMK still handles debounce, raw_matrix,
 * and matrix_init — we only override matrix_scan_raw().
 *
 * -----------------------------------------------------------------------
 * OLD GPIO-based matrix scan (preserved for reference — DO NOT DELETE)
 * This is what quantum/matrix.c does for ROW2COL. It cannot coexist with
 * the LED controller because P0/P3/P7 (cols) and P4 (rows) are shared.
 *
 * static void old_matrix_scan_raw(matrix_row_t current_matrix[]) {
 *     matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
 *     for (uint8_t col = 0; col < MATRIX_COLS; col++, row_shifter <<= 1) {
 *         // Drive col pin low
 *         setPinOutput(col_pins[col]);
 *         writePinLow(col_pins[col]);
 *         matrix_output_select_delay();
 *
 *         // Read all row pins
 *         for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
 *             if (readPin(row_pins[row]) == 0) {
 *                 current_matrix[row] |=  row_shifter;
 *             } else {
 *                 current_matrix[row] &= ~row_shifter;
 *             }
 *         }
 *
 *         // Release col pin
 *         setPinInputHigh(col_pins[col]);
 *         matrix_output_unselect_delay(col, false);
 *     }
 * }
 * -----------------------------------------------------------------------
 */

#include "matrix.h"
#include "rgb_matrix_ch555.h"

/*
 * matrix_scan_raw() — called by QMK's matrix_scan() every scan cycle.
 * Translates the ISR-filled led_shadow_matrix[] (col-indexed, row bits)
 * into QMK's row-indexed current_matrix[] format.
 *
 * led_shadow_matrix[col] bit N = 1 means row N is pressed on that col.
 * QMK current_matrix[row] bit col = 1 means that key is pressed.
 */
void matrix_scan_raw(matrix_row_t current_matrix[]) {
    uint8_t col;
    uint8_t row;
    matrix_row_t col_bit;

    for (row = 0; row < MATRIX_ROWS; row++) {
        current_matrix[row] = 0;
    }

    col_bit = 1u;
    for (col = 0; col < MATRIX_COLS; col++, col_bit <<= 1) {
        uint8_t rows = led_shadow_matrix[col];
        for (row = 0; row < MATRIX_ROWS; row++) {
            if (rows & (1u << row)) {
                current_matrix[row] |= col_bit;
            }
        }
    }
}
