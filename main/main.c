#include <stdio.h>

#include "driver/ledc.h"

void app_main(void)
{
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = LEDC_TIMER_7_BIT,
        .timer_num        = LEDC_TIMER_0,
        .freq_hz          = 38*1000,
        .clk_cfg          = LEDC_USE_RC_FAST_CLK
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .gpio_num       = 13,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .duty           = 39, // 39/128 = 30.5% duty cycle
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channel);
}