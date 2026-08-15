#include "recieveMain.h"

void recieveMain::init()
{
    std::cout << "Initializing recieveMain..." << std::endl;
}

void recieveMain::start()
{
    // Code to start the thread
    std::cout << "Thread started." << std::endl;
    recieveSignal *signal = new recieveSignal();
    std::vector<uint64_t> timingData;
    QueueHandle_t timingQueue = xQueueCreate(10, sizeof(uint64_t));
    signal->init(timingQueue);

    while (true)
    {
        uint64_t delta_time;
        BaseType_t result = xQueueReceive(timingQueue, &delta_time, 1000 / portTICK_PERIOD_MS);
        if (result == pdTRUE)
        {
            timingData.push_back(delta_time);
        }
        else
        {
            std::cout << "Failed to receive from queue." << std::endl;
            std::cout << "Timing Data: ";
            for (const auto &time : timingData)
            {
                std::cout << time << " ";
            }
            std::cout << std::endl;
            timingData.clear();
        }
    }
}

void recieveMain::stop()
{
    // Code to stop the thread
    std::cout << "Thread stopped." << std::endl;
}
