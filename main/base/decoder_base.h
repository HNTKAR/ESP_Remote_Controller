#ifndef __DECODER_BASE_H__
#define __DECODER_BASE_H__
#include <vector>
#include <cstdint>
#ifdef USE_IOSTREAM_FOR_DEBUG
#include <iostream>
#include <iomanip>
#endif
class DecoderBase
{
public:
    enum format_type
    {
        FORMAT_TYPE_RAW,
        FORMAT_TYPE_NEC,
        FORMAT_TYPE_AEHA,
        FORMAT_TYPE_SONY,
        FORMAT_TYPE_UNKNOWN
    };
    struct DecodedResult
    {
        bool isValid;
        uint8_t data;
    };

    virtual ~DecoderBase() = default;
    virtual bool decode(const std::vector<uint64_t> &timingData) = 0;
    void DisplayDecodedData(bool reverse = false) const;
    void reset();

protected:
    format_type format;
    std::vector<std::vector<uint8_t>> decodedData;
    bool pushBin2Vector(std::vector<uint8_t> &binData);
};

#endif // __DECODER_BASE_H__