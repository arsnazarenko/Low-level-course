#include "rotate.h"
#include <stdint.h>


struct maybe_image image_rotate_left(const struct image img) {
    struct maybe_image maybe = image_create(img.height, img.width);
    if (!maybe.valid) {
        return maybe;
    }
    struct image dest = maybe.img;
    for ( uint32_t i = 0; i < img.height; ++i) {
        for (uint32_t j = 0; j < img.width; ++j) {
            dest.data[j * dest.width + (dest.width - i -1)] = img.data[i * img.width + j];
        }
    }
    return (struct maybe_image) {.valid = true, .img = dest};
}


