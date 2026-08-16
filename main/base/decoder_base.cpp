#include "decoder_base.h"

bool DecoderBase::pushBin2Vector(std::vector<uint8_t> &binData)
{
    std::vector<uint8_t> tempBinData;
    for (size_t i = 0; i + 8 <= binData.size(); i += 8)
    {
        uint8_t hexValue = 0;

        for (size_t j = 0; j < 8; ++j)
            hexValue |= (binData[i + j] & 0x01) << j;

        tempBinData.push_back(hexValue);
    }
    if (!tempBinData.empty())
        decodedData.push_back(tempBinData);
    return true;
}
void DecoderBase::reset()
{
    decodedData.clear();
}

void DecoderBase::DisplayDecodedData() const
{
#ifdef USE_IOSTREAM_FOR_DEBUG
    std::cout << "Decoded Data:" << std::endl;
    for (const auto &dataVector : decodedData)
    {
        for (const auto &data : dataVector)
        {
            std::cout << std::hex << static_cast<int>(data) << " ";
        }
        std::cout << std::endl;
    }
#endif
}
