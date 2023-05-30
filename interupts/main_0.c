#include <avr/io.h>
#include <avr\interrupt.h>
#include <util/delay.h>
#define pin5 0x20

int main(){
    sei() //enable interrupts
    DDRB |= 0x20; //00100000 enable pin5
    TCNT0 = -32; //4 micro secs
    TCCR0B = 0x01 //  normal mode, no prescaler, int clk 
    TIMSK = (1<<TOIEO) //enable Timer0 overflow interrupt

    DDRC = 0x00; //make port C input
    DDRD = 0xFF; //make PortD Outputs
    while (1)
        PORTD = PINC;

    
    return 0;
}

ISR(TIMERO_OF_vect){ //isr for  timer0 interrupt
    TCNT0 = -32; // reset clock
    PORTB ^= 0x20; //toggle PORTB.5
}