/*
Rising Edge: If you want the interrupt to be triggered when the button is pressed
 (transitioning from LOW to HIGH), you would use the rising edge triggering mode.

Falling Edge: If you want the interrupt to be triggered when the button is released 
(transitioning from HIGH to LOW), you would use the falling edge triggering mode.
*/


#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
// Built for ATMEGA328

int main() {
    DDRB |= (1 << PINB5); // enable output for LED

    DDRD &= ~(1 << PIND2); // set the pinB1 which has a pin going to one side of a button
    PORTD |= (1 << PIND2); // using inbuilt resistor

    EICRA |= (1 << ISC01) | (1 << ISC00);  // Set interrupt to trigger on rising edge
    EIMSK |= (1 << INT0);  // Enable external interrupt 0
    PORTB ^= (1 << PINB5);
    sei(); // enable global interrupts
    while (1){
        //
    }
    return 0;
}
ISR(INT0_vect){
    PORTB ^= (1 << PINB5); // turn PINB4 on 
    _delay_ms(50); // add delay for debouncing
}