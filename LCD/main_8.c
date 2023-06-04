/*
using 20 x 4 LCD 
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LCD_Data_PORT PORTD // my data port
#define LCD_Data_DDR DDRD //DR data port
#define LCD_Data_PIN PIND //data pin

#define LCD_Comm_DDR DDRB // command port
#define LCD_Comm_PORT PORTB //DR command port
#define LCD_Comm_PIN PINB

#define LCD_RS 0
#define LCD_RW 1
#define LCD_E 2

#define LCD_DDR DDRD


void lcd_init();
void lcd_send_data ( unsigned char data );
void lcd_command ( unsigned char cmnd );
void  lcd_gotoxy (unsigned char x, unsigned char y);
void lcd_print(char* str);


int main(void){
    LCD_Comm_DDR |= (1 << PB5);
    LCD_Comm_PORT |= (1 << PB5);
    lcd_init();
    lcd_gotoxy(1,1);
    lcd_print("hello world");
    lcd_gotoxy(1,2);
    lcd_print("Embedded");
    while (1){
        LCD_Comm_PORT ^= (1 << PB5);
        _delay_ms(10000);
    }
    
    return 0;
}

void lcd_init(){
    LCD_Data_DDR = 0xFF;
    LCD_Comm_DDR |= (1 << PB5);
    LCD_Comm_PORT |= (1<<LCD_E);
    _delay_us(2000);
    lcd_command(0x38); 
    lcd_command(0x0E); 
    lcd_command(0x01); 
    _delay_us(2000);
    lcd_command(0x06); 

}
void lcd_command(unsigned char cmnd){
    LCD_Data_PORT = cmnd;
    LCD_Comm_PORT &= ~(1<<LCD_RS); // turn RS 0
    LCD_Comm_PORT &= ~(1<<LCD_RW); // turn Rw 0
    LCD_Comm_PORT |= (1<<LCD_E); //EN =1 H to L prepping for L to H
    _delay_us(1);
    LCD_Comm_PORT &= ~(1<<LCD_E);//for H to L pulse
    _delay_us(100);
}

void lcd_send_data ( unsigned char data ){
    LCD_Data_PORT = data;
    LCD_Comm_PORT |= (1<<LCD_RS);
    LCD_Comm_PORT &= ~(1<<LCD_RW); //write
    LCD_Comm_PORT |= (1<<LCD_E); //EN = 1 H to L prepping for L to H
    _delay_us(1);
    LCD_Comm_PORT &= ~(1<<LCD_E);//for H to L pulse
    _delay_us(100);
}


void  lcd_gotoxy (unsigned char x, unsigned char y){
    //Table 12-5
    unsigned char firstCharAdri[] = {0x80, 0xC0, 0x94, 0xD4} ;
    lcd_command(firstCharAdri[y-1] + x - 1);
    _delay_us(100);
}

void lcd_print(char* str){
    unsigned char i = 0;
    while (str[i] != 0)
    {
        lcd_send_data(str[i]);
        i++;
    }
    
}

