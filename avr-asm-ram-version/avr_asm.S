;
; Arduino RAM library : interface with 30-pin SIMM RAM modules
;
; Copyright (C) 2014 Rafael Ignacio Zurita <rafaelignacio.zurita@gmail.com>
;
; This ram library is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 2 of the License, or
; (at your option) any later version.

; interface with 30-pin SIMM RAM using atmega328p on Arduino

.globl ram_read
ram_read:
		
	; argumentos de funciones r24 es byte 0, r25 byte 1, r22 byte 3, r23 byte4, etc
	; r24 es fila (row)
	; r22 es columna (col)
	; REMOVED! r20 es buf
	
	; movw r26, r20
	
	in r25, 0x3F	;r25 = SREG
	cli
	
	out 0x05, r24	;PORTC = row
	cbi 0x08, 2	;nRAS

	out 0x05, r22	;PORTB = col
	
	cbi 0x08, 0	;nCAS
	
	sbi 0x08, 2	;nRAS
	sbi 0x08, 0	;nCAS

	; Leemos el dato y lo colocamos en el espacio buf
	in r24, 0x09	;r24 = PIND data
	;st X, r24
	
	out 0x3F, r25	;restore SREG
	
	ret


.globl ram_write
ram_write:
	
	; argumentos de funciones r24 es byte 0, r25 byte 1, r22 byte 3, r23 byte4, etc
	; r24 es fila (row)
	; r22 es columna (col)
	; r20 es el byte a guardar en memoria

	in r25, 0x3F	;r25 = SREG
	cli
	
	ldi r18, 0xFF
	out 0x0A, r18	;PORTD is output
	
	out 0x05, r24	;PORTB = row
	cbi 0x08, 2	;nRAS

	out 0x0b, r20	;PORTD = val (data byte to store)

	cbi 0x08, 1	;nWE

	out 0x05, r22	;PORTB = col
	cbi 0x08, 0	;nCAS
	

	sbi 0x08, 0	;nCAS
	sbi 0x08, 1	;nWE
	nop
	sbi 0x08, 2	;nRAS
	
	out 0x0A, r1	;PORTD is input
	
	out 0x3F, r25	;restore SREG
	
	ret
	
; el refresh que sucede cada 62ms
.globl __vector_13		;refresh = TIMER1_COMPA_vect
__vector_13:
	
	push r25
	push r24
	push r23
	
	in r23, 0x3F
	
	clr r25
	ldi r24, -16	;do it 16 times
	
ramRefreshLoop:
	
	cbi 0x08, 0	;nCAS
	cbi 0x08, 2	;nRAS
	inc r25
	sbi 0x08, 0	;nCAS
	sbi 0x08, 2	;nRAS
	
	brne ramRefreshLoop
	
	inc r24
	brne ramRefreshLoop
	
	out 0x3F, r23
	pop r23
	pop r24
	pop r25
	reti
