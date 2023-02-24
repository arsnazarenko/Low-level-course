#ifndef MAP_H
#define MAP_H


#include "common.h"
#include "list.h"


#define MAP_SIZE 65537

typedef const char* key;
typedef const char* value;
typedef void (kvp_action)(entry);
struct map {
    struct list** buckets;
};


struct map map_create(void);
void map_destroy(struct map);
void map_add(struct map, key, value);
void map_foreach_kvp(struct map, kvp_action);
const value map_get(struct map, const key );
#endif