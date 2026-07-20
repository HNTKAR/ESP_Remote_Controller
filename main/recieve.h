#ifndef __RECEIVE_H__
#define __RECEIVE_H__
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "esp_err.h"

void recieve_init();
void recieve_set();
void recieve_isr(void* arg);

#endif // __RECEIVE_H__
