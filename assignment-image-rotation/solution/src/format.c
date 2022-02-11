#include "format.h"

const struct format_io formats[] = {
        [FORMAT_BMP] = {.serialize = to_bmp, .deserialize = from_bmp}
        //  other formats
};
