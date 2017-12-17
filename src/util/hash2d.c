
#include <util/hash2d.h>

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

static const unsigned long initial_size = 128;


hash2d_t * hash2d_init(hash2d_t * h) {
  // allocate fresh
  h->entries = calloc(sizeof(hash2d_entry_t *), initial_size);
  h->size = initial_size;
  return h;
}

hash2d_t * hash2d_deinit(hash2d_t * h) {
  unsigned long size = h->size;
  hash2d_entry_t ** entries = h->entries;

  for(unsigned long i = 0 ; i < size ; i ++) {
    // free chain
    hash2d_entry_t * entry = entries[i];

    while(entry) {
      // cache next pointer
      hash2d_entry_t * next = entry->next;
      // free this one
      free(entry);
      // try again with the next
      entry = next;
    }
  }

  // free buffer
  free(h->entries);

  // cleared!
  h->entries = NULL;
  h->size = 0;

  return h;
}


static hash2d_entry_t ** bucket_of(hash2d_t * h, int x, int y) {
  assert(h->entries);
  assert(h->size > 0);

  // TODO: make better
  uint32_t hash = (uint32_t)x + 5000*(uint32_t)y;

  unsigned long idx = hash % h->size;

  return h->entries + idx;
}

static void * find(int x, int y, hash2d_entry_t * list) {
  while(list) {
    if(list->x == x && list->y == y) {
      return &list->data;
    }
    list = list->next;
  }
  return NULL;
}


void * hash2d_alloc(hash2d_t * h, int x, int y, size_t size) {
  hash2d_entry_t ** slot = bucket_of(h, x, y);

  // advance last slot
  while(*slot) {
    hash2d_entry_t * entry = *slot;

    if(entry->x == x && entry->y == y) {
      // already exists, fail
      return NULL;
    }

    slot = &(*slot)->next;
  }

  // reached end of chain, create a new entry
  hash2d_entry_t * new_entry = calloc(sizeof(hash2d_entry_t) + size, 1);
  new_entry->x = x;
  new_entry->y = y;
  new_entry->next = NULL;
  *slot = new_entry;

  // return the address of the new data
  return &new_entry->data;
}

void hash2d_free(hash2d_t * h, int x, int y) {
  hash2d_entry_t ** slot = bucket_of(h, x, y);

  while(*slot) {
    hash2d_entry_t * entry = *slot;

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

void * hash2d_get(hash2d_t * h, int x, int y) {
  return find(x, y, *bucket_of(h, x, y));
}

void hash2d_each(hash2d_t * h, void (* cb)(int x, int y, void * data, void * ud), void * ud) {
  unsigned long size = h->size;
  hash2d_entry_t ** entries = h->entries;

  for(unsigned long i = 0 ; i < size ; i ++) {
    // iterate chain
    hash2d_entry_t * entry = entries[i];

    while(entry) {
      cb(entry->x, entry->y, &entry->data, ud);
      // repeat with the next
      entry = entry->next;
    }
  }
}


