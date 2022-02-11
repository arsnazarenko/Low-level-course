#ifndef LAB_IMAGE_H
#define LAB_IMAGE_H
#include "stdint.h"
#include "stdbool.h"

struct pixel {
    uint8_t b, g, r;
};

struct image {
    uint32_t width, height;
    struct pixel* data;
};

struct maybe_image {
    bool valid;
    struct image img;
};

#define PIXEL_SIZE sizeof(struct pixel)

struct maybe_image image_create(const uint32_t width,
                          const uint32_t height);

void image_destroy(const struct image* image);

#endif
