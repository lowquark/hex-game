#ifndef GS_CELLHASH_H
#define GS_CELLHASH_H

#include <hex/hex.h>

#include <gs/cell.h>

typedef struct gs_cellhash_entry {
  hex_vec2i_t pos;
  gs_cell_t cell;
  struct gs_cellhash_entry * next;
} gs_cellhash_entry_t;


// initializes the cell hash
void gs_cellhash_init(void);

// clears all cells in the cell hash
void gs_cellhash_clear(void);


// returns a cell in the hex hash
gs_cell_t * gs_cellhash_get(hex_vec2i_t p);

// sets a shallow copy of cell in the hex hash
gs_cell_t * gs_cellhash_set(hex_vec2i_t p, const gs_cell_t * cell);

// erases a cell in the hex hash
void gs_cellhash_erase(hex_vec2i_t p);

// don't call erase or set while iterating
void gs_cellhash_each(void (* cb)(hex_vec2i_t, gs_cell_t *, void *), void * ud);


#endif
