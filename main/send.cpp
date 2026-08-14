#include "send.h"
void send_init() {
    ledc_timer_config_t ledc_timer = {};
    ledc_timer.speed_mode       = LEDC_LOW_SPEED_MODE;
    ledc_timer.duty_resolution  = LEDC_TIMER_7_BIT;
    ledc_timer.timer_num        = LEDC_TIMER_0;
    ledc_timer.freq_hz          = 38*1000;
    ledc_timer.clk_cfg          = LEDC_USE_RC_FAST_CLK;
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {};
    ledc_channel.gpio_num       = 13;
    ledc_channel.speed_mode     = LEDC_LOW_SPEED_MODE;
    ledc_channel.channel        = LEDC_CHANNEL_0;
    ledc_channel.timer_sel      = LEDC_TIMER_0;
    ledc_channel.duty           = 39; // 39/128 = 30.5% duty cycle
    ledc_channel.hpoint         = 0;
    ledc_channel_config(&ledc_channel);
}