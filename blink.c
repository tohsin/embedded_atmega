// #include <avr/io.h>
// #include <util/delay.h>
// // #define PORTB *((volatile unsigned char*) 0x25)
// // #define DDRB *((volatile unsigned char*) 0x24)



// int main(){
//     DDRB |= (1 << 5); //red led 
//     DDRB |= (1 << 4); //green led
//     while(1){
            
//         PORTB |= 1<<5;
//         PORTB &= ~(1<<4);
//         _delay_ms (10000);


//         PORTB &= ~(1<<5);
//         _delay_ms (10000);
//         PORTB |= 1<<4;

//     }
// }

#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 10000

int main(void) {
    DDRB |= (1 << PB4) | (1 << PB5);  // Set PB4 and PB5 as output

    while (1) {
        // turn on PB5 and turn off PB4
        PORTB |= (1 << PB5);
        PORTB &= ~(1 << PB4);
        _delay_ms(BLINK_DELAY_MS);

        // Turn off PB5 and turn on PB4
        PORTB &= ~(1 << PB5);
        PORTB |= (1 << PB4);
        _delay_ms(BLINK_DELAY_MS);
        
        // Turn off both PB4 and PB5
        PORTB &= ~((1 << PB4) | (1 << PB5));
        _delay_ms(BLINK_DELAY_MS);
        
    }

    return 0;
}
