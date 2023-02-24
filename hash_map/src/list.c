#include "list.h"
#include "common.h"
#include <malloc.h>
#include <string.h>


//  static - ограничивает область видимости функции/переменной
//  только файлом, в котором определена эты функция/переменная
//  хорошей практикой считается добавление static к любому функционалу
//  который вы создали для удобства, и в интерфейс работы с вашей
//  сущностью включать его не хотите
static struct list* node_create(entry e) {
    struct list* result = malloc(sizeof(struct list));
    *result = (struct list) {.value = e, .next = NULL};
    return result;
}

void list_add_front(struct list** l, entry e) {
    if (*l) {
        struct list* const old_start = *l;
        *l = node_create(e);
        (*l)->next = old_start;
    } else {
        *l = node_create(e);
    }
}
struct list* list_last(struct list* l) {
    if (l == NULL) {
        return NULL;
    }
    struct list* cur = l;
    while(cur->next != NULL) {
        cur = cur->next;
    }
    return cur;
}

//struct list** list_last1(struct list** l) {
//    struct list** cur = l;
//    while(*cur) { cur = &( (*cur) -> next ) }
//    return cur
//}

void list_add_back(struct list** l, entry e) {
    if (*l) {
        list_last(*l)->next = node_create(e);
    } else {
        list_add_front(l , e);
    }
}

void list_destroy(struct list* l) {
    if (! l) return;

    struct list* cur = l;
    while(cur) {
        struct list* next = cur->next;
        free(cur);
        cur = next;
    }
}

void list_foreach(const struct list* l, entry_action f) {
    for (const struct list* cur = l; cur; cur = cur->next) {
        f(cur->value);
    }
}

void entry_print(entry e) {
    printf("%s -> %s\n", e.key, e.value);
    print_newline();
}
const entry* list_find_key(struct list* l, const char* query) {
    for(const struct list* cur = l; cur; cur=cur->next) {
        if (0 == strcmp(query, cur->value.key)) {
            return &(cur->value);
        }
    }
    return NULL;
}

struct list* c(entry value, struct list* next) {
    struct list* l = node_create(value);
    l -> next = next;
    return l;
}




