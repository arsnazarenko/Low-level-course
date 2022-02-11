#ifndef LAB_SERIALIZATION_H
#define LAB_SERIALIZATION_H
#include <stdbool.h>
#include "image.h"
#include "io.h"

typedef enum write_status (*format_serializer)(FILE*, const struct image*);
typedef enum read_status (*format_deserializer)(FILE*, struct image*);


bool image_deserialize(const char* in, struct image* img, format_deserializer des);
bool image_serialize(const char* out, const struct image* img, format_serializer ser);

#endif
