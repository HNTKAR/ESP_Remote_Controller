#ifndef __RECIEVE_MAIN_H__
#define __RECIEVE_MAIN_H__
#include <iostream>
#include <vector>
#include "freertos/FreeRTOS.h"
#include "abstruct/mode.h"
#include "recieveSignal.h"

class recieveMain : public modeMain
{
public:
    void init() override;
    void start() override;
    void stop() override;

private:
    TaskHandle_t recieveTaskHandle;
    std::vector<uint64_t> timingData;
};

#endif // __RECIEVE_MAIN_H__
