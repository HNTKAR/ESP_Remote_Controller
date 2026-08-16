#include "decoder_base.h"

/// @brief バイナリデータを8ビットごとにまとめて16進数に変換し、decodedDataベクターに格納する。
/// @param binData バイナリデータのベクター
/// @return データが正常にプッシュされた場合はtrue、それ以外の場合はfalse。
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

/// @brief デコードされたデータをリセットする。decodedDataベクターをクリアする。
void DecoderBase::reset()
{
    decodedData.clear();
}

/// @brief デコードされたデータを表示する。
/// @param rev データを逆順に表示するかどうかを指定するフラグ。デフォルトはfalse。
void DecoderBase::DisplayDecodedData(bool rev) const
{
#ifdef USE_IOSTREAM_FOR_DEBUG

    std::cout << "Decoding successful!" << std::endl;
    std::cout << "Decoded Data:" << std::endl;
    int index = 0;
    for (const auto &dataVector : decodedData)
    {
        index++;
        std::cout << "segment " << index << ": ";
        for (const auto &data : dataVector)
        {
            auto tmpData = data;
            if (rev)
            {
                tmpData = 0;
                for (int i = 0; i < 8; ++i)
                    tmpData |= ((data >> i) & 0x01) << (7 - i);
            }
            std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(tmpData) << " ";
        }
        std::cout << std::endl;
    }
#endif
}
