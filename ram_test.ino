#include "ram.h"

/* 
 * RAM test : Test a SIMM RAM module with the ram library for Arduino
 *
 * Copyright (C) 2014 Rafael Ignacio Zurita <rafaelignacio.zurita@gmail.com>
 *
 *  This ram test is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this software (check COPYING); if not, write to the Free
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


 
char texto[80];
unsigned char i;
unsigned char j;
unsigned char buf;

unsigned char v[100];
char st[] = "This is a test\n";


void setup()  {

	ram_init();
  

	/* write 4K */
	for (i=0;i<64;i++)
	for (j=0;j<64;j++)
		ram_write(i, j, j);

	/* read 4K */
	for (i=0;i<64;i++)
	for (j=0;j<64;j++)
		buf = ram_read(i, j);

	/* write at row=62 the text "This is a text\n" */
	for (i=0;i<strlen(st);i++)
		ram_write(62, i, (unsigned char) st[i]);

	/* read row=62 */
	for (i=0;i<strlen(st);i++)
		v[80+i] = ram_read(62, i);


	/* read row=63 */
	for (i=0;i<64;i++)
		v[i] = ram_read(63, i);


	/* stop ram interrupts */
	TIMSK1 &= ~(1<<OCIE1A); 

	Serial.begin(115000); 

	for (i=0;i<64;i++) {
		sprintf(texto, "Testing RAM readings : %0x ", v[i]);
		Serial.println(texto);
	}

	sprintf(texto, "Testing RAM readings : %s", &v[80]);
	Serial.println(texto);
}


void loop(void) {

	delay(1000);
}

