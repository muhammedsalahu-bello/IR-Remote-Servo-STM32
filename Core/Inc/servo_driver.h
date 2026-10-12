#ifndef servo_driver_h
#define servo_driver_h
#include "main.h"
#include "stm32f4xx_hal.h"

void start_servo_pwm(void);
void set_servo_angle(uint8_t angle);

#endif
