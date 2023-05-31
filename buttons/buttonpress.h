#ifndef ButtonPress
#define ButtonPress
#include <avr/io.h>


char ButtonPressed( int button_id, unsigned char pin_button, unsigned char portbit, 
    int confidence_level);


char pressed[number_buttons] = {0};
int pressed_confidence_level[number_buttons] = {0};
int released_confidence_level[number_buttons] = {0};


char 
ButtonPressed
(
    int button_id,
    unsigned char button_port, 
    unsigned char portbit, 
    int confidence_level
){
    if (!(button_port & (1 << portbit))){
        pressed_confidence_level[button_id]++;
        released_confidence_level[button_id] = 0;
        if (pressed_confidence_level[button_id] > confidence_level){
            if (pressed[button_id]  == 0){
                pressed[button_id]  = 1;
                return 1;
            }
            
        }
        pressed_confidence_level[button_id] = 0;

    }else{
        released_confidence_level[button_id]++;
        pressed_confidence_level[button_id] = 0;
        if(released_confidence_level[button_id] >= confidence_level){
            pressed[button_id] = 0;
            released_confidence_level[button_id] = 0;
        }
    }
    return 0;
}


#endif