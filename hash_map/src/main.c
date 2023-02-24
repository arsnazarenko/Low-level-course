#include "list.h"
#include "map.h"





int main() {
for (size_t i = 0; i < 100000; ++i) {
    struct map m = map_create();

    map_add(m, "hello", "world");
    map_add(m, "hello1", "world1");
    map_add(m, "hello2", "world2");
    map_add(m, "hello3", "world3");

    map_foreach_kvp(m, entry_print);

    printf("%s", map_get(m, "hello2"));

    map_destroy(m);
}



    return 0;
}