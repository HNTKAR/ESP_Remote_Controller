#ifndef __FORMAT_H__
#define __FORMAT_H__
#include <stdint.h>

enum format_type
{
    FORMAT_TYPE_RAW,
    FORMAT_TYPE_NEC,
    FORMAT_TYPE_AEHA,
    FORMAT_TYPE_SONY,
    FORMAT_TYPE_UNKNOWN
};

typedef struct
{
    enum format_type type;
    uint32_t command;
} signal_t;

#endif // __FORMAT_H__