#ifndef LAB_FORMAT_H
#define LAB_FORMAT_H
#include "serialization.h"
#include "bmp.h"

enum format {
    FORMAT_BMP = 0
    //  other formats...
};

struct format_io {
    format_serializer serialize;
    format_deserializer deserialize;
};

extern struct format_io const formats[];

#endif
