#ifndef LAB_TRANSFORM_H
#define LAB_TRANSFORM_H
#include "rotate.h"
#include "image.h"

typedef struct maybe_image (*transform)(const struct image);

enum transformation {
    TR_ROTATE_LEFT = 0
    // other transformations
};

extern transform const transformations[];

#endif
