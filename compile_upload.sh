#!/bin/bash

if [ $# -eq 0 ]; then
    echo "No file path provided. Usage: ./compile_upload.sh <filepath>"
    exit 1
fi

filepath=$1
output="a.out"
hexfile="a.hex"

# Get the directory and filename
dirname=$(dirname "$filepath")
filename=$(basename "$filepath")

# Compile the source code
avr-gcc -mmcu=atmega328 "$filepath" -o "$output"

# Convert to Intel HEX format
avr-objcopy -O ihex -j .text -j .data "$output" "$hexfile"

# Upload the HEX file to the microcontroller using avrdude
avrdude -C /Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -v -p atmega328p -c USBasp -U flash:w:"$hexfile"

# Clean up temporary files
rm "$output" "$hexfile"


