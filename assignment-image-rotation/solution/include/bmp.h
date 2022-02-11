#ifndef LAB_BMP_H
#define LAB_BMP_H
#include "io.h"
#include "image.h"

enum read_status from_bmp(FILE* in, struct image* image);

enum write_status to_bmp(FILE* out, const struct image* image);

#endif
