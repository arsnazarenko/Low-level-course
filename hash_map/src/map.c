#include "map.h"
#include <string.h>
#include <malloc.h>
#include "hash.h"

//struct map {
//    struct list* buckets;
//};


struct map map_create(void) {
    return (struct map) {
        //  выделяем и зануляем память под массив бакетов, потому что иначе
        //  у нас как буто будут лежать в массиве адреса первых
        //  элементов связных спсков
        .buckets = calloc( MAP_SIZE, sizeof(struct list*) )
    };
}
void map_destroy(struct map m) {
    for (size_t i = 0; i < MAP_SIZE; ++i) {
        if (m.buckets[i]) {
            list_destroy(m.buckets[i]);
        }
    }
    free(m.buckets);
}

//  по ключу возвращает указатель на указатель
//  на первый элеменет списка
static struct list** map_find_list( struct map m, key k ) {
    const size_t sz = strlen(k);
    const hash h = hash_compute(k, sz);
    return m.buckets + (h % MAP_SIZE);
}

void map_add(struct map m, key k, value v) {
    struct list** l = map_find_list(m, k);
    list_add_front(l, (entry) {.key = k, .value = v});
}
void map_foreach_kvp(struct map m, kvp_action action) {
    for (size_t i = 0; i < MAP_SIZE; i++) {
        if (m.buckets[i]) {
            list_foreach(m.buckets[i], action);
        }
    }
}
const value map_get(struct map m, const key k ) {
    struct list** l = map_find_list(m, k);
    const entry* e = list_find_key(*l, k);
    return e->value;
}
