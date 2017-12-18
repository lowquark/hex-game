#ifndef UTIL_VECTOR_H
#define UTIL_VECTOR_H

typedef struct {
  void ** entries;
  int entries_size;
  int size;
} vector_t;

vector_t * vector_init(vector_t * v);
vector_t * vector_deinit(vector_t * v);

int  vector_size(vector_t * v);
void vector_resize(vector_t * v, int len);

void * vector_alloc(vector_t * v, int idx, size_t elem_size);
void * vector_free(vector_t * v, int idx);

void * vector_push_back(vector_t * v, size_t elem_size);
void   vector_pop_back(vector_t * v);

void * vector_front(vector_t * v);
void * vector_back(vector_t * v);
void * vector_at(vector_t * v, int idx);

#endif
