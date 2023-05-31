#define number_buttons 1
#include <avr/io.h>
#include "buttonpress.h"
#include <avr/interrupt.h>

int main(){
    DDRB |= (1 << PINB5); // enable output for LED
    DDRB |= (1 << PINB4); // enable output for LED
    DDRB &= ~(1 << PINB1); // set the pinB1 which has a pin going to one side of a button
    PORTB |= (1 << PINB1); // using inbuilt resistor
    PORTB ^= (1 << PINB4); // turn PINB4 on 

    while(1){
        if(ButtonPressed(0, PINB, PINB1, 100)){
            PORTB ^= (1 << PINB4); // turn PINB4 on 
            PORTB ^= (1 << PINB5); // turn PINB4 on 
           
        }  
    }
    return 0;
}