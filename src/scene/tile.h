#ifndef SCENE_TILE_H
#define SCENE_TILE_H

#include <hex/hex.h>

#include <gfx/gfx.h>


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
  int despawn;
} scene_tile_t;

#define SCENE_TILE_NULL { { 0 } }


////////////////////////
// high-level control //
////////////////////////

// update by one tick
void scene_tile_tick(scene_tile_t * tile);
// draw this tile
void scene_tile_draw(scene_tile_t * tile);
// query whether tile is animating
int scene_tile_isanimating(scene_tile_t * tile);


////////////////////////
// set state directly //
////////////////////////

// tile state is overwritten if already loaded
void scene_tile_setstate(scene_tile_t * tile, const scene_tile_state_t * state);
// unload a tile
void scene_tile_clear(scene_tile_t * tile);


/////////////////////////
// set state via event //
/////////////////////////

// reveal tiles via animation
// tile state is overwritten if already loaded
void scene_tile_spawn(scene_tile_t * tile, int type);
// hide tiles via animation
void scene_tile_despawn(scene_tile_t * tile, int type);

// show tile exploding into flames
void scene_tile_ignite(scene_tile_t * tile);
// show tile smoking and cooling off
void scene_tile_extinguish(scene_tile_t * tile);


#endif
