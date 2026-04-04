#ifdef RGB_MATRIX_ENABLE

#include "rgb_matrix.h"
#include "config_led.h"

/*
 * LED indices are numbered row-major, left to right, top to bottom,
 * skipping KC_NO positions:
 *
 *   row 0 — 18 keys → LEDs   0–17
 *   row 1 — 18 keys → LEDs  18–35
 *   row 2 — 18 keys → LEDs  36–53
 *   row 3 — 17 keys → LEDs  54–70  (col 12 = KC_NO)
 *   row 4 — 16 keys → LEDs  71–86  (col 1 and col 12 = KC_NO)
 *   row 5 — 17 keys → LEDs  87–103 (col 17 = KC_NO)
 *   row 6 — macro keys (G1–G6), no RGB LEDs
 *   row 7 — media keys, no RGB LEDs
 *
 * TODO: x/y positions are placeholder (evenly spread).
 *       Calibrate by flashing a test pattern once RGB is confirmed working.
 */

led_config_t g_led_config = { {
    /* matrix_co[MATRIX_ROWS=8][MATRIX_COLS=18] */

    /* row 0 */ {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17 },
    /* row 1 */ { 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 },
    /* row 2 */ { 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53 },
    /* row 3 */ { 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, NO_LED, 66, 67, 68, 69, 70 },
    /* row 4 */ { 71, NO_LED, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, NO_LED, 82, 83, 84, 85, 86 },
    /* row 5 */ { 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102,103, NO_LED },
    /* row 6 — macro keys (G1–G6), no RGB */
                { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
                  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    /* row 7 — media keys, no RGB */
                { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
                  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
}, {
    /* point[104] — physical (x, y) positions, placeholder evenly spread.
     * x: 0–224 across 18 cols, y: 0–64 across 6 rows. */

    /* row 0, y=0  */
    {  0,0},{13,0},{26,0},{39,0},{52,0},{65,0},{79,0},{92,0},{105,0},{118,0},{131,0},{144,0},{158,0},{171,0},{184,0},{197,0},{210,0},{224,0},
    /* row 1, y=12 */
    {  0,12},{13,12},{26,12},{39,12},{52,12},{65,12},{79,12},{92,12},{105,12},{118,12},{131,12},{144,12},{158,12},{171,12},{184,12},{197,12},{210,12},{224,12},
    /* row 2, y=25 */
    {  0,25},{13,25},{26,25},{39,25},{52,25},{65,25},{79,25},{92,25},{105,25},{118,25},{131,25},{144,25},{158,25},{171,25},{184,25},{197,25},{210,25},{224,25},
    /* row 3, y=38 — col 12 (x=158) skipped */
    {  0,38},{13,38},{26,38},{39,38},{52,38},{65,38},{79,38},{92,38},{105,38},{118,38},{131,38},{144,38},          {171,38},{184,38},{197,38},{210,38},{224,38},
    /* row 4, y=51 — col 1 (x=13) and col 12 (x=158) skipped */
    {  0,51},        {26,51},{39,51},{52,51},{65,51},{79,51},{92,51},{105,51},{118,51},{131,51},{144,51},          {171,51},{184,51},{197,51},{210,51},{224,51},
    /* row 5, y=64 — col 17 (x=224) skipped */
    {  0,64},{13,64},{26,64},{39,64},{52,64},{65,64},{79,64},{92,64},{105,64},{118,64},{131,64},{144,64},{158,64},{171,64},{184,64},{197,64},{210,64}
}, {
    /* flags[104] — LED_FLAG_KEYLIGHT (4) for all, gaps aligned with NO_LED positions */

    /* row 0 */  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    /* row 1 */  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    /* row 2 */  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    /* row 3 */  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4, 4, 4, 4, 4,
    /* row 4 */  4,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4, 4, 4, 4, 4,
    /* row 5 */  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
} };

#endif /* RGB_MATRIX_ENABLE */
