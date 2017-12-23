
#include <util/hash_ul.h>

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

static const unsigned long initial_size = 32;

void hash_ul_clear(hash_ul_t * h) {
  unsigned long size = h->size;
  hash_ul_entry_t ** entries = h->entries;

  for(unsigned long i = 0 ; i < size ; i ++) {
    // free chain
    hash_ul_entry_t * entry = entries[i];

    while(entry) {
      // cache next pointer
      hash_ul_entry_t * next = entry->next;
      // free this one
      free(entry);
      // try again with the next
      entry = next;
    }

    entries[i] = NULL;
  }

  // free buffer
  free(h->entries);

  // cleared!
  h->entries = NULL;
  h->size = 0;
}


static hash_ul_entry_t ** bucket_of(hash_ul_t * h, unsigned long key) {
  assert(h->entries);
  assert(h->size > 0);

  // TODO: real 64 bit mixing function
  uint32_t hash = (uint32_t)(53377*(key >> 32) + 248735*key);

  unsigned long idx = hash % h->size;

  return h->entries + idx;
}

static void * find(unsigned long key, hash_ul_entry_t * list) {
  while(list) {
    if(list->key == key) {
      return &list->data;
    }
    list = list->next;
  }
  return NULL;
}

void * hash_ul_create(hash_ul_t * h, unsigned long key, size_t data_size) {
  if(h->entries == NULL) { 
    // initialize if not already
    h->entries = calloc(sizeof(hash_ul_entry_t *), initial_size);
    h->size = initial_size;
  }

  hash_ul_entry_t ** slot = bucket_of(h, key);

  // advance last slot
  while(*slot) {
    hash_ul_entry_t * entry = *slot;

    if(entry->key == key) {
      // already exists, fail
      return NULL;
    }

    slot = &(*slot)->next;
  }

  // reached end of chain, create a new entry
  hash_ul_entry_t * new_entry = calloc(sizeof(hash_ul_entry_t) + data_size, 1);
  new_entry->key = key;
  new_entry->next = NULL;
  *slot = new_entry;

  // return the address of the new data
  return &new_entry->data;
}
void hash_ul_destroy(hash_ul_t * h, unsigned long key) {
  if(h->entries == NULL) { return; }

  hash_ul_entry_t ** slot = bucket_of(h, key);

  while(*slot) {
    hash_ul_entry_t * entry = *slot;

    if(entry->key == key) {
      // matches, skip over
      *slot = entry->next;
      // free
      free(entry);

      return;
    }

    slot = &entry->next;
  }
}
void * hash_ul_find(hash_ul_t * h, unsigned long key) {
  if(h->entries == NULL) { return NULL; }

  return find(key, *bucket_of(h, key));
}

void hash_ul_each(hash_ul_t * h, void (* cb)(unsigned long key, void * data, void * ud), void * ud) {
  unsigned long size = h->size;
  hash_ul_entry_t ** entries = h->entries;

  for(unsigned long i = 0 ; i < size ; i ++) {
    // iterate chain
    hash_ul_entry_t * entry = entries[i];

    while(entry) {
      cb(entry->key, &entry->data, ud);
      // repeat with the next
      entry = entry->next;
    }
  }
}

