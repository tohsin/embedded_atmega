
[link](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)

[Programmer 1](http://hub360.com.ng/product/usbisp-avr-programmer/)

Using AVR Boards
man avr-gcc
# Compile
>avr-gcc -mmcu=atmega328 blink.c

Without linking 
>avr-gcc -c -mmcu=atmega328 helper.c
-E 
Combine Machine Code files
>avr-gcc -mmcu=atmega328 blink.o helper.o

Optimise diff options 
1.For size
>avr-gcc -mmcu=atmega328 blink.c
# Convert To hex
>avr-objcopy -O ihex -j.text -j.data a.out a.hex 

# Avr dude location
>/Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf


>avrdude -C /Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -v -p atmega328p -c USBasp -U flash:w:a.hex