30pin-simm-ram-arduino
======================

Arrduino library to interface with 30-pin simm ram

This is a C version of a library to interface with 30-pin simm ram module
which were used in AT (286), 386, 486, Macintosh Plus, Macintosh II, Quadra,
Atari STE and Wang VS systems.

It will give you plenty of RAM to store dynamic data to your sketchest.

WARNING: using this kind of RAM will put your CPU to refresh the SIMM RAM data
most of the time. It means that your sketches (programs) could be slow.
Also, we need to use most of the Arduino pins to be soldered with SIMM RAM pins
so there will be just few available extra pins for your project.

Usage :

Connect the 30-pin SIMM RAM like schematic.txt file explains.

Copy the ram/ directory under sketchbook/libraries/.
If you want to use the avr assembler version for better performance
copy the files under avr-asm-ram-version/* instead. Read the REAMDE
file there as well.


Use the ram_test.ino as example to control your 30-pin simm ram.
