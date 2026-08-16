#include "decoder_DAIKIN.h"

bool DecoderDAIKIN::decode(const std::vector<uint64_t> &timingData)
{
    uint64_t index = 1;
    bool passSize = checkSize(timingData);
    bool passLeader = checkLeader(timingData, index);
    bool pass1stData = checkData(timingData, index);
    bool pass2ndData = checkData(timingData, index);

    return passSize && passLeader && pass1stData && pass2ndData;
}

bool DecoderDAIKIN::checkSize(const std::vector<uint64_t> &timingData)
{
    return timingData.size() == 644;
}

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
