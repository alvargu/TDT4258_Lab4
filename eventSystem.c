#include "eventSystem.h"
#include <avr/io.h>

void eventSystem_init(void){
     // Binds AC0 as a generator to channel 0 in the event system
     EVSYS.CHANNEL0 = EVSYS_CHANNEL0_AC0_OUT_gc;
     // Binds PA2 as a user to the event channel 0 which AC0 will generate an event on
     EVSYS.USEREVSYSEVOUTA = EVSYS_USER_CHANNEL0_gc;
}

/*
 * End of file eventSystem.c
*/
