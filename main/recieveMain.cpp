#include "recieveMain.h"
#include "decoder_DAIKIN.h"

/// @brief recieveMainクラスのinitメソッド。初期化処理を行う。
void recieveMain::init()
{
    iostreamDebug("Initializing recieveMain...");
}

/// @brief recieveMainクラスのstartメソッド。スレッドを開始する際に呼び出される。
void recieveMain::start()
{
    // Code to start the thread
    iostreamDebug("Thread started.");
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
                displayTimingData(timingData);

                DecoderDAIKIN decoder;
                bool decodeResult = decoder.decode(timingData);
                if (decodeResult)
                {
                    decoder.DisplayDecodedData();
                    decoder.reset(); // Reset the decoder for the next decoding session
                }
                else
                {
                    iostreamDebug("Decoding failed.");
                }
            }
            timingData.clear();
        }
    }
}

/// @brief USE_IOSTREAM_FOR_DEBUGが定義されている場合に、デバッグメッセージを標準出力に表示する。
/// @param message デバッグメッセージの文字列
void recieveMain::iostreamDebug(const char *message) const
{
#ifdef USE_IOSTREAM_FOR_DEBUG
    std::cout << message << std::endl;
#endif
}

/// @brief タイミングデータを表示する。USE_IOSTREAM_FOR_DEBUGが定義されている場合に、タイミングデータの内容を標準出力に表示する。
/// @param timingData タイミングデータのベクター
/// @return なし
void recieveMain::displayTimingData(const std::vector<uint64_t> &timingData) const
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
}

/// @brief recieveMainクラスのstopメソッド。スレッドを停止する際に呼び出される。
void recieveMain::stop()
{
    iostreamDebug("Thread stopped.");
}
