#include "TIM_HAL.h"
#include "TIM_REG.h"
#include "TIM_RTOS.h"

int app_main() 
{
    // Enable timer initializing style on demand
    Init_TIM_HAL();
    //Init_TIM_REG();
    //Init_TIM_RTOS();
    while(1)
    {

    }
}