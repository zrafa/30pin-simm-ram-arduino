30pin-simm-ram-arduino
======================

Library to interface with 30-pin simm ram using an atmega328p on Arduino

Copyright (C) 2014 - Rafael Ignacio Zurita <rafaelignacio.zurita@gmail.com>
LICENSE : read below.

**This project got a got article in HACKADAY!** : http://hackaday.com/2014/04/09/using-simms-to-add-some-extra-ram-on-your-arduino-uno

Introduction
------------

This repo contains the library to interface with 30-pin simm ram modules,
like the ones which were used in AT (286), 386, 486, Macintosh Plus, 
Macintosh II, Quadra, Atari STE and Wang VS systems. Using an atmega328p on
Arduino.

It will give you extra RAM to store and restore dynamic data 
in your sketches.

__Pictures and Video__ : on the bottom

This work was inspired and based for the great hack to run Linux
on a 8bit MCU by Dmitry Grinberg
http://dmitry.gr/index.php?r=05.Projects&proj=07.%20Linux%20on%208bit

The code is also based in the __KM41C4000D 4M x 1Bit CMOS Dynamic RAM datasheet__ http://pdf.datasheetcatalog.com/datasheets/400/250350_DS.pdf

License
-------

The library has two versions : C and avr assembler version. Both for
atmega328p (Arduino).

Both version are free software, you can redistribute it and/or modify
it under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

Read the LICENSE file for details, and the README file under the assembler
version directory.


Usage
-----

WARNING: using this kind of RAM will put your Arduino CPU to refresh the SIMM RAM
data part of the time. It means that your sketches (programs) could run 
a little slower than before.
Also, we need to use most of the Arduino pins to be soldered with SIMM RAM pins
so there will be just few available extra pins for your project.

 1. Connect the 30-pin SIMM RAM like schematic.txt file explains.

 2. Copy the ram/ directory under sketchbook/libraries/.
If you prefer using the avr assembler version for better performance
copy the files under avr-asm-ram-version/* instead. Read the REAMDE
file there as well.

 3. The usage of the RAM is easy. In your main code (or sketch) call ram_init()
just once, and then ram_write() and ram_read() to store and recover
data from SIMM RAM.


Example
-------

```
#include "ram.h"
...

ram_init();

/* write one byte to RAM */
ram_write(1, 2, 7);		/*# row=1, col=2, store byte = 7 */

/* write several bytes to RAM */
char gb[] = "Good Bye!";
for (i=0, i<strlen(gb), i++)
	ram_write(2, i, gb[i]);	/* row=2, col=i, store byte = i of gb */

/* read from RAM */
c = ram_read(1, 2);		/* restore byte = 7 from row=1, col=2 */
d = ram_read(2, 0);		/* restore letter "G" from row=2, col=0 */
	
```

You can use the ram_test.ino as example for using your 30-pin simm ram.


Limitations
-----------

SIMM RAM has 12 bit address for rows and columns. Max RAM size here
is 16MB. We are using just 6 pins for rows and columns, so we
are limited to 4KB of RAM space.

Addresses space will be of 64rows x 64columns = 4096 addresses
1 byte each = 4KB of space.

If you need to use more RAM you can solder the 3 analog pins remaining
to simm ram module pins A6, A7 and A8. It will give you 256 KB of RAM space.


References
----------

Dmitry code for atmega168 did not work as is.
In order to have a proper working code we needed to read several
datasheets. At least we studied the KM41C4000D, KM41V4000D CMOS DRAM 
datasheet and other sources of RAM chips, like 

http://www.pjrc.com/mp3/simm/datasheet.html 
and
http://www.pjrc.com/mp3/simm/simm.html

__KM41C4000D 4M x 1Bit CMOS Dynamic RAM datasheet__ http://pdf.datasheetcatalog.com/datasheets/400/250350_DS.pdf

Pics
----

<img src="https://github.com/zrafa/zrafa.github.io/blob/master/ram-atmega328p-arduino/ram-arduino-sch.jpg?raw=true" alt="simm ram and atmega328p" width="500" height="400">
<img src="https://github.com/zrafa/zrafa.github.io/blob/master/ram-atmega328p-arduino/ram-arduino3.jpg?raw=true" alt="simm ram and atmega328p" width="400" height="300">
<img src="https://github.com/zrafa/zrafa.github.io/blob/master/ram-atmega328p-arduino/ram-arduino2.jpg?raw=true" alt="simm ram and atmega328p" width="400" height="300">
<img src="https://github.com/zrafa/zrafa.github.io/blob/master/ram-atmega328p-arduino/ram-arduino.jpg?raw=true" alt="simm ram and atmega328p" width="400" height="300">


Video
-----

<a href="http://www.youtube.com/watch?feature=player_embedded&v=Yah3ViEggxA"
target="_blank"><img src="http://img.youtube.com/vi/Yah3ViEggxA/0.jpg" 
alt="arduino interfacing with simm ram module" width="320" height="240" border="10" /></a>


