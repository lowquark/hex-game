
#include <util/hash_ul.h>

// TODO: Real mixing function
#define HASH_HASH(key) ((uint32_t)(53377*(key >> 32) + 248735*key))

#define HASH_KEY_T    unsigned long
#define HASH_ENTRY_T  hash_ul_entry_t
#define HASH_T        hash_ul_t

#define HASH_CLEAR    hash_ul_clear
#define HASH_CREATE   hash_ul_create
#define HASH_DESTROY  hash_ul_destroy
#define HASH_FIND     hash_ul_find

#include "hash_gen.c"

#undef HASH_KEY_T
#undef HASH_ENTRY_T
#undef HASH_T

#undef HASH_CLEAR
#undef HASH_CREATE
#undef HASH_DESTROY
#undef HASH_FIND

void hash_ul_each(hash_ul_t * h, void (* cb)(unsigned long key, void * data, void * ud), void * ud) {
  unsigned long table_size = h->table_size;
  hash_ul_entry_t ** table = h->table;

  for(unsigned long i = 0 ; i < table_size ; i ++) {
    // iterate chain
    hash_ul_entry_t * entry = table[i];

    while(entry) {
      cb(entry->key, &entry->data, ud);
      // repeat with the next
      entry = entry->next;
    }
  }
}

