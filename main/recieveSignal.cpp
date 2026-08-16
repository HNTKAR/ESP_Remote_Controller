#include "recieveSignal.h"

/// @brief recieveSignalクラスのinitメソッド。GPIOピンの設定とタイマーの初期化を行う。
/// @param timingQueue タイミングデータを保持するキューのハンドル
void recieveSignal::init(QueueHandle_t timingQueue)
{
    previous_time = 0;
    initGpio();
    initGptTimer();
    timing = timingQueue; // Assign the passed queue to the member variable
}

/// @brief recieveSignalクラスのGPIO初期化メソッド。GPIOピンの設定と割り込みの設定を行う。
/// @return なし
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

/// @brief recieveSignalクラスのGPTimer初期化メソッド。GPTimerの設定と開始を行う。
/// @return なし
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

/// @brief recieveSignalクラスの割り込みサービスルーチン。GPIOピンの変化を検出し、タイミングデータをキューに送信する。
/// @return なし
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

/// @brief recieveSignalクラスのresetメソッド。タイマーを停止し、カウントをリセットして再起動する。
/// @return なし
void recieveSignal::reset()
{
    ESP_ERROR_CHECK(gptimer_stop(timer));
    ESP_ERROR_CHECK(gptimer_set_raw_count(timer, 0));
    ESP_ERROR_CHECK(gptimer_start(timer));
    previous_time = 0;
}
