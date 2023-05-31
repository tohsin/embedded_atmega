#include <avr/io.h>

int main(){
    // enable output and turn on 
    DDRB |= (1<<PINB5);
    PORTB &= ~(1<<PINB5);

    // enable input and internal resistror
    DDRB &= ~(1<<PINB1);
    PORTB |= (1<<PINB1);
    
    while(1){
        
    }
    return 0;
}