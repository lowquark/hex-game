
#include <util/objarray.h>

#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>

static const int initial_size = 32;
static const int size_max = INT_MAX;

objarray_t * objarray_init(objarray_t * v, objarray_dtor_t dtor) {
  v->entries = NULL;
  v->max_entries = 0;
  v->size = 0;
  v->dtor = dtor;
  return v;
}
objarray_t * objarray_deinit(objarray_t * v) {
  int size = v->size;
  objarray_dtor_t dtor = v->dtor;

  if(dtor) {
    // call dtor before freeing
    for(int i = 0 ; i < size ; i ++) {
      void * entry = v->entries[i];
      if(entry) {
        dtor(entry);
        free(entry);
        v->entries[i] = 0;
      }
    }
  } else {
    // just free
    for(int i = 0 ; i < size ; i ++) {
      free(v->entries[i]);
      v->entries[i] = 0;
    }
  }

  free(v->entries);
  memset(v, 0, sizeof(*v));

  return v;
}

static void objarray_ensure(objarray_t * v, int new_size) {
  if(v->max_entries < new_size) {
    int alloc_size = v->max_entries ? v->max_entries * 2 : initial_size;

    while(alloc_size < new_size) { alloc_size *= 2; } 

    v->entries = (void **)realloc(v->entries, alloc_size * sizeof(void *));
    v->max_entries = alloc_size;
  }
}

int objarray_size(const objarray_t * v) {
  return v->size;
}
void objarray_resize(objarray_t * v, int new_size) {
  assert(new_size <= size_max);
}

// constant time
void * objarray_push_back(objarray_t * v, size_t elem_size)
{
  assert(v->size < size_max);

  // ensure we have space for this one
  objarray_ensure(v, v->size + 1);

  void * value = calloc(elem_size, 1);

  v->entries[v->size] = value;
  v->size ++;

  return value;
}
void objarray_pop_back(objarray_t * v)
{
  // C89 style
  int size;
  int idx;
  objarray_dtor_t dtor;

  size = v->size;

  if(size > 0) {
    dtor = v->dtor;
    idx = v->size - 1;

    if(dtor) {
      dtor(v->entries[idx]);
    }

    free(v->entries[idx]);
    v->entries[idx] = NULL;

    v->size = idx;
  }
}
// O(n)
void * objarray_push_front(objarray_t * v, size_t elem_size)
{
  return NULL;
}
void objarray_pop_front(objarray_t * v)
{
}

void * objarray_front(const objarray_t * v)
{
  if(v->size > 0) {
    return v->entries[0];
  } else {
    return NULL;
  }
}
void * objarray_back(const objarray_t * v)
{
  if(v->size > 0) {
    return v->entries[v->size - 1];
  } else {
    return NULL;
  }
}
void * objarray_at(const objarray_t * v, int idx)
{
  if(idx >= 0 && idx < v->size) {
    return v->entries[idx];
  } else {
    return NULL;
  }
}

void * objarray_set(objarray_t * v, int idx, size_t elem_size)
{
  if(idx >= 0 && idx < v->size) {
    void * value = v->entries[idx];

    if(value) {
      objarray_dtor_t dtor = v->dtor;

      if(dtor) {
        dtor(value);
      }
      free(value);
    }

    value = calloc(elem_size, 1);
    v->entries[idx] = value;
    return value;
  } else {
    return NULL;
  }
}
void objarray_unset(objarray_t * v, int idx)
{
  if(idx >= 0 && idx < v->size) {
    void * value = v->entries[idx];

    if(value) {
      objarray_dtor_t dtor = v->dtor;

      if(dtor) {
        dtor(value);
      }
      free(value);

      v->entries[idx] = NULL;
    }
  }
}

void objarray_each(const objarray_t * v, void (* fn)(int idx, void * val, void * ud), void * ud)
{
  int size = v->size;

  for(int i = 0 ; i < size ; i ++) {
    fn(i, v->entries[i], ud);
  }
}

