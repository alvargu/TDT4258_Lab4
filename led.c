#include "led.h"

void LED_init(void) {
     PORTA.DIRSET = PIN2_bm;
}
void set_LED_on(void){
     // LED is active low. Set pin LOW to turn LED on
     PORTA.OUTCLR = PIN2_bm;
}
void set_LED_off(void){
     // LED is active low. Set pin HIGH to turn LED off
     PORTA.OUTSET = PIN2_bm;
}

void toggle_LED(void){
     // LED is active low. Set pin HIGH to turn LED off
     PORTA.OUT ^= PIN2_bm;
}

/*
 * End of file led.c
*/
