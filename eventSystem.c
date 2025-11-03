#include "eventSystem.h"
#include <avr/io.h>

void eventSystem_init(void){
     // Binds AC0 to channel 0 in the event system
     EVSYS.CHANNEL0 = EVSYS_CHANNEL0_AC0_OUT_gc;
     // Binds PA2 to the event channel 0 wich AC0 will generate an event on
     EVSYS.USEREVSYSEVOUTA = EVSYS_CHANNEL0_PORTA_PIN2_gc;
}

