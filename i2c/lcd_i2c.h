//rs is p0 ,rw = p1 e = p2 is P1 D4-D7 = P4 to P7
//rw is on ground 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void intialise_lcd_i2c(){
    send_higher_bit(0x30);
    send_higher_bit(0x30);
    send_higher_bit(0x30);
    send_higher_bit(0x20);
}
void send_command_lcd(unsigned char cmnd){

    send_higher_bit(cmd);
    // lets start lower bits buisness
    TWDR &= 0x0F; //clear higher bits thats what we use to send information
    wait_send();
    TWDR |= ((cmnd & 0x0F)<<4); // write the lower bits of cmnd (mask ) to the higher bits of TWDR
    wait_send();
    toggle_enable(); //send H to L pulse

}

void send_higher_bit(unsigned char cmd, ){
    TWDR  &= ~0x01; //set rs = 0 Cmnd mode
    wait_send();
    TWDR  &= 0x0F; //clear higher bits make them zero
    wait_send();
    TWDR |= (cmnd & 0xF0); //write the higer bits of cmnd (mask ) to the higher bits of twdr 
    wait_send();
    toggle_enable(); //sends H to L pulse
}

void wait_send(){
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1<<TWINT)));
}

void lcd_send_data(char cmd){
    TWDR  |= 0x01; //set rs = 1 data mode
    wait_send();

    TWDR  &= 0x0F; //clear higher bits make them zero
    wait_send();
    TWDR |= (cmnd & 0xF0); //write the higer bits of cmnd (mask ) to the higher bits of twdr 
    wait_send();
    toggle_enable(); //sends H to L pulse

    TWDR &= 0x0F; //clear higher bits thats what we use to send information
    wait_send();
    TWDR |= ((cmnd & 0x0F)<<4); // write the lower bits of cmnd (mask ) to the higher bits of TWDR
    wait_send();
    toggle_enable(); //send H to L pulse

}

void toggle_enable(){
    // for latching  read LCD datasheet
    TWDR |= 0x04;
    wait_send();
    _delay_us(1);

    TWDR &= ~(0x04); //H to L toggle
    wait_send(); 
    _delay_us(20);
}

void lcd_print(char *c)
{
	while(*c != 0)      //----Wait till all String are passed to LCD
	lcd_send_data(*c++);		//----Send the String to LCD
}

