#ifndef UTIL_HASHS2D_H
#define UTIL_HASHS2D_H

#include <stddef.h>

typedef struct hash2d_entry {
  int x, y;
  struct hash2d_entry * next;
  char data[];
} hash2d_entry_t;

typedef struct {
  hash2d_entry_t ** entries;
  unsigned long size;
} hash2d_t;


hash2d_t * hash2d_init(hash2d_t * h);

hash2d_t * hash2d_deinit(hash2d_t * h);

void hash2d_clear(hash2d_t * h);

void * hash2d_alloc(hash2d_t * h, int x, int y, size_t size);
void   hash2d_free(hash2d_t * h, int x, int y);
void * hash2d_get(hash2d_t * h, int x, int y);

void hash2d_each(hash2d_t * h, void (* cb)(int x, int y, void * data, void * ud), void * ud);


#endif
