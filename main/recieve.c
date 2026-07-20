#include "recieve.h"

void recieve_init() {
    gpio_config_t reciever_conf = {
        .pin_bit_mask = (1ULL << GPIO_NUM_12),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_ANYEDGE 
    };
    ESP_ERROR_CHECK(gpio_reset_pin(GPIO_NUM_12));
    ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_12, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_set_intr_type(GPIO_NUM_12, GPIO_INTR_ANYEDGE));
    ESP_ERROR_CHECK(gpio_intr_enable(GPIO_NUM_12));
    // ESP_ERROR_CHECK(gpio_isr_register(recieve_isr, NULL, 0, NULL));
    ESP_ERROR_CHECK(gpio_install_isr_service(0));
    ESP_ERROR_CHECK(gpio_isr_handler_add(GPIO_NUM_12, recieve_isr, NULL));

    // ESP_ERROR_CHECK(gpio_config(&reciever_conf));
}

void recieve_set() {
    int level = 0;
    gpio_dump_io_configuration(stdout, (1ULL << GPIO_NUM_12));

    while (1) {
    level = gpio_get_level(GPIO_NUM_12);
    printf("Recieved: %d\n", level);
    vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void IRAM_ATTR recieve_isr(void* arg) {
    // Placeholder for ISR implementation
    printf("Interrupt received on GPIO 12\n");
}
