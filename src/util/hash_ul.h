#ifndef UTIL_HASH64_H
#define UTIL_HASH64_H

#define HASH_KEY_T    unsigned long
#define HASH_ENTRY_T  hash_ul_entry_t
#define HASH_T        hash_ul_t

#define HASH_CLEAR    hash_ul_clear
#define HASH_CREATE   hash_ul_create
#define HASH_DESTROY  hash_ul_destroy
#define HASH_FIND     hash_ul_find

#include "hash_gen.h"

#undef HASH_KEY_T
#undef HASH_ENTRY_T
#undef HASH_T

#undef HASH_CLEAR
#undef HASH_CREATE
#undef HASH_DESTROY
#undef HASH_FIND

// iterate all elements in the hash
void hash_ul_each(hash_ul_t * h, void (* cb)(unsigned long key, void * data, void * ud), void * ud);

/*
typedef struct {
  hash_ul_entry_t ** lcur;
  hash_ul_entry_t ** lend;
  hash_ul_entry_t * e;
  void * elem;
  unsigned long key;
} hash_ul_iter;

static inline void hash_ul_first(hash_ul_iter * it, hash_ul_t * h) {
  it->lcur = h->table;
  it->lend = h->table + h->table_size;
}
static inline void hash_ul_next(hash_ul_iter * it) {
}
*/

#endif
