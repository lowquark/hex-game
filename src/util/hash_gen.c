
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

static const unsigned long initial_size = 32;

static inline int key_eq(HASH_KEY_T key0, HASH_KEY_T key1) {
  return memcmp(&key0, &key1, sizeof(HASH_KEY_T)) == 0;
}

static unsigned long hash_idx(HASH_KEY_T key, unsigned long table_size) {
  assert(table_size > 0);

  return HASH_HASH(key) % table_size;
}

static HASH_ENTRY_T ** bucket_of(HASH_T * h, HASH_KEY_T key) {
  assert(h->table);

  return h->table + hash_idx(key, h->table_size);
}

static void * find(HASH_KEY_T key, HASH_ENTRY_T * list) {
  while(list) {
    if(key_eq(list->key, key)) {
      return &list->data;
    }
    list = list->next;
  }
  return NULL;
}

static void resize_table(HASH_T * h, unsigned long newsize) {
  unsigned long table_size = h->table_size;
  HASH_ENTRY_T ** table = h->table;
  HASH_ENTRY_T ** newtable = calloc(sizeof(*newtable), newsize);

  for(unsigned long i = 0 ; i < table_size ; i ++) {
    // free chain
    HASH_ENTRY_T * entry = table[i];

    while(entry) {
      // save next pointer
      HASH_ENTRY_T * next = entry->next;

      unsigned long idx = hash_idx(entry->key, newsize);

      // lookup chain in the new table
      HASH_ENTRY_T ** slot = newtable + idx;

      // advance slot in the new chain
      while(*slot) {
        assert(!key_eq((*slot)->key, entry->key));
        slot = &(*slot)->next;
      }

      // place at end of destination chain
      *slot = entry;
      entry->next = NULL;

      // repeate again with the next entry in the old chain
      entry = next;
    }
  }

  free(table);
  h->table = newtable;
  h->table_size = newsize;
}

void HASH_CLEAR(HASH_T * h) {
  unsigned long table_size = h->table_size;
  HASH_ENTRY_T ** table = h->table;

  for(unsigned long i = 0 ; i < table_size ; i ++) {
    // free chain
    HASH_ENTRY_T * entry = table[i];

    while(entry) {
      // cache next pointer
      HASH_ENTRY_T * next = entry->next;
      // free this one
      free(entry);
      // try again with the next
      entry = next;
    }

    table[i] = NULL;
  }

  // free buffer
  free(h->table);

  // cleared!
  h->table = NULL;
  h->table_size = 0;
}

void * HASH_CREATE(HASH_T * h, HASH_KEY_T key, size_t data_size) {
  if(h->table == NULL) { 
    // initialize if not already
    h->table = calloc(sizeof(HASH_ENTRY_T *), initial_size);
    h->table_size = initial_size;
  }

  if(h->entry_count > h->table_size*2) {
    resize_table(h, h->table_size * 2);
  }

  HASH_ENTRY_T ** slot = bucket_of(h, key);

  // advance last slot
  while(*slot) {
    HASH_ENTRY_T * entry = *slot;

    if(key_eq(entry->key, key)) {
      // already exists, fail
      return NULL;
    }

    slot = &(*slot)->next;
  }

  // reached end of chain, create a new entry
  HASH_ENTRY_T * new_entry = calloc(sizeof(HASH_ENTRY_T) + data_size, 1);
  new_entry->key = key;
  new_entry->next = NULL;
  *slot = new_entry;

  h->entry_count ++;

  // return the address of the new data
  return &new_entry->data;
}
void HASH_DESTROY(HASH_T * h, HASH_KEY_T key) {
  if(h->table == NULL) { return; }

  HASH_ENTRY_T ** slot = bucket_of(h, key);

  while(*slot) {
    HASH_ENTRY_T * entry = *slot;

    if(key_eq(entry->key, key)) {
      // matches, skip over
      *slot = entry->next;
      // free
      free(entry);

      h->entry_count --;

      return;
    }

    slot = &entry->next;
  }
}
void * HASH_FIND(HASH_T * h, HASH_KEY_T key) {
  if(h->table == NULL) { return NULL; }

  return find(key, *bucket_of(h, key));
}

