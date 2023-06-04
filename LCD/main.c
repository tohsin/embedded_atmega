/*
using 20 x 4 LCD 
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


#define LCD_RS PIND0
#define LCD_RW PIND1
#define LCD_E PIND2
#define LCD_PORT PORTD 
#define LCD_DDR DDRD
// I used port D for everything

void lcd_init();
void lcdData ( unsigned char data );
void lcd_command ( unsigned char cmnd );
void  lcd_gotoxy (unsigned char x, unsigned char y);
void lcd_print(char* str);


int main(void){

    lcd_init();
    while (1)
    {
        lcd_gotoxy(1,1);
        lcd_print("hello world");

    }
    
    return 0;
}

void lcd_init(){
    DDRD  = 0x7F;
    LCD_PORT |= (1<<LCD_E); // E = 0
    _delay_us(2000); // wait for stability
    lcd_command(0x33); //switch to 4 bit mode
    _delay_us(100);
    lcd_command(0x32);
    lcd_command(0x28);

    lcd_command(0x0e); // display on cursor on
    _delay_us(100);

    lcd_command(0x01); // clear lcd
    _delay_us(2000);

    lcd_command(0x06); // shift cursor right
     _delay_us(100);

}
void lcd_command(unsigned char cmnd){
    // data pins are D3 to D6 for LCD
    LCD_PORT = (LCD_PORT & 0x87) | (cmnd & 0x78); //send high nibble to data pins in this case port6 to 3
    LCD_PORT &= ~(1<<LCD_RS); //rs = 0 when sendind commands
    LCD_PORT   &= ~(1<<LCD_RW); // rw = 0 when writing
    LCD_PORT |= (1<<LCD_E); // High to low pulse for this useage
    _delay_us(1); // read datasheet require for E
    LCD_PORT &= ~(1<<LCD_E); //low to High on E
    _delay_us(20);
    //send low nibble
    LCD_PORT = (LCD_PORT & 0x87) | (cmnd << 3);  //send low nibble to D4 - D7
    LCD_PORT |= (1<<LCD_E); // High to low pulse for this useage
    _delay_us(1); // read datasheet require for E
    LCD_PORT &= ~(1<<LCD_E); //low to High on E
    _delay_us(20);
}

void lcdData ( unsigned char data ){
    LCD_PORT = (LCD_PORT & 0x87) | (data & 0x78); //send high nibble to data pins in this case port6 to 3]
    LCD_PORT |= (1<<LCD_RS); //rs = 0 when sendind information
    LCD_PORT   &= ~(1<<LCD_RW); // rw = 0 when writing

    LCD_PORT |= (1<<LCD_E); // High to low pulse for this useage   
    _delay_us(1);
    LCD_PORT &= ~(1<<LCD_E); 

    LCD_PORT = (LCD_PORT & 0x87) | (data << 3);    
    LCD_PORT |= (1<<LCD_E); // High to low pulse for this useage
    _delay_us(1); // read datasheet require for E  
    LCD_PORT &= ~(1<<LCD_E);
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
        lcdData(str[i]);
        i++;
    }
    
}

