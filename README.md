30pin-simm-ram-arduino
======================

Arrduino library to interface with 30-pin simm ram

Do you want to have plenty of RAM with your atmega328p (Arduino)?

This repo contains the library to interface with 30-pin simm ram module,
like the ones which were used in AT (286), 386, 486, Macintosh Plus, 
Macintosh II, Quadra, Atari STE and Wang VS systems.

The library has two versions : C and avr assembler version. Both for
atmega328p (Arduino).

It will give you plenty of RAM to store dynamic data to your sketches.

WARNING: using this kind of RAM will put your CPU to refresh the SIMM RAM data
most of the time. It means that your sketches (programs) could run slow.
Also, we need to use most of the Arduino pins to be soldered with SIMM RAM pins
so there will be just few available extra pins for your project.

Usage :

Connect the 30-pin SIMM RAM like schematic.txt file explains.

Copy the ram/ directory under sketchbook/libraries/.
If you prefer using the avr assembler version for better performance
copy the files under avr-asm-ram-version/* instead. Read the REAMDE
file there as well.

The usage of the RAM is easy. In your main code (or sketch) call ramInit()
just once, and then ramRead() and ramWrite() to store and recover
data from SIMM RAM.

Example :

ram_init();
ram_write(1, 2, 7);		/*# row=1, col=2, store byte = 7 */

char gb[] = "Good Bye!"
for (i=0, i<strlen(gb), i++)
	ram_write(2, i, gb[i]);	/* row=2, col=i, store byte = i of gb */

c = ram_read(1, 2);		/* restore byte = 7 from row=1, col=2 */
d = ram_read(2, 0);		/* restore letter "G" from row=2, col=0 */
	

You can use the ram_test.ino as example for using your 30-pin simm ram.
