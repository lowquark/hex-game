#ifndef SCENE_TILES_H
#define SCENE_TILES_H

#include <hex/hex.h>
#include <gfx/gfx.h>

#include <scene/id.h>
#include <scene/sprites.h>


///////////
// types //
///////////

typedef struct {
  gfx_Color color;
  unsigned int onfire : 1;
} scene_tile_state_t;

#define SCENE_TILE_STATE_NULL { { 0 } }

typedef struct {
  gfx_Color color;
  unsigned int onfire : 1;
} scene_tile_t;

#define SCENE_TILE_NULL { { 0 } }


////////////////////////
// high-level control //
////////////////////////

// unload all tiles
void scene_tiles_unload(void);

// update all tiles by one tick
void scene_tiles_tick(void);


////////////////////////
// set state directly //
////////////////////////

// tile state is overwritten if already loaded
void scene_tile_load(hex_vec2i_t hex, const scene_tile_state_t * state);
// unload a tile
void scene_tile_unload(hex_vec2i_t hex);


/////////////////////////
// set state via event //
/////////////////////////

// reveal tiles via animation
// tile state is overwritten if already loaded
void scene_tile_spawn(hex_vec2i_t hex, int type, const scene_tile_state_t * state);
// hide tiles via animation
void scene_tile_despawn(hex_vec2i_t hex, int type);

// show tile exploding into flames
void scene_tile_ignite(hex_vec2i_t hex);
// show tile smoking and cooling off
void scene_tile_extinguish(hex_vec2i_t hex);


////////////////////////
// query loaded tiles //
////////////////////////

// retrieve a loaded tile
const scene_tile_t * scene_tile_find(hex_vec2i_t hex);


#endif
