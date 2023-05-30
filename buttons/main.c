#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>


// Built for ATMEGA328
int main() {
    DDRB |= (1 << PINB5); // enable output for LED
    DDRB |= (1 << PINB4); // enable output for LED
    DDRB &= ~(1 << PINB1); // set the pinB1 which has a pin going to one side of a button
    PORTB |= (1 << PINB1); // using inbuilt resistor
    PORTB ^= (1 << PINB4); // turn PINB4 on 

    uint8_t is_pressed = 0;
    while (1) {
        // when pressed toggle and switch LEDs so one goes off, and the other goes on
        if (!(PINB & (1 << PINB1))) { // if button is pressed
            if (is_pressed == 0) { // button was off
                _delay_ms(10); // debounce delay
                if (!(PINB & (1 << PINB1))) { // recheck button state after delay
                    PORTB ^= (1 << PINB4); // turn PINB4 on 
                    PORTB ^= (1 << PINB5); // turn PINB4 on 
                    is_pressed = 1;
                }
            }
        } else {
            // do nothing to the LEDs
            is_pressed = 0;
        }
    }
    
    return 0;
}