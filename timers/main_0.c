#include <avr/io.h>
#include <util/delay.h>
//function decleration
void myDelay();


int 
main(){
    DDRB = 0x3F;/// setting all except secound to last and last bits to output

    while(1){
        PORTB = 0x2A;
        myDelay();
        //  _delay_ms(5000);
        PORTB = 0x15;
        // _delay_ms(5000);
        myDelay();
    }
    return 0;   
}

void 
myDelay(){
    TCNT0 = 0x20;   //Load TCNT0 : set it to 32 ticks 0x22 = 32 in decimal
    TCCR0B = 0x01;//Set Timer/Counter Control Register 0 to 0x01 (specific configuration)
    while ((TIFR0 & (1 << TOV0)) == 0 ); //check the flag for 
    TCCR0B = 0; // stop timer 
    TIFR0 = (1<<TOV0); // set flag back to false
        /* code */
    
}