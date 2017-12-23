
#include <util/hash_2i.h>

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>


static const unsigned long initial_size = 32;


void hash_2i_clear(hash_2i_t * h) {
  unsigned long size = h->size;
  hash_2i_entry_t ** entries = h->entries;

  for(unsigned long i = 0 ; i < size ; i ++) {
    // free chain
    hash_2i_entry_t * entry = entries[i];

    while(entry) {
      // cache next pointer
      hash_2i_entry_t * next = entry->next;
      // free this one
      free(entry);
      // try again with the next
      entry = next;
    }

    entries[i] = 0;
  }

  // free buffer
  free(h->entries);

  // cleared!
  h->entries = NULL;
  h->size = 0;
}


static hash_2i_entry_t ** bucket_of(hash_2i_t * h, int x, int y) {
  assert(h->entries);
  assert(h->size > 0);

  // TODO: make better
  uint32_t hash = (uint32_t)x + 5000*(uint32_t)y;

  unsigned long idx = hash % h->size;

  return h->entries + idx;
}

static void * find(int x, int y, hash_2i_entry_t * list) {
  while(list) {
    if(list->x == x && list->y == y) {
      return &list->data;
    }
    list = list->next;
  }
  return NULL;
}


void * hash_2i_create(hash_2i_t * h, int x, int y, size_t size) {
  if(h->entries == NULL) { 
    // initialize if not already
    h->entries = calloc(sizeof(hash_2i_entry_t *), initial_size);
    h->size = initial_size;
  }

  hash_2i_entry_t ** slot = bucket_of(h, x, y);

  // advance last slot
  while(*slot) {
    hash_2i_entry_t * entry = *slot;

    if(entry->x == x && entry->y == y) {
      // already exists, fail
      return NULL;
    }

    slot = &(*slot)->next;
  }

  // reached end of chain, create a new entry
  hash_2i_entry_t * new_entry = calloc(sizeof(hash_2i_entry_t) + size, 1);
  new_entry->x = x;
  new_entry->y = y;
  new_entry->next = NULL;
  *slot = new_entry;

  // return the address of the new data
  return &new_entry->data;
}

void hash_2i_destroy(hash_2i_t * h, int x, int y) {
  if(h->entries == NULL) { return; }

  hash_2i_entry_t ** slot = bucket_of(h, x, y);

  while(*slot) {
    hash_2i_entry_t * entry = *slot;

    if(entry->x == x && entry->y == y) {
      // matches, skip over
      *slot = entry->next;
      // free
      free(entry);

      return;
    }

    slot = &entry->next;
  }
}

void * hash_2i_find(hash_2i_t * h, int x, int y) {
  if(h->entries == NULL) { return NULL; }

  return find(x, y, *bucket_of(h, x, y));
}

void hash_2i_each(hash_2i_t * h, void (* cb)(int x, int y, void * data, void * ud), void * ud) {
  unsigned long size = h->size;
  hash_2i_entry_t ** entries = h->entries;

  for(unsigned long i = 0 ; i < size ; i ++) {
    // iterate chain
    hash_2i_entry_t * entry = entries[i];

    while(entry) {
      cb(entry->x, entry->y, &entry->data, ud);
      // repeat with the next
      entry = entry->next;
    }
  }
}


