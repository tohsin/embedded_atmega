#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>


#define i2cAdress 0x27

void write_i2c(unsigned char data);
void start_i2c();
void stop_i2c();
void initalise_i2c();

void initalise_i2c(){
    TWCR = 0x00; // turn off prescaler
    TWBR = 0x98; // scl frequency is 50k for XTAL = 16MHZ = 152 set frequecny for SCL
    TWCR = 0X04; //enable TWI : interrupt
}


void write_i2c(unsigned char data){
    //TWDR is read write register
    TWDR = data;
    //TWCR is control register
    //TWINT TWI Interrupt Flag
    //TWEN enable bit telling it to take control
    TWCR = (1 << TWINT) | (1 << TWEN);
    // while((TWCR & (1 << TWINT)) == 0 );
    while (!(TWCR & (1<<TWINT)))
}


void start_i2c(){
    //TWSTA create  a start condition if bus is free
    TWCR = (1 << TWINT) | (1 << TWSTA ) | ( 1 << TWEN );
    // while((TWCR & (1 << TWINT)) == 0 );
    //same as below less elegangt
    while (!(TWCR & (1<<TWINT)));
}


void stop_i2c(){
    // TWEN Stop bit
    TWCR = (1 << TWINT) | (1 << TWSTO ) | ( 1 << TWEN );
}
