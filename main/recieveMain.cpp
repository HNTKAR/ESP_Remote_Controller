#include "recieveMain.h"
#include "decoder_DAIKIN.h"

void recieveMain::init()
{
#ifdef USE_IOSTREAM_FOR_DEBUG
    std::cout << "Initializing recieveMain..." << std::endl;
#endif
}

void recieveMain::start()
{
    // Code to start the thread
#ifdef USE_IOSTREAM_FOR_DEBUG
    std::cout << "Thread started." << std::endl;
#endif
    recieveSignal *signal = new recieveSignal();
    std::vector<uint64_t> timingData;
    QueueHandle_t timingQueue = xQueueCreate(100, sizeof(uint64_t));
    signal->init(timingQueue);

    while (true)
    {
        uint64_t delta_time;
        BaseType_t result = xQueueReceive(timingQueue, &delta_time, 100 / portTICK_PERIOD_MS);
        if (result == pdTRUE)
        {
            timingData.push_back(delta_time);
        }
        else if (!timingData.empty())
        {
            if (timingData.size() > 10)
            {
#ifdef USE_IOSTREAM_FOR_DEBUG
                std::cout << std::dec << "Timing Data: ";
                for (int i = 0; i < timingData.size(); ++i)
                {
                    if (timingData[i] > 1500)
                        std::cout << i << ": " << timingData[i] << " " << std::endl;
                }
                for (const auto &time : timingData)
                {

                    std::cout << time << " ";
                }
                std::cout << std::endl;
                std::cout << "vector size: " << timingData.size();
                std::cout << std::endl;
#endif

                DecoderDAIKIN decoder;
                bool decodeResult = decoder.decode(timingData);
                if (decodeResult)
                {
#ifdef USE_IOSTREAM_FOR_DEBUG
                    std::cout << "Decoding successful!" << std::endl;
#endif
                    decoder.DisplayDecodedData();
                    decoder.reset(); // Reset the decoder for the next decoding session
                }
                else
                {
#ifdef USE_IOSTREAM_FOR_DEBUG
                    std::cout << "Decoding failed." << std::endl;
#endif
                }
            }
            timingData.clear();
        }
    }
}

void recieveMain::stop()
{
    // Code to stop the thread
#ifdef USE_IOSTREAM_FOR_DEBUG
    std::cout << "Thread stopped." << std::endl;
#endif
}
