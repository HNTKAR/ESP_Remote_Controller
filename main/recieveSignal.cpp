#include "recieveSignal.h"

void recieveSignal::init(QueueHandle_t timingQueue)
{
    previous_time = 0;
    initGpio();
    initGptTimer();
    timing = timingQueue; // Assign the passed queue to the member variable
}

void recieveSignal::initGpio()
{
    ESP_ERROR_CHECK(gpio_reset_pin(GPIO_NUM_12));
    ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_12, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_set_intr_type(GPIO_NUM_12, GPIO_INTR_ANYEDGE));
    ESP_ERROR_CHECK(gpio_intr_enable(GPIO_NUM_12));
    ESP_ERROR_CHECK(gpio_install_isr_service(tskIDLE_PRIORITY));
    ESP_ERROR_CHECK(gpio_isr_handler_add(GPIO_NUM_12, [](void *arg)
                                         { ((recieveSignal *)arg)->isr(); }, this));
}

void recieveSignal::initGptTimer()
{
    gptimer_config_t timer_config = {};
    timer_config.clk_src = GPTIMER_CLK_SRC_DEFAULT;
    timer_config.direction = GPTIMER_COUNT_UP;
    timer_config.resolution_hz = 1000000; // 1 MHz resolution
    ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &timer));
    ESP_ERROR_CHECK(gptimer_enable(timer));
    ESP_ERROR_CHECK(gptimer_start(timer));
}

void recieveSignal::isr()
{
    uint64_t current_time;
    ESP_ERROR_CHECK(gptimer_get_raw_count(timer, &current_time));
    uint64_t delta_time = current_time - previous_time;
    previous_time = current_time;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xQueueSendToBackFromISR(timing, &delta_time, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken)
    {
        taskYIELD();
    }
}

void recieveSignal::reset()
{
    ESP_ERROR_CHECK(gptimer_stop(timer));
    ESP_ERROR_CHECK(gptimer_set_raw_count(timer, 0));
    ESP_ERROR_CHECK(gptimer_start(timer));
    previous_time = 0;
}
