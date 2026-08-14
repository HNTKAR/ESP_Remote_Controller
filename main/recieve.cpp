#include "recieve.h"

void recieve_init(QueueHandle_t queue) {
    ESP_ERROR_CHECK(gpio_reset_pin(GPIO_NUM_12));
    ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_12, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_set_intr_type(GPIO_NUM_12, GPIO_INTR_ANYEDGE));
    ESP_ERROR_CHECK(gpio_intr_enable(GPIO_NUM_12));
    ESP_ERROR_CHECK(gpio_install_isr_service(0));
    ESP_ERROR_CHECK(gpio_isr_handler_add(GPIO_NUM_12, recieve_isr, queue));
    gpio_dump_io_configuration(stdout, (1ULL << GPIO_NUM_12));
    gptimer_config_t timer_config = {};
    timer_config.clk_src = GPTIMER_CLK_SRC_DEFAULT;
    timer_config.direction = GPTIMER_COUNT_UP;
    timer_config.resolution_hz = 1000000; // 1 MHz resolution
    ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &timer));
    ESP_ERROR_CHECK(gptimer_enable(timer));
    ESP_ERROR_CHECK(gptimer_start(timer));
}

void IRAM_ATTR recieve_isr(void* arg) {
    QueueHandle_t queue = (QueueHandle_t)arg;
    uint64_t raw_count;
    static uint64_t last_count = 0;
    uint64_t delta_count;
    ESP_ERROR_CHECK(gptimer_get_raw_count(timer, &raw_count));
    bool is_high = gpio_get_level(GPIO_NUM_12);
    delta_count = raw_count - last_count;
    last_count = raw_count;

    edge_timing_t timing = {
        .is_high = is_high,
        .last_change_time = delta_count
    };
    xQueueSendFromISR(queue, &timing, NULL);
}
