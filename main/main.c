#include <stdio.h>
#include "driver/ledc.h"
#include "send.h"
#include "recieve.h"

void print_timing(void *arg) {
    QueueHandle_t queue = (QueueHandle_t)arg;
    bool odd = false;
    while (1) {
        edge_timing_t timing;
        if (xQueueReceive(queue, &timing, portMAX_DELAY)) {
            if (timing.last_change_time > 50000) {
                printf("Timing(%s): %llu (overflow)\n", timing.is_high ? "high" : "low", timing.last_change_time);
                odd = false;
            } else {
                odd = !odd;
                printf("Timing(%s): %llu%s\n", timing.is_high ? "high" : "low", timing.last_change_time, odd ? " (odd)" : "");
            }
        }
    }
}

void app_main(void){
    QueueHandle_t xQueue1 =NULL;
    xQueue1 = xQueueCreate(10, sizeof(edge_timing_t));
    xTaskCreate(print_timing, "print_timing", 4096, xQueue1, 5, NULL);
    // send_init();
    recieve_init(xQueue1);
    // recieve_set();
}
