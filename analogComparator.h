
#ifndef ANALOGCOMPARATOR0_H_
#define ANALOGCOMPARATOR0_H_

#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>

void AC0_init(void);
void AC0_interruptInit(void);
uint8_t AC0_status(void);

#endif  // ANALOGCOMPARATOR0_H_