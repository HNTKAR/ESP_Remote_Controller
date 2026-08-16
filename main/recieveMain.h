#ifndef __RECIEVE_MAIN_H__
#define __RECIEVE_MAIN_H__
#ifdef USE_IOSTREAM_FOR_DEBUG
#include <iostream>
#endif
#include <vector>
#include "freertos/FreeRTOS.h"
#include "base/mode_base.h"
#include "recieveSignal.h"

class recieveMain : public modeMain
{
public:
    void init() override;
    void start() override;
    void stop() override;

private:
    TaskHandle_t recieveTaskHandle;
    void displayTimingData(const std::vector<uint64_t> &timingData) const;
    void iostreamDebug(const char *message) const;
};

#endif // __RECIEVE_MAIN_H__
