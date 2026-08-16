#ifndef __DECODER_AEHA_H__
#define __DECODER_AEHA_H__
#include "base/decoder_base.h"

class DecoderAEHA : public DecoderBase
{
public:
    bool decode(const std::vector<uint64_t> &timingData) override;

protected:
    DecodedResult checkBin(uint64_t on_time, uint64_t off_time);
    uint16_t on_time_max = 500; // 500us
    uint16_t on_time_min = 350; // 350us
};
#endif // __DECODER_AEHA_H__