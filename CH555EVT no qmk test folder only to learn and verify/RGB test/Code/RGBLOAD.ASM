; RGB PWM data load, prepare COMMON pin low for key scan
;
$NOMOD51
#include "CH555.INC"
;
NAME	RGBLOAD
;
?PR?LED_LOAD?RGBLOAD	SEGMENT CODE
;
	PUBLIC	LED_LOAD_XRAM
	PUBLIC	LED_LOAD_CODE
;
				RSEG	?PR?LED_LOAD?RGBLOAD
;
LED_LOAD_XRAM:
;				MOV   A,R7			;load data from XRAM
;				PUSH  ACC
;				MOV   R7,#32/8		;total 32bytes, PWM pins[0~7]*4(intensity,R,G,B)
				SETB  E_DIS			;disable global interrupt for RGB LED DMA
				SETB  P				;copy LED_DMA into DPTR1
LED_XRAM_LOOP:
				MOVX  A,@DPTR		;load 1 byte for PWM pin[0] intensity
				MOVX  A,@DPTR		;load 1 byte for PWM pin[0] R
				MOVX  A,@DPTR		;load 1 byte for PWM pin[0] G
				MOVX  A,@DPTR		;load 1 byte for PWM pin[0] B
				MOVX  A,@DPTR
				MOVX  A,@DPTR
				MOVX  A,@DPTR
				MOVX  A,@DPTR

				MOVX  A,@DPTR
				MOVX  A,@DPTR
				MOVX  A,@DPTR
				MOVX  A,@DPTR
				MOVX  A,@DPTR
				MOVX  A,@DPTR
				MOVX  A,@DPTR
				MOVX  A,@DPTR

				MOVX  A,@DPTR
				MOVX  A,@DPTR
				MOVX  A,@DPTR
				MOVX  A,@DPTR
				MOVX  A,@DPTR
				MOVX  A,@DPTR
				MOVX  A,@DPTR
				MOVX  A,@DPTR

				MOVX  A,@DPTR
				MOVX  A,@DPTR
				MOVX  A,@DPTR
				MOVX  A,@DPTR
				MOVX  A,@DPTR		;load 1 byte for PWM pin[7] intensity
				MOVX  A,@DPTR
				MOVX  A,@DPTR
				MOVX  A,@DPTR
;				DJNZ  R7,LED_XRAM_LOOP
				CLR   E_DIS
;				RET
LED_COM_KEY:	MOV   A,LED_COMMON	;prepare keyboard scan
				JBC   ACC.4,LED_COM_P0P3	;COM16~COM31
				ANL   A,#01H		;COM14/COM15 -> 0/1
				INC   A				;1/2
				CPL   A				;0xFF/0xFE
				DEC   A				;0xFE/0xFD
				ANL   P7,A			;COM14/COM15 action low for keyboard scan
				RET
LED_COM_P0P3:	MOV   R7,A
				ADD   A,R7
				ADD   A,R7			;*3
				MOV   DPTR,#TAB_COM_PIN
				JMP   @A+DPTR
TAB_COM_PIN:	CLR   P0.0
				RET
				CLR   P0.1
				RET
				CLR   P0.2
				RET
				CLR   P0.3
				RET
				CLR   P0.4
				RET
				CLR   P0.5
				RET
				CLR   P0.6
				RET
				CLR   P0.7
				RET
				CLR   P3.0
				RET
				CLR   P3.1
				RET
				CLR   P3.2
				RET
				CLR   P3.3
				RET
				CLR   P3.4
				RET
				CLR   P3.5
				RET
				CLR   P3.6
				RET
				CLR   P3.7
				RET
;
LED_LOAD_CODE:	CLR   A				;for MOVC only
				SETB  E_DIS			;disable global interrupt for RGB LED DMA
				SETB  P				;copy LED_DMA into DPTR1
				MOVC  A,@A+DPTR		;load 4 bytes (intensity,R,G,B) for PWM pin[0]
				MOVC  A,@A+DPTR		;load 4 bytes
				MOVC  A,@A+DPTR		;load 4 bytes
				MOVC  A,@A+DPTR		;load 4 bytes
				MOVC  A,@A+DPTR		;load 4 bytes
				MOVC  A,@A+DPTR		;load 4 bytes
				MOVC  A,@A+DPTR		;load 4 bytes
				MOVC  A,@A+DPTR		;load 4 bytes for PWM pin[7]
				CLR   E_DIS
;				RET
				SJMP  LED_COM_KEY
;
END
