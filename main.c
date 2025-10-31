/**
 * @file main.c
 * @author agudd
 * @date 2025-10-28
 * @brief Main function
 */
// #define F_CPU 4000000UL

//#include <stdio.h>
#include <avr/io.h>
//#include <string.h>
//#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>


#include "timerCounter.h"
#include "usart.h"
#include "analogComparator.h"
#include "led.h"


void pinCtl_init(void);
void sleepModeStby(void);
void Task1_testUsart(void);
void Task3a_busyWaiting(void);
void Task3b_utilizePolling(void);
//Task4_InterruptDrivenApproach
//Task5_coreIndependentOperation


int main(void){
    // USART3_Init(); // Uncomment for uart debugging

    // pinCtl is active for all tasks
    pinCtl_init();
    // Uncomment the task that is desireable to use
    //Task1_testUsart();
    //Task3a_busyWaiting();
    Task3b_utilizePolling();
    //Task4_
    //Task5_coreIndependentOperation

    return 0;
}

void pinCtl_init(void){
    // Used pins are PA2 (for LED) and PD2 (for analog comparator)
    // The rest we sett to pullup to reduce possible currentdraw
    PORTA.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc | PORT_PULLUPEN_bm;
    PORTA.PINCTRLUPD = (0xFF ^ PIN2_bm);    // Excludes pin PA2 from the disable and pullup copy
    PORTB.PINCTRLUPD = 0xFF;
    PORTC.PINCTRLUPD = 0xFF;
    PORTD.PINCTRLUPD = (0xFF ^ PIN2_bm);    // Excludes pin PD2 from the disable and pullup copy
    PORTE.PINCTRLUPD = 0xFF;
    PORTF.PINCTRLUPD = 0xFF;
}

void sleepModeStby(void){
    // Sets the sleep mode to standby and enables sleep
    SLPCTRL.CTRLA = SLEEP_MODE_STANDBY | SLEEP_ENABLE_gc;
}

void Task1_testUsart(void){
    // Init functions neccesary for task
    USART3_Init();
    USART3_SendString("Hello, USART!");
}

void Task3a_busyWaiting(void){
    // Init functions neccesary for task
    AC0_init();
    LED_init();

    // Run continuosly
    while (1) {
        // Constantly check if Analog comparator is triggered or not.
        // Turn LED on or off based on result
        if (AC0_status()) set_LED_off();
        else if (!AC0_status()) set_LED_on();
    }
}

// bool checkLight = false;
void Task3b_utilizePolling(void){
    // Init functions neccesary for task
    AC0_init();
    LED_init();
    TCA0_init();

    // Run continuosly
    while (1) {
        // Constantly check if Analog comparator is triggered or not.
        // Turn LED on or off based on result
        if (AC0_status()) set_LED_off();
        else if (!AC0_status()) set_LED_on();
        sleepModeStby();
    }
}
