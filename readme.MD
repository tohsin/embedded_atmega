# Setup and devices used for this repo
[link](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)

[Programmer 1](http://hub360.com.ng/product/usbisp-avr-programmer/)

Using AVR Boards
man avr-gcc
## Compile
>avr-gcc -mmcu=atmega328 blink.c

## Compile Without linking 
>avr-gcc -c -mmcu=atmega328 helper.c

## Combine Machine Code files
>avr-gcc -mmcu=atmega328 blink.o helper.o

## Optimise diff options 
1. For size
>avr-gcc -mmcu=atmega328 blink.c
## Convert To hex
>avr-objcopy -O ihex -j.text -j.data a.out a.hex 

## Avr dude location
>/Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf

## Flash program to  Chip
avrdude -C /Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -v -p atmega328p -c USBasp -U flash:w:a.hex

## Bash File for all 3 prcoesses
```
chmod +x compile_upload.sh
./compile_upload.sh /path/to/blink.c
```