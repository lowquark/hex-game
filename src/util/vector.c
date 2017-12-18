
#include <util/hash2d.h>

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

static const unsigned int initial_size = 32;

vector_t * vector_init(vector_t * v) {
  return v;
}
vector_t * vector_deinit(vector_t * v) {
  return v;
}

int vector_size(vector_t * v) {
  return 0;
}
void vector_resize(vector_t * v, int len) {
}

void * vector_alloc(vector_t * v, int idx, size_t elem_size) {
  return NULL;
}
void * vector_free(vector_t * v, int idx) {
  return NULL;
}

void * vector_push_back(vector_t * v, size_t elem_size) {
  return NULL;
}
void vector_pop_back(vector_t * v) {
}

void * vector_front(vector_t * v) {
  return NULL;
}
void * vector_back(vector_t * v) {
  return NULL;
}
void * vector_at(vector_t * v, int idx) {
  return NULL;
}

