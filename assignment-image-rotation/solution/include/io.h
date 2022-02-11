#ifndef LAB_IO_H
#define LAB_IO_H
#include<stdio.h>

enum read_status {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    READ_INVALID_INPUT_STREAM,
    READ_DEST_NULL,
    READ_DEST_ALLOC_ERR
};

enum write_status {
    WRITE_OK = 0,
    WRITE_ERROR,
    WRITE_INVALID_OUTPUT_STREAM,
    WRITE_SRC_NULL,
    WRITE_SRC_INVALID
};

enum open_status {
    OPEN_OK = 0,
    OPEN_ERROR
};

enum close_status {
    CLOSE_OK = 0,
    CLOSE_ERROR
};

enum open_status file_open(FILE** file, const char* filepath, const char* modes);

enum close_status file_close(FILE** file);

#endif

