#ifndef UTIL_VECTOR_H
#define UTIL_VECTOR_H

#include <stddef.h>

typedef void (* objarray_dtor_t)(void * value);

typedef struct {
  void ** entries;
  int max_entries;
  int size;
  objarray_dtor_t dtor;
} objarray_t;

objarray_t * objarray_init(objarray_t * v, objarray_dtor_t dtor);
objarray_t * objarray_deinit(objarray_t * v);

int  objarray_size(const objarray_t * v);
void objarray_resize(objarray_t * v, int len);

// constant time
void * objarray_push_back(objarray_t * v, size_t elem_size);
void   objarray_pop_back(objarray_t * v);
// O(n)
void * objarray_push_front(objarray_t * v, size_t elem_size);
void   objarray_pop_front(objarray_t * v);

void * objarray_front(const objarray_t * v);
void * objarray_back(const objarray_t * v);
void * objarray_at(const objarray_t * v, int idx);

void * objarray_set(objarray_t * v, int idx, size_t elem_size);
void   objarray_unset(objarray_t * v, int idx);

void objarray_each(const objarray_t * v, void (* fn)(int idx, void * val, void * ud), void * ud);

#endif
