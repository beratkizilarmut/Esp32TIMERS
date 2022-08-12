#include "TIM_HAL.h"

#define LED_GPIO 25 // Using GPIO25
#define group_num 0 // Using TIMG0
#define timer_num 0 // Using TIM0
#define TIMER_RESOLUTION_HZ   1000000 // 1MHz resolution
#define TIMER_ALARM_PERIOD_S  0.1    // Alarm period 0.1s
#define alarm_value TIMER_ALARM_PERIOD_S * TIMER_RESOLUTION_HZ // Setting alarm_value

bool IRAM_ATTR timer_group_isr_callback(void *args) // Alarm interrupt handler
{
    gpio_set_level(LED_GPIO, !gpio_get_level(LED_GPIO)); // Toggle LED
    return true;
}

void Init_TIM_HAL()
{
    int *user_data = calloc(1, sizeof(int)); // Allocate space on heap
    timer_config_t config = { // Config struct
        .divider = APB_CLK_FREQ / TIMER_RESOLUTION_HZ, // Divider ratio from clk and res
        .counter_dir = TIMER_COUNT_UP, // Counting up
        .counter_en = TIMER_START, // Starting timer
        .alarm_en = TIMER_ALARM_EN, // Enabling alarm
        .auto_reload = TIMER_AUTORELOAD_EN, // Enabling autoreload
    };
    timer_init(group_num, timer_num, &config); // Initializing timer
    timer_set_alarm_value(group_num, timer_num, alarm_value); // Setting alarm value
    timer_enable_intr(group_num, timer_num); // Enabling interrupt
    timer_isr_callback_add(group_num, timer_num, timer_group_isr_callback, user_data, 0); // Initiating interrupt handler at allocated space
    gpio_set_direction(LED_GPIO, GPIO_MODE_INPUT_OUTPUT); // Setting GPIO25 as both input and output
}