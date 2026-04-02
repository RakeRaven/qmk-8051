;
; rgbload.asm — SDCC sdas8051 port of WCH RGBLOAD.ASM
;
; Clocks one column worth of LED data (8 rows × 4 bytes = 32 bytes) from
; xRAM into the CH555 LED PWM engine via the dual-DPTR DMA mechanism.
;
; How the CH555 DMA works:
;   SETB E_DIS  — disables global interrupts (IE.6, bit addr 0xAE)
;   SETB P      — PSW.0; on CH555 this copies LED_DMA register into DPTR,
;                 and enables "shadow feed" mode: every subsequent
;                 MOVX A,@DPTR also clocks that byte into the LED engine.
;                 LED_DMA auto-increments after each fed byte.
;   32x MOVX    — reads xRAM sequentially, hardware absorbs each byte.
;   CLR E_DIS   — re-enable interrupts.
;
; Called from LED_INT (C ISR) once per COM column advance.
; DPTR is set by SETB P from LED_DMA, so no setup needed by caller.
;
; CH555 bit addresses used:
;   E_DIS = IE.6  = 0xAE   (inhibit interrupts, independent of EA)
;   P     = PSW.0 = 0xD0
;

.module RGBLOAD

.globl _LED_LOAD_XRAM

.area RGBLOAD_CODE (CODE)

_LED_LOAD_XRAM:
    setb  0xae              ; E_DIS — disable global interrupt

    setb  0xd0              ; P — load DPTR from LED_DMA, arm DMA feed

    ; row 0: intensity, R, G, B
    movx  a,@dptr
    movx  a,@dptr
    movx  a,@dptr
    movx  a,@dptr
    ; row 1
    movx  a,@dptr
    movx  a,@dptr
    movx  a,@dptr
    movx  a,@dptr
    ; row 2
    movx  a,@dptr
    movx  a,@dptr
    movx  a,@dptr
    movx  a,@dptr
    ; row 3
    movx  a,@dptr
    movx  a,@dptr
    movx  a,@dptr
    movx  a,@dptr
    ; row 4
    movx  a,@dptr
    movx  a,@dptr
    movx  a,@dptr
    movx  a,@dptr
    ; row 5
    movx  a,@dptr
    movx  a,@dptr
    movx  a,@dptr
    movx  a,@dptr
    ; row 6 (zeros — macro/media LEDs, not yet driven)
    movx  a,@dptr
    movx  a,@dptr
    movx  a,@dptr
    movx  a,@dptr
    ; row 7 (zeros — underglow, not yet driven)
    movx  a,@dptr
    movx  a,@dptr
    movx  a,@dptr
    movx  a,@dptr

    clr   0xae              ; CLR E_DIS — re-enable global interrupt
    ret

.end
