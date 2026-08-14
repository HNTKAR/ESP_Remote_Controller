#include <iostream>
#include "driver/ledc.h"
#include "send.h"
#include "recieve.h"

void print_timing(void *arg) {
    QueueHandle_t queue = (QueueHandle_t)arg;
    bool is_high = false;
    while (1) {
        edge_timing_t timing;
        if (xQueueReceive(queue, &timing, portMAX_DELAY)) {
            if (timing.last_change_time > 50000) {
                std::cout << "Timing (LOW): " << timing.last_change_time << " (overflow)" << std::endl;
                is_high = true;
            } else {
                is_high = !is_high;
                std::cout << "Timing (" << (is_high ? "LOW" : "HIGH") << "): " << timing.last_change_time << std::endl;
            }
        }
    }
}

extern "C" void app_main(void){
    QueueHandle_t xQueue1 =NULL;
    xQueue1 = xQueueCreate(10, sizeof(edge_timing_t));
    xTaskCreate(print_timing, "print_timing", 4096, xQueue1, 5, NULL);
    // send_init();
    recieve_init(xQueue1);
    // recieve_set();
}
