#ifndef __DECODER_DAIKIN_H__
#define __DECODER_DAIKIN_H__
#include "decoder_AEHA.h"

class DecoderDAIKIN : public DecoderAEHA
{
public:
    bool decode(const std::vector<uint64_t> &timingData) override;
    void DisplayDecodedData(bool reverse = false) const override;

private:
    bool checkSize(const std::vector<uint64_t> &timingData);
    bool checkLeader(const std::vector<uint64_t> &timingData, uint64_t &start_index);
    bool checkData(const std::vector<uint64_t> &timingData, uint64_t &start_index);
    const uint8_t SeparatorCount = 4;
};
#endif // __DECODER_DAIKIN_H__