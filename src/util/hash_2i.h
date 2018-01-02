#ifndef UTIL_HASH_2I_H
#define UTIL_HASH_2I_H


typedef struct { int x, y; } hash_2i_key_t;


#define HASH_KEY_T    hash_2i_key_t
#define HASH_ENTRY_T  hash_2i_entry_t
#define HASH_T        hash_2i_t

#define HASH_CLEAR    hash_2i_clear
#define HASH_CLEAR    hash_2i_clear

#include "hash_gen.h"

#undef HASH_KEY_T
#undef HASH_ENTRY_T
#undef HASH_T

#undef HASH_CLEAR


// lookup data indexed by x, y
void * hash_2i_get(hash_2i_t * h, int x, int y);
// set data indexed by x, y
void * hash_2i_set(hash_2i_t * h, int x, int y, void * value);


// iterate all elements in the hash
void hash_2i_each  (hash_2i_t * h, void (* each_fn)(void * value));
void hash_2i_eachd (hash_2i_t * h, void (* each_fn)(void * value, void * ud), void * ud);
void hash_2i_eachk (hash_2i_t * h, void (* each_fn)(int x, int y, void * value));
void hash_2i_eachkd(hash_2i_t * h, void (* each_fn)(int x, int y, void * value, void * ud), void * ud);

// iterate all elements in the hash, erase if callback returns nonzero
void hash_2i_eraseif  (hash_2i_t * h, int (* eraseif_fn)(void * value));
void hash_2i_eraseifd (hash_2i_t * h, int (* eraseif_fn)(void * value, void * ud), void * ud);
void hash_2i_eraseifk (hash_2i_t * h, int (* eraseif_fn)(int x, int y, void * value));
void hash_2i_eraseifkd(hash_2i_t * h, int (* eraseif_fn)(int x, int y, void * value, void * ud), void * ud);


#endif
