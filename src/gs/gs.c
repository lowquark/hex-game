
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <gs/gs.h>
#include <gs/cellhash.h>

#define ZERO(_item_) \
  memset(&_item_, 0, sizeof(_item_))

#define MALLOC_ARRAY_FREE(_ptr_, _len_) { \
  free(_ptr_); \
  _ptr_ = NULL; \
  _len_ = 0; \
}

#define MALLOC_ARRAY_COPY(_dst_, _dstlen_, _src_, _srclen_) { \
  free(_dst_); \
  if(_srclen_ > 0) { \
    size_t src_size = sizeof(*_src_)*(size_t)_srclen_; \
    _dst_ = (__typeof__(_src_))malloc(src_size); \
    _dstlen_ = _srclen_; \
    memcpy(_dst_, _src_, src_size); \
  } else { \
    _dst_ = NULL; \
    _dstlen_ = 0; \
  } \
}


static void cell_deinit(gs_cell_t * cell) {
  MALLOC_ARRAY_FREE(cell->mobs, cell->mob_num);
  MALLOC_ARRAY_FREE(cell->items, cell->item_num);
}
static void cell_copy(gs_cell_t * cell, const gs_cell_t * other_cell) {
  // copy tile
  cell->tile = other_cell->tile;
  // copy items
  MALLOC_ARRAY_COPY(cell->items, cell->item_num, other_cell->items, other_cell->item_num);
  // copy mobs
  MALLOC_ARRAY_COPY(cell->mobs, cell->mob_num, other_cell->mobs, other_cell->mob_num);
}


void gs_init(void) {
  gs_deinit();

  // init cell hash
  gs_cellhash_init();
}

static void gs_deinit_cell_deinit(hex_vec2i_t pos, gs_cell_t * cell, void * _) {
  // deinit cell
  cell_deinit(cell);
}
void gs_deinit(void) {
  // destroy all cells
  gs_cellhash_each(gs_deinit_cell_deinit, NULL);
  // clear all cells
  gs_cellhash_clear();
}

void gs_clear(void) {
  gs_deinit();
}


const gs_cell_t * gs_get_cell(hex_vec2i_t p) {
  return gs_cellhash_get(p);
}
void gs_set_cell(hex_vec2i_t p, const gs_cell_t * cell) {
  // this cell will be shallow copied into the hash
  gs_cell_t new_cell;
  ZERO(new_cell);
  cell_copy(&new_cell, cell);

  gs_cell_t * old_cell = gs_cellhash_get(p);
  if(old_cell) {
    cell_deinit(old_cell);
    *old_cell = new_cell;
  } else {
    gs_cellhash_set(p, &new_cell);
  }
}

