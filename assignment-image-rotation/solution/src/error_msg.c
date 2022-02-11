#include "error_msg.h"

char* const open_messages[] = {
    [OPEN_ERROR] = "File open error"
};
char* const close_messages[] = {
    [OPEN_ERROR] = "File open error"
};
char* const read_messages[] = {
    [READ_INVALID_SIGNATURE] = "read: invalid file signature",
    [READ_INVALID_BITS] = "read: invalid file pixel content",
    [READ_INVALID_HEADER] = "read: invalid file header",
    [READ_INVALID_INPUT_STREAM] = "read: input stream cannot be  NULL",
    [READ_DEST_NULL] = "read: image argument cannot be NULL",
    [READ_DEST_ALLOC_ERR] = "read: failed to allocate memory for image"
};
char* const write_messages[] = {
    [WRITE_ERROR] = "write: error writing to file",
    [WRITE_INVALID_OUTPUT_STREAM] = "write: output stream cannot be NULL",
    [WRITE_SRC_NULL] = "write: image argument cannot be NULL",
    [WRITE_SRC_INVALID] = "write: image argument is invalid"
};
