#ifndef UTIL_HASH_2I_H
#define UTIL_HASH_2I_H

#include <stddef.h>

typedef struct hash_2i_entry {
  int x;
  int y;
  struct hash_2i_entry * next;
  char data[];
} hash_2i_entry_t;

typedef struct {
  hash_2i_entry_t ** entries;
  unsigned long size;
} hash_2i_t;

#define HASH_2I_INIT { NULL, 0 }


void hash_2i_clear(hash_2i_t * h);

// malloc zero'ed data indexable by x, y
void * hash_2i_create(hash_2i_t * h, int x, int y, size_t size);
// free data indexed by x, y
void   hash_2i_destroy(hash_2i_t * h, int x, int y);
// lookup data indexed by x, y
void * hash_2i_find(hash_2i_t * h, int x, int y);

// iterate all elements in the hash
void hash_2i_each(hash_2i_t * h, void (* cb)(int x, int y, void * data, void * ud), void * ud);


#endif
