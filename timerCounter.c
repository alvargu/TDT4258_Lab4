#include "timerCounter.h"

void TCA0_init(void) {
    // Disable global interrupts during setup
    cli();
    
    // Set the period of the timer.
    // PER = period[s] * F_CPU / Prescaler = 0.01s * 4 000 000 Hz / 2
    TCA0.SINGLE.PER = 20000;
    // Enable timer overflow interrupt
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
    // Run timer in standby mode, set prescaler to 2, enable timer
    // This needs to be set for polling as well as interrupt driven approach
    TCA0.SINGLE.CTRLA = TCA_SINGLE_RUNSTDBY_bm | TCA_SINGLE_CLKSEL_DIV2_gc | TCA_SINGLE_ENABLE_bm;
    
    // Enable global interrupts after setup
    sei();
}
