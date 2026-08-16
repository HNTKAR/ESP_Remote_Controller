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
