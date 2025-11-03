/**
 * @file main.c
 * @author agudd
 * @date 2025-10-28
 * @brief Main function
 */
#include <avr/interrupt.h>
#include <avr/sleep.h>
#define F_CPU 4000000UL

//#include <stdio.h>
#include <avr/io.h>
//#include <string.h>
//#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>
#include <avr/sleep.h>


#include "timerCounter.h"
#include "usart.h"
#include "analogComparator.h"
#include "led.h"


void pinCtl_init(void);
void Task1_testUsart(void);
void Task3a_busyWaiting(void);
void Task3b_utilizePolling(void);
void Task4_InterruptDrivenApproach(void);
void Task5_coreIndependentOperation(void);


int main(void){
    // USART3_Init(); // Uncomment for uart debugging

    // pinCtl and LED is active/used for all tasks
    pinCtl_init();
    LED_init();
    // Uncomment the task that is desireable to use
    //Task1_testUsart();
    //Task3a_busyWaiting();
    //Task3b_utilizePolling();
    Task4_InterruptDrivenApproach();
    //Task5_coreIndependentOperation();

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

void Task1_testUsart(void){
    // Init functions neccesary for task
    USART3_Init();
    USART3_SendString("Hello, USART!");
}

void Task3a_busyWaiting(void){
    // Init functions neccesary for task
    AC0_init();

    // Run continuosly
    while (1) {
        // Constantly check if Analog comparator is triggered or not.
        // Turn LED on or off based on result
        if (AC0_status()) set_LED_off();
        else set_LED_on();
    }
}


/*
 * Task 3b: Utilize polling with sleep mode standby
*/
// Approach that utilizes polling with sleep mode standby is clearly more energy efficient.
// On the other hand, it is slightly more complex to implement and has a bit higher latency 
// due to sleep mode wakeup time and only checking on a set interval.
void Task3b_utilizePolling(void){
    // Init functions neccesary for task
    // AC0_init();
    LED_init();
    TCA0_init();
    // Set sleep mode to standby
    set_sleep_mode(SLEEP_MODE_STANDBY);

    // Run continuosly
    while (1) {
        // Enter sleep mode and wait for interrupt
        sleep_mode();
    }
}
/* Uncomment this if you want to run task 3b
ISR(TCA0_OVF_vect) {
    // Constantly check if Analog comparator is triggered or not.
    // Turn LED on or off based on result
    if (AC0_status()) set_LED_off();
    else set_LED_on();
    
    // Clear interrupt flag
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}
*/
/*
 * End of Task 3b
*/


/*
 * Task 4: Interrupt driven approach with sleep mode standby
*/
void Task4_InterruptDrivenApproach(void){
    // Init functions neccesary for task
    LED_init();
    AC0_interruptInit();
    
    // Disable interrupts
    cli();
    // Select a start state for the LED (on/off) based on current light state
    if (AC0_status()) set_LED_off();
    else set_LED_on();
    // Enable interrupts
    sei();

    // Set sleep mode to standby
    set_sleep_mode(SLEEP_MODE_STANDBY);
    // Run continuosly
    while (1) {
        // Enter sleep mode and wait for interrupt
        sleep_mode();
    }
}

ISR(AC0_AC_vect){
    // Toggle LED (on -> off & off -> on)
    toggle_LED();
    // Clear Interruptflag when LED is toggled
    AC0.STATUS = AC_CMPIF_bm;
}

/*
 * End of Task 4
*/


/*
 * Task 5: 
*/
void Task5_coreIndependentOperation(void){
    // Init functions neccesary for task
    AC0_interruptInit();
    LED_init();
    //AC0_enableInterrupt();

    // Run continuosly
    while (1) {
        // Enter sleep mode and wait for interrupt
        sleep_mode();
    }
}


/*
 * End of Task 5
*/


/*
 * End of file main.c
*/
