#ifndef TIM_HAL_H
#define TIM_HAL_H

#include <stdio.h>
#include "driver/gpio.h"
#include "driver/timer.h"

void Init_TIM_HAL(void);
bool timer_group_isr_callback(void *args);

#endif