#include "bmp.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


struct __attribute__((packed)) bmp_header {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

#define BMP_HEADER_SIZE sizeof(struct bmp_header)
#define BMP_INFO_HEADER_SIZE 40
#define BMP_SIGNATURE 0x4D42
#define BMP_BITS_PER_COLOR 24
#define BMP_PLANES_NUMBER 1
#define BMP_COMPRESSION 0
#define BMP_RESERVED 0
#define BMP_X_PIX_PER_METER 0
#define BMP_Y_PIX_PER_METER 0
#define BMP_COLOR_USED 0
#define BMP_COLOR_IMPORTANT 0
static const uint8_t ZERO[4] = {0};


static bool bmp_header_read(FILE *in, struct bmp_header* header) {
    return ( fread(header,1,  BMP_HEADER_SIZE, in) == BMP_HEADER_SIZE );
}

static bool bmp_header_write(FILE* out, const struct bmp_header* header) {
    return ( fwrite(header, 1, BMP_HEADER_SIZE, out) == BMP_HEADER_SIZE );
}

static uint8_t get_padding(const uint32_t width) {
    return ((4 - ((width * PIXEL_SIZE) % 4)) % 4);
}

static enum read_status bmp_header_check(const struct bmp_header* header) {
    if (header->biBitCount != BMP_BITS_PER_COLOR
        || header->biCompression != 0
        || header->biSize != BMP_INFO_HEADER_SIZE
        || header->biPlanes != BMP_PLANES_NUMBER) {
        return READ_INVALID_HEADER;
    }
    if (header->bfType != BMP_SIGNATURE) {
        return READ_INVALID_SIGNATURE;
    }
    return READ_OK;
}

static bool pixel_array_read(FILE* in,
                             const uint8_t padding,
                             struct image* image) {
    for (size_t row = 0; row < image->height; ++row) {
        if (fread(&(image->data[row * image->width]), PIXEL_SIZE, image->width, in) < image->width) {
            return false;
        }
        if (fseek(in, padding, SEEK_CUR) != 0) {
            return false;
        }
    }
    return true;
}



static struct bmp_header bmp_header_create(const uint32_t width,
                                           const uint32_t height) {
    const size_t image_size = (height * (width + get_padding(width))) * PIXEL_SIZE;
    return (struct bmp_header) {
            .bfType = BMP_SIGNATURE,
            .biHeight = height,
            .biWidth = width,
            .bOffBits = BMP_HEADER_SIZE,
            .biSize = BMP_INFO_HEADER_SIZE,
            .biPlanes = BMP_PLANES_NUMBER,
            .bfileSize = BMP_HEADER_SIZE + image_size,
            .biCompression = BMP_COMPRESSION,
            .bfReserved = BMP_RESERVED,
            .biBitCount = BMP_BITS_PER_COLOR,
            .biXPelsPerMeter = BMP_X_PIX_PER_METER,
            .biYPelsPerMeter = BMP_Y_PIX_PER_METER,
            .biClrUsed = BMP_COLOR_USED,
            .biClrImportant = BMP_COLOR_IMPORTANT,
            .biSizeImage = image_size
    };
}

static bool pixel_array_write(FILE* out,
                              const size_t padding,
                              const struct image* image) {
    for (size_t row = 0; row < image->height; ++row) {
        if (fwrite(&(image->data[row * image->width]), PIXEL_SIZE,  image->width,out) < image->width) {
            return false;
        }
        if (fwrite(&ZERO, 1, padding, out) < padding) {
            return false;
        }
    }
    return true;
}

enum read_status from_bmp(FILE *in, struct image *image) {
    if (!in) return READ_INVALID_INPUT_STREAM;
    if (!image) return READ_DEST_NULL;
    struct bmp_header header = {0};
    if (!bmp_header_read(in, &header)) {
        return READ_INVALID_HEADER;
    }
    enum read_status header_status = bmp_header_check(&header);
    if (header_status != READ_OK) {
        return header_status;
    }
    struct maybe_image maybe = image_create(header.biWidth, header.biHeight);
    if (!maybe.valid) {
        return READ_DEST_ALLOC_ERR;
    }
    *image = maybe.img;
    const uint8_t padding = get_padding(header.biWidth);
    const size_t offset = header.bOffBits - BMP_HEADER_SIZE;
    if (fseek(in, offset, SEEK_CUR) != 0) {
        return READ_INVALID_BITS;
    }
    if (!pixel_array_read(in, padding, image)) {
        image_destroy(image);
        return READ_INVALID_BITS;
    }
    return READ_OK;
}

enum write_status to_bmp(FILE *out, const struct image *image) {
    if (!out) return WRITE_INVALID_OUTPUT_STREAM;
    if (!image) return WRITE_SRC_NULL;
    if (!image->data) return WRITE_SRC_INVALID;
    const struct bmp_header header = bmp_header_create(image->width, image->height);
    if (!bmp_header_write(out, &header)) {
        return WRITE_ERROR;
    }
    const size_t padding = get_padding(image->width);
    if (!pixel_array_write(out, padding, image)) {
        return WRITE_ERROR;
    }
    return WRITE_OK;
}

