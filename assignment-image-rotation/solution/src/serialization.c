#include "serialization.h"
#include "error_msg.h"
#include "util.h"

bool image_deserialize(const char* in, struct image* img, format_deserializer format_deserialize) {
    FILE* src = NULL;
    const enum open_status open_st = file_open(&src, in, "rb");
    if (open_st != OPEN_OK) {
        app_err(open_messages[open_st]);
        return false;
    }
    const enum read_status read_st = format_deserialize(src, img);
    if (read_st != READ_OK) {
        app_err(read_messages[read_st]);
        file_close(&src);
        return false;
    }
    const enum close_status close_st = file_close(&src);
    if (close_st != CLOSE_OK) {
        app_err(close_messages[close_st]);
        return false;
    }
    return true;
}


bool image_serialize(const char* out, const struct image* img, format_serializer format_serialize) {
    FILE* dest = NULL;
    const enum open_status open_st = file_open(&dest, out, "wb");
    if (open_st != OPEN_OK) {
        app_err(open_messages[open_st]);
        return false;
    }
    const enum write_status write_st = format_serialize(dest, img);
    if (write_st != WRITE_OK) {
        app_err(write_messages[write_st]);
        file_close(&dest);
        return false;
    }
    const enum close_status close_st = file_close(&dest);
    if (close_st != CLOSE_OK) {
        app_err(close_messages[close_st]);
        return false;
    }
    return true;
}
