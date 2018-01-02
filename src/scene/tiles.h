#ifndef SCENE_TILES_H
#define SCENE_TILES_H

#include <hex/hex.h>

#include <scene/tile.h>


// unload all tiles immediately
void scene_tiles_clear(void);

// update all tiles by one tick
void scene_tiles_tick(void);

// draw all tiles within bounds
void scene_tiles_draw(int imin, int imax, int jmin, int jmax);


// retrieve a loaded tile
// returns NULL if not loaded
scene_tile_t * scene_tiles_get(hex_vec2i_t pos);

// load a tile, overwrite existing state if one already exists
scene_tile_t * scene_tiles_load(hex_vec2i_t hex, const scene_tile_state_t * state);

// unload immediately
void           scene_tiles_unload(hex_vec2i_t hex);


#endif
