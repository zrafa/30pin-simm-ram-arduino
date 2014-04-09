/* 
 * Arduino RAM library : interface with 30-pin SIMM RAM modules
 *
 * Copyright (C) 2014 Rafael Ignacio Zurita <rafaelignacio.zurita@gmail.com>
 *
 *  This ram library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this software (check COPYING); if not, write to the Free
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#include <Arduino.h>
#include <avr/wdt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/boot.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>

void __vector_13() {
	int cycles = 4096;

	do{
		PORTC = PORTC & B11111110;	/* CAS = 0 */
		PORTC = PORTC & B11111011;	/* RAS = 0 */
		PORTC = PORTC | B00000001;	/* CAS = 1 */
		PORTC = PORTC | B00000100;	/* RAS = 1 */
	}while(--cycles);
}

unsigned char ram_read(unsigned char row, unsigned char col) {
	
	unsigned char buf;

	cli();

	PORTB = row;
	PORTC = PORTC & B11111011;	/* RAS = 0 */

	PORTB = col;
	PORTC = PORTC & B11111110;	/* CAS = 0 */

	PORTC = PORTC | B00000100;	/* RAS = 1 */
	PORTC = PORTC | B00000001;	/* CAS = 1 */

	buf = PIND;
	sei();

	return buf;
}


void ram_write(unsigned char row, unsigned char col, unsigned char val) {
	
	cli();

	DDRD = B11111111;		/* DATA output */

	PORTB = row;
	PORTC = PORTC & B11111011;	/* RAS = 0 */

	PORTD = val;

	PORTC = PORTC & B11111101;	/* WE = 0 */

	PORTB = col;
	PORTC = PORTC & B11111110;	/* CAS = 0 */

	PORTC = PORTC | B00000001;	/* CAS = 1 */
	PORTC = PORTC | B00000010;	/* WE = 1 */
	//asm("nop");
	PORTC = PORTC | B00000100;	/* RAS = 1 */

	DDRD = B00000000;		/* DATA input */
	sei();
}

void ram_init() {
	cli();

	asm("cli");

	/* timer for refresh */
	TCCR1A = 0x00;
	TCCR1B = 0x0B;		//reset on match with OCR1A, clk= clk/64 -> overflow every 13.1 ms (faster than 4x as fast as we need to refresh)
	OCR1A = 0x493E;		//match every 60ms
	TIMSK1 = 2;		//interrupt when we match

	/* conf RAM port */
	DDRB |= 0x3F;	//out: A0..A7
	PORTB |= 0xC0;	//lo: A0..A7    - portb 0x25  -  
	DDRC |= 0x04;	//out: nRAS
	DDRC |= 0x02;	//out: nWE
	DDRC |= 0x01;	//out: nCAS
	DDRC |= 0x08;	//out: led
		
	PORTC |= 0x04;	//hi: nRAS    - 0x28 - pinc 0x06
	PORTC |= 0x01;	//hi: nCAS
	PORTC |= 0x02;	//hi: nWE

	DDRD &= 0x00;	//in:  D0..D7
	PORTD = 0x00;	//no pullups: data  portd 0x2b - pind 0x09

	unsigned char t;
	
	/* init SIMM RAM */
	_delay_us(200);	//as per init instructions
	for(t = 0; t < 8; t++) __vector_13();
	
	sei();	//enable refresh
}


