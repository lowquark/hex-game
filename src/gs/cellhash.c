
#include <gs/cellhash.h>

#include <stdlib.h>
#include <assert.h>

static const unsigned long initial_size = 128;

static gs_cellhash_entry_t ** entries = NULL;
static unsigned long          size = 0;

void gs_cellhash_clear(void) {
  for(unsigned long i = 0 ; i < size ; i ++) {
    // free chain
    gs_cellhash_entry_t * entry = entries[i];

    while(entry) {
      // cache next pointer
      gs_cellhash_entry_t * next = entry->next;
      // free this one
      free(entry);
      // try again with the next
      entry = next;
    }
  }

  // free buffer
  free(entries);

  // cleared!
  entries = NULL;
  size = 0;
}

void gs_cellhash_init() {
  // free anything before continuing
  gs_cellhash_clear();

  // allocate fresh
  entries = calloc(sizeof(gs_cellhash_entry_t *), initial_size);
  size = initial_size;
}

static gs_cellhash_entry_t ** bucket_of(hex_vec2i_t p) {
  assert(entries);
  assert(size > 0);

  // TODO: make better
  uint32_t hash = (uint32_t)p.x + 5000*(uint32_t)p.y;

  unsigned long idx = hash % size;

  return entries + idx;
}

static gs_cell_t * find(hex_vec2i_t p, gs_cellhash_entry_t * list) {
  while(list) {
    if(hex_vec2i_eq(list->pos, p)) {
      return &list->cell;
    }
    list = list->next;
  }
  return NULL;
}


// returns a cell in the hex hash
gs_cell_t * gs_cellhash_get(hex_vec2i_t p) {
  return find(p, *bucket_of(p));
}
// inserts a shallow copy of cell into the hex hash
gs_cell_t * gs_cellhash_set(hex_vec2i_t p, const gs_cell_t * cell) {
  gs_cellhash_entry_t ** slot = bucket_of(p);

  // advance last slot
  while(*slot) {
    gs_cellhash_entry_t * entry = *slot;

    if(hex_vec2i_eq(entry->pos, p)) {
      // already exists, just overwrite this entry
      entry->cell = *cell;
      // return the address to it
      return &entry->cell;
    }

    slot = &(*slot)->next;
  }

  // reached end of chain, create a new entry
  gs_cellhash_entry_t * new_entry = malloc(sizeof(gs_cellhash_entry_t));
  new_entry->cell = *cell;
  new_entry->pos = p;
  new_entry->next = NULL;
  *slot = new_entry;

  // return the address of the new cell
  return &new_entry->cell;
}
// erases a cell in the hex hash
void gs_cellhash_erase(hex_vec2i_t p) {
  gs_cellhash_entry_t ** slot = bucket_of(p);

  while(*slot) {
    gs_cellhash_entry_t * entry = *slot;

    if(hex_vec2i_eq(entry->pos, p)) {
      // matches, skip over
      *slot = entry->next;
      // free
      free(entry);

      return;
    }

    slot = &entry->next;
  }
}

void gs_cellhash_each(void (* cb)(hex_vec2i_t, gs_cell_t *, void *), void * ud) {
  for(unsigned long i = 0 ; i < size ; i ++) {
    // iterate chain
    gs_cellhash_entry_t * entry = entries[i];

    while(entry) {
      cb(entry->pos, &entry->cell, ud);
      // repeat with the next
      entry = entry->next;
    }
  }
}

