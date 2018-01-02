
#include <util/hash_2i.h>

#define HASH_HASH(key) ((uint32_t)((53377*key.x) + 248735*key.y))

#define HASH_KEY_T    hash_2i_key_t
#define HASH_ENTRY_T  hash_2i_entry_t
#define HASH_T        hash_2i_t

#define HASH_CLEAR    hash_2i_clear
#define HASH_GET      hash_2i_get_
#define HASH_SET      hash_2i_set_

#include "hash_gen.c"

#undef HASH_KEY_T
#undef HASH_ENTRY_T
#undef HASH_T

#undef HASH_CLEAR
#undef HASH_GET
#undef HASH_SET

void * hash_2i_get(hash_2i_t * h, int x, int y) {
  hash_2i_key_t key = { x, y };
  return hash_2i_get_(h, key);
}

void * hash_2i_set(hash_2i_t * h, int x, int y, void * value) {
  hash_2i_key_t key = { x, y };
  return hash_2i_set_(h, key, value);
}

void hash_2i_each(hash_2i_t * h, void (* cb)(void * data)) {
  unsigned long table_size = h->table_size;
  hash_2i_entry_t ** table = h->table;

  for(unsigned long i = 0 ; i < table_size ; i ++) {
    // iterate chain
    hash_2i_entry_t * entry = table[i];

    while(entry) {
      cb(entry->value);
      // repeat with the next
      entry = entry->next;
    }
  }
}
void hash_2i_eachd(hash_2i_t * h, void (* cb)(void * data, void * ud), void * ud) {
  unsigned long table_size = h->table_size;
  hash_2i_entry_t ** table = h->table;

  for(unsigned long i = 0 ; i < table_size ; i ++) {
    // iterate chain
    hash_2i_entry_t * entry = table[i];

    while(entry) {
      cb(entry->value, ud);
      // repeat with the next
      entry = entry->next;
    }
  }
}
void hash_2i_eachk(hash_2i_t * h, void (* cb)(int x, int y, void * data)) {
  unsigned long table_size = h->table_size;
  hash_2i_entry_t ** table = h->table;

  for(unsigned long i = 0 ; i < table_size ; i ++) {
    // iterate chain
    hash_2i_entry_t * entry = table[i];

    while(entry) {
      cb(entry->key.x, entry->key.y, entry->value);
      // repeat with the next
      entry = entry->next;
    }
  }
}
void hash_2i_eachkd(hash_2i_t * h, void (* cb)(int x, int y, void * data, void * ud), void * ud) {
  unsigned long table_size = h->table_size;
  hash_2i_entry_t ** table = h->table;

  for(unsigned long i = 0 ; i < table_size ; i ++) {
    // iterate chain
    hash_2i_entry_t * entry = table[i];

    while(entry) {
      cb(entry->key.x, entry->key.y, entry->value, ud);
      // repeat with the next
      entry = entry->next;
    }
  }
}

