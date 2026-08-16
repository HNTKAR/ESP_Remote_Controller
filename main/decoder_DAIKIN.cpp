#include "decoder_DAIKIN.h"

/// @brief DAIKIN信号のデコードを行う。timingDataのサイズ、リーダー部分、データ部分を順にチェックし、すべてが正しい場合にtrueを返す。
/// @param timingData DAIKIN信号のタイミングデータのベクター
/// @return デコードが成功した場合はtrue、それ以外の場合はfalse。
bool DecoderDAIKIN::decode(const std::vector<uint64_t> &timingData)
{
    uint64_t index = 1;
    bool passSize = checkSize(timingData);
    bool passLeader = checkLeader(timingData, index);
    bool pass1stData = checkData(timingData, index);
    bool pass2ndData = checkData(timingData, index);

    return passSize && passLeader && pass1stData && pass2ndData;
}

/// @brief DAIKIN信号のサイズをチェックする。timingDataのサイズが644であることを確認する。
/// @param timingData DAIKIN信号のタイミングデータのベクター
/// @return サイズが正しい場合はtrue、それ以外の場合はfalse。
bool DecoderDAIKIN::checkSize(const std::vector<uint64_t> &timingData)
{
    return timingData.size() == 644;
}

/// @brief DAIKIN信号のリーダー部分をチェックする。timingDataからindex位置のデータを読み取り、リーダー部分が正しいかどうかを判定する。
/// @param timingData DAIKIN信号のタイミングデータのベクター
/// @param index データを読み取る開始位置のインデックス。チェック後、次のデータの開始位置に更新される。
/// @return リーダー部分が正しい場合はtrue、それ以外の場合はfalse。
bool DecoderDAIKIN::checkLeader(const std::vector<uint64_t> &timingData, uint64_t &index)
{
    bool ret = false;
    while (index + 1 < timingData.size())
    {
        if (timingData[index + 1] > 10000)
        {
            ret = true;
            index += SeparatorCount;
            break;
        }
        index += 2;
    }
    return ret;
}

void DecoderDAIKIN::DisplayDecodedData(bool rev) const
{
    DecoderBase::DisplayDecodedData(rev);
    if (decodedData.size() >= 2)
    {
        std::cout << std::dec << std::endl;

        uint8_t power = decodedData[1][5] & 0x0f;
        std::cout << "Power: ";
        if (power == 8)
            std::cout << "OFF" << std::endl;
        else if (power == 9)
            std::cout << "ON" << std::endl;
        else
            std::cout << "Unknown" << std::endl;

        uint8_t mode = (decodedData[1][5] >> 4) & 0x0f;
        std::cout << "Mode: ";
        switch (mode)
        {
        case 0:
            std::cout << "Auto" << std::endl;
            break;
        case 2:
            std::cout << "Dry" << std::endl;
            break;
        case 3:
            std::cout << "Cool" << std::endl;
            break;
        case 4:
            std::cout << "Heat" << std::endl;
            break;
        case 6:
            std::cout << "Fan" << std::endl;
            break;
        default:
            std::cout << "Unknown" << std::endl;
            break;
        }

        uint8_t temperature = (decodedData[1][6] >> 1) & 0xff;
        std::cout << "Temperature: " << static_cast<int>(temperature) << std::endl;

        uint8_t fanSpeed = (decodedData[1][8] >> 4) & 0b00001111;
        std::cout << "Fan Speed: ";
        switch (fanSpeed)
        {
        case 10:
            std::cout << "Auto" << std::endl;
            break;
        case 11:
            std::cout << "Quiet" << std::endl;
            break;
        default:
            std::cout << static_cast<int>(fanSpeed) - 2 << std::endl;
            break;
        }

        uint8_t fanDirection = (decodedData[1][8] >> 4) & 0x0f;
        std::cout << "Fan Direction: ";
        switch (fanDirection)
        {
        case 0:
            std::cout << "Fixed" << std::endl;
            break;
        case 15:
            std::cout << "Auto" << std::endl;
            break;
        default:
            std::cout << "Unknown" << std::endl;
            break;
        }

        uint16_t onTimer = decodedData[1][11];
        onTimer = (onTimer << 8) & 0x0f00;
        onTimer |= decodedData[1][10] & 0xff;
        std::cout << "On Timer: " << onTimer << " minutes" << std::endl;

        uint16_t offTimer = decodedData[1][12];
        offTimer = (offTimer << 4) & 0xff0;
        offTimer |= (decodedData[1][11] >> 4) & 0x0f;
        std::cout << "Off Timer: " << offTimer << " minutes" << std::endl;

        uint8_t streamer = (decodedData[1][16] >> 4) & 0x0f;
        std::cout << "Streamer: ";
        if (streamer == 8)
            std::cout << "OFF" << std::endl;
        else if (streamer == 9)
            std::cout << "ON" << std::endl;
        else
            std::cout << "Unknown" << std::endl;
    }
}

/// @brief DAIKINデータのチェックを行う。timingDataからindex位置のデータを読み取り、バイナリデータに変換する。
/// @param timingData DAIKIN信号のタイミングデータのベクター
/// @param index データを読み取る開始位置のインデックス。チェック後、次のデータの開始位置に更新される。
/// @return データが正常にチェックされ、バイナリデータが取得できた場合はtrue、それ以外の場合はfalse。
bool DecoderDAIKIN::checkData(const std::vector<uint64_t> &timingData, uint64_t &index)
{
    bool ret = false;
    std::vector<uint8_t> binData;
    for (; index + 2 <= timingData.size(); index += 2)
    {
        DecoderBase::DecodedResult binResult = checkBin(timingData[index], timingData[index + 1]);
        if (!binResult.isValid)
        {
            index += SeparatorCount;
            break;
        }
        binData.push_back(binResult.data);
    }
    pushBin2Vector(binData);
    ret = !binData.empty();
    return ret;
}
