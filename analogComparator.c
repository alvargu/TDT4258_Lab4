#include "analogComparator.h"
#include <avr/io.h>

void AC0_init(void){
     // Set pin PD2 (port D, pin 2) as an input
     PORTD.DIRCLR = PIN2_bm;
     // Disable digital input buffer and pull-up resistor for pin PD2
     PORTD.PIN2CTRL = PORT_ISC_INPUT_DISABLE_gc;

     // Set positive input to pin PD2 and negative input to internal DAC reference   
     AC0.MUXCTRL = AC_MUXPOS_2_bm | AC_MUXNEG_DACREF_gc;
    
     // Set voltage reference 1.024V
     VREF.ACREF = VREF_REFSEL_1V024_gc;

     // Set "trigger level" for ON/OFF function of analog comparator
     // V_DACREF = (DACREF/256)*V_REF
     // DACREF = 25 => (25 / 256)*1.024V = V_DACREF = 0.1 V
     AC0.DACREF = 25;

     // Enable Analog Comparator 0
     AC0.CTRLA = AC_ENABLE_bm | AC_RUNSTDBY_bm;  
}

// Same as AC0_init but with interrupt settings added
void AC0_interruptInit(void){
     // Set pin PD2 (port D, pin 2) as an input
     PORTD.DIRCLR = PIN2_bm;
     // Disable digital input buffer and pull-up resistor for pin PD2
     PORTD.PIN2CTRL = PORT_ISC_INPUT_DISABLE_gc;

     // Set positive input to pin PD2 and negative input to internal DAC reference   
     AC0.MUXCTRL = AC_MUXPOS_2_bm | AC_MUXNEG_DACREF_gc;
     // Set voltage reference 1.024V
     VREF.ACREF = VREF_REFSEL_1V024_gc;
     // Set "trigger level" for ON/OFF function of analog comparator
     // V_DACREF = (DACREF/256)*V_REF & DACREF = 25 => (25 / 256)*1.024V = V_DACREF = 0.1 V
     AC0.DACREF = 25;

     // Enable Analog Comparator interupt And setting the interrupt mode to trigger on both edges.
     AC0.INTCTRL = AC_CMP_bm | AC_INTMODE_NORMAL_BOTHEDGE_gc;

     // Enable Analog Comparator 0 and set it to run in standbymode
     AC0.CTRLA = AC_ENABLE_bm | AC_RUNSTDBY_bm;  

     
}

uint8_t AC0_status(void){
     // Macro for on/off detection
     return ((AC0.STATUS & AC_CMPSTATE_bm) >> AC_CMPSTATE_bp);
}

/*
 * End of file analogComparator.c
*/
