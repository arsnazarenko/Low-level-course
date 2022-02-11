#include "io.h"

enum open_status file_open(FILE** file, const char* filepath, const char* modes) {
    if (!filepath || !modes) return OPEN_ERROR;
    *file = fopen(filepath, modes);
    if (!(*file)) {
        return OPEN_ERROR;
    }
    return OPEN_OK;

}
enum close_status file_close(FILE** file) {
    if (!fclose(*file)) {
        return CLOSE_OK;
    }
    return CLOSE_ERROR;
}

