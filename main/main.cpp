#ifdef USE_IOSTREAM_FOR_DEBUG
#include <iostream>
#endif
#include "driver/ledc.h"
#include "send.h"
#include "recieveSignal.h"
#include "recieveMain.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void app_main(void)
{
#ifdef DEBUG_MODE
        std::cout << "Debug mode is enabled." << std::endl;
#endif
        recieveMain *recieveMainInstance = new recieveMain();
        recieveMainInstance->init();
        xTaskCreate([](void *arg)
                    {
        recieveMain* ptr = static_cast<recieveMain*>(arg);
        ptr->start(); }, "recieve_task", 2048, recieveMainInstance, tskIDLE_PRIORITY, NULL);
}
