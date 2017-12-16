#ifndef GS_GS_H
#define GS_GS_H

#include <stdint.h>

#include <hex/hex.h>

#include <gs/cell.h>

typedef struct {
  int x, y;
} vec2i_t;

typedef struct {
  int x, y, w, h;
} rect2i_t;


void gs_init(void);
void gs_deinit(void);

void gs_clear(void);

// retrieves a cell from the cell hash
const gs_cell_t * gs_get_cell(hex_vec2i_t p);
// performs a deep copy on `cell` and stores it in the cell hash
void              gs_set_cell(hex_vec2i_t p, const gs_cell_t * cell);


#endif
