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

#endif
