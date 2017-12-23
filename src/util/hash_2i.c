
#include <util/hash_2i.h>

#define HASH_HASH(key) ((uint32_t)((53377*key.x) + 248735*key.y))

#define HASH_KEY_T    hash_2i_key_t
#define HASH_ENTRY_T  hash_2i_entry_t
#define HASH_T        hash_2i_t

#define HASH_CLEAR    hash_2i_clear
#define HASH_CREATE   hash_2i_create_
#define HASH_DESTROY  hash_2i_destroy_
#define HASH_FIND     hash_2i_find_

#include "hash_gen.c"

#undef HASH_KEY_T
#undef HASH_ENTRY_T
#undef HASH_T

#undef HASH_CLEAR
#undef HASH_CREATE
#undef HASH_DESTROY
#undef HASH_FIND

void * hash_2i_create(hash_2i_t * h, int x, int y, size_t size) {
  hash_2i_key_t key = { x, y };
  return hash_2i_create_(h, key, size);
}

void hash_2i_destroy(hash_2i_t * h, int x, int y) {
  hash_2i_key_t key = { x, y };
  hash_2i_destroy_(h, key);
}

void * hash_2i_find(hash_2i_t * h, int x, int y) {
  hash_2i_key_t key = { x, y };
  return hash_2i_find_(h, key);
}

void hash_2i_each(hash_2i_t * h, void (* cb)(int x, int y, void * data, void * ud), void * ud) {
  unsigned long table_size = h->table_size;
  hash_2i_entry_t ** table = h->table;

  for(unsigned long i = 0 ; i < table_size ; i ++) {
    // iterate chain
    hash_2i_entry_t * entry = table[i];

    while(entry) {
      cb(entry->key.x, entry->key.y, &entry->data, ud);
      // repeat with the next
      entry = entry->next;
    }
  }
}

