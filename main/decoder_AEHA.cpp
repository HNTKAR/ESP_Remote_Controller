#include "decoder_AEHA.h"

bool DecoderAEHA::decode(const std::vector<uint64_t> &timingData)
{
    bool ret = false;

    for (auto timing = timingData.begin(); timing != timingData.end(); ++timing)
    {
        // Implement the decoding logic here
    }

    return ret;
}

DecoderBase::DecodedResult DecoderAEHA::checkBin(uint64_t on_time, uint64_t off_time)
{
    DecodedResult ret;
    ret.isValid = false;
    ret.data = 0;

    uint64_t off_time_times_10 = off_time * 10;
    uint8_t div = 0;

    while (off_time_times_10 > on_time)
    {
        off_time_times_10 -= on_time;
        div += 1;
        if (div > 35)
            break;
    }

    if (div > 5 && div < 15)
    {
        ret.isValid = true;
        ret.data = 0;
    }
    else if (div > 25 && div < 35)
    {
        ret.isValid = true;
        ret.data = 1;
    }

    if (on_time < on_time_min || on_time > on_time_max)
        ret.isValid = false;

    return ret;
}
