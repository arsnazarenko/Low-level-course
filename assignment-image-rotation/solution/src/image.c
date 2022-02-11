#include "image.h"
#include <stdio.h>
#include <stdlib.h>

struct maybe_image image_create(const uint32_t width,
                          const uint32_t height) {
    struct pixel* pixel_array = (struct pixel*) malloc(width * height * PIXEL_SIZE);
    if (!pixel_array) {
        return (struct maybe_image) {
            .valid = false,
            .img = {0}
        };
    }
    return (struct maybe_image) {
        .valid = true,
        .img = (struct image) {.width = width, .height = height, .data = pixel_array }
    };
}

void image_destroy(const struct image* image) {
    if (image && image->data) {
        free(image->data);
    }
}
