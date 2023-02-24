#ifndef LIST_H
#define LIST_H

#include "common.h"

typedef struct {
  const char* key;
  const char* value;
} entry;

struct list {
    entry value;
    struct list* next;
};

typedef void (entry_action)(entry);

void list_add_front(struct list** l, entry e);
void list_add_back(struct list** l, entry e);
void list_destroy(struct list* l);
void list_print(const struct list* l);


void list_foreach(struct list const* l, entry_action f);

void entry_print(entry e);

struct list* c(entry value, struct list* next);

const entry* list_find_key(struct list*, const char*);
#endif
