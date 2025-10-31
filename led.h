#ifndef LED_H_
#define LED_H_

#include <avr/io.h>
//#include <string.h>
//#include <stdint.h>
#include <stdbool.h>

void LED_init(void);
void set_LED_on(void);
void set_LED_off(void);

#endif    // LED_H_
