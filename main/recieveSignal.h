#ifndef __RECIEVE_SIGNAL_H__
#define __RECIEVE_SIGNAL_H__
#include "driver/gptimer.h"
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include <vector>

class recieveSignal
{
public:
    // GPIOピンの設定とタイマーの初期化を行う関数
    void init(QueueHandle_t queue);
    void IRAM_ATTR isr();
    void reset();

private:
    uint64_t previous_time;           // 前回のタイムスタンプを保持する静的メンバ変数
    gptimer_handle_t timer;           // タイマーのハンドル
    void initGptTimer();              // タイマーの初期化を行う関数
    void initGpio();                  // GPIOの初期化を行う関数
    QueueHandle_t timing;          // タイミングデータを保持するキュー
};

#endif // __RECIEVE_SIGNAL_H__
