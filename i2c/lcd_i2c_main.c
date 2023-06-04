/*
using 20 x 4 LCD 
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


#define i2cAdress 0x27
#define Cntrl_i2c TWCR



int main(void){
    initalise_i2c();
   
    while (1)
    {
        /* code */
    }
    
    return 0;
}
void send_command_lcd(unsigned char cmnd){
   
}

void write_lcd(unsigned char data) {
    // Set RS = 1, RW = 0, E = 1 (enable high)
    unsigned char upperNibble = data & 0xF0;
    write_i2c(upperNibble | 0x05);
    _delay_us(1);  // Delay for enable pulse width

    // Set E = 0 (enable low)
    write_i2c(upperNibble);
    _delay_us(1);  // Small delay before writing the lower nibble

    // Set E = 1 (enable high)
    unsigned char lowerNibble = (data & 0x0F) << 4;
    write_i2c(lowerNibble | 0x05);
    _delay_us(1);  // Delay for enable pulse width

    // Set E = 0 (enable low)
    write_i2c(lowerNibble);
    _delay_us(100);  // Delay for data write time
}

void set_cursor(uint8_t col, uint8_t row){
    int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
}




