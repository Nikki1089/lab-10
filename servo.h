#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>
#include <inc/tm4c123gh6pm.h>

void servo_init(void);
void servo_move(uint16_t degrees);

#endif
