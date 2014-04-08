#ifdef __cplusplus
 extern "C" {
#endif 

#ifndef RAM_H
#define RAM_H

void ramInit();
void ramRefresh();
void ramRead(unsigned char row, unsigned char col, unsigned char * buf, unsigned char sz);
void ramWrite(unsigned char row, unsigned char col, unsigned char * buf, unsigned char sz);
	

#endif /* RAM_H */

#ifdef __cplusplus
 }
#endif 

