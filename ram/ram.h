/* 
 * Arduino RAM library : interface with 30-pin SIMM RAM modules
 *
 * Copyright (C) 2014 Rafael Ignacio Zurita <rizurita@yahoo.com>
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

#ifdef __cplusplus
 extern "C" {
#endif 

#ifndef RAM_H
#define RAM_H

void ramInit();
void ramRead(unsigned char row, unsigned char col, unsigned char *b);
void ramWrite(unsigned char row, unsigned char col, unsigned char val);
void __vector_13();	//we call it directly :)
	

#endif /* RAM_H */

#ifdef __cplusplus
 }
#endif 

