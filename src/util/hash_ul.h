#ifndef UTIL_HASH64_H
#define UTIL_HASH64_H

#include <stddef.h>

typedef struct hash_ul_entry {
  struct hash_ul_entry * next;
  unsigned long key;
  char data[];
} hash_ul_entry_t;

typedef struct {
  hash_ul_entry_t ** entries;
  unsigned long size;
} hash_ul_t;


void hash_ul_clear(hash_ul_t * h);

void * hash_ul_create (hash_ul_t * h, unsigned long key, size_t data_size);
void   hash_ul_destroy(hash_ul_t * h, unsigned long key);
void * hash_ul_find   (hash_ul_t * h, unsigned long key);

void hash_ul_each(hash_ul_t * h, void (* cb)(unsigned long key, void * data, void * ud), void * ud);

#endif
