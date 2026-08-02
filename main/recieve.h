#ifndef __RECIEVE_H__
#define __RECIEVE_H__
#include <time.h>
#include <sys/time.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "driver/gptimer.h"
#include "esp_err.h"

static gptimer_handle_t timer;

typedef struct
{
    bool is_high;
    uint64_t last_change_time;
} edge_timing_t;
// static edge_timing_t last_timing = {0, 0};

void recieve_init(QueueHandle_t queue);
void recieve_isr(void *arg);

#endif // __RECIEVE_H__
