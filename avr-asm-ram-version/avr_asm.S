
.globl ramRead
ramRead:
		
	; argumentos de funciones r24 es byte 0, r25 byte 1, r22 byte 3, r23 byte4, etc
	; r24 es fila (row)
	; r22 es columna (col)
	; Rafa r20 es buf
	
	movw r26, r20
	
	
	in r25, 0x3F	;r25 = SREG
	cli
	
	out 0x05, r24	;PORTA = rB
	cbi 0x08, 2	;PIND = (1 << 7)	;nRAS

	out 0x05, r22	;PORTA = cB
	
	cbi 0x08, 0	;PINB = (1 << 4)	;nCAS
	
	sbi 0x08, 2	;PIND = (1 << 7)	;nRAS
	sbi 0x08, 0	;PINB = (1 << 4)	;nCAS

	; Rafa Leemos el dato y lo colocamos en el espacio buf
	in r24, 0x09	;r24 = PINC
	st X, r24
	
	out 0x3F, r25	;restore SREG

	
	ret

.globl ramWrite
ramWrite:
	
	; argumentos de funciones r24 es byte 0, r25 byte 1, r22 byte 3, r23 byte4, etc
	; r24 es fila (row)
	; r22 es columna (col)
	; r20 es el byte a guardar en memoria

	in r25, 0x3F	;r25 = SREG
	cli
	
	ldi r18, 0xFF
	out 0x0A, r18	;PORTC is output
	
	out 0x05, r24	;PORTA = rB
	cbi 0x08, 2	;PIND = (1 << 7)	;nRAS

	out 0x0b, r20	;PORTC = val

	cbi 0x08, 1	;PINB = (1 << 5)	;nWE

	out 0x05, r22	;PORTA = cB
	cbi 0x08, 0	;PINB = (1 << 4)	;nCAS
	
	
	sbi 0x08, 0	;PINB = (1 << 4)	;nCAS
	sbi 0x08, 1	;PINB = (1 << 5)	;nWE
	nop
	sbi 0x08, 2	;PIND = (1 << 7)	;nRAS
	
	out 0x0A, r1	;PORTC is input
	
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
	
	cbi 0x08, 0	;PINB = (1 << 4)	;nCAS
	cbi 0x08, 2	;PIND = (1 << 7)	;nRAS
	inc r25
	sbi 0x08, 0	;PINB = (1 << 4)	;nCAS
	sbi 0x08, 2	;PIND = (1 << 7)	;nRAS
	
	brne ramRefreshLoop
	
	inc r24
	brne ramRefreshLoop
	
	out 0x3F, r23
	pop r23
	pop r24
	pop r25
	reti
