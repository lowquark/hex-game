#ifndef UTIL_HASH_2I_H
#define UTIL_HASH_2I_H

typedef struct { int x, y; } hash_2i_key_t;

#define HASH_KEY_T    hash_2i_key_t
#define HASH_ENTRY_T  hash_2i_entry_t
#define HASH_T        hash_2i_t

#define HASH_CLEAR    hash_2i_clear

#include "hash_gen.h"

#undef HASH_KEY_T
#undef HASH_ENTRY_T
#undef HASH_T

#undef HASH_CLEAR

// malloc zero'ed data indexable by x, y
void * hash_2i_create(hash_2i_t * h, int x, int y, size_t size);
// free data indexed by x, y
void   hash_2i_destroy(hash_2i_t * h, int x, int y);
// lookup data indexed by x, y
void * hash_2i_find(hash_2i_t * h, int x, int y);

// iterate all elements in the hash
void hash_2i_each(hash_2i_t * h, void (* cb)(int x, int y, void * data, void * ud), void * ud);


#endif
