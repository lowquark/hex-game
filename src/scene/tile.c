
#include <assert.h>

#include <scene/tile.h>


void scene_tile_load(scene_tile_t * tile, const scene_tile_state_t * state) {
  tile->color = state->color;
  tile->onfire = state->onfire;
  tile->despawn = 0;
}
void scene_tile_unload(scene_tile_t * tile) {
}


void scene_tile_spawn(scene_tile_t * tile, int type) {
}
void scene_tile_despawn(scene_tile_t * tile, int type) {
  tile->despawn = 1;
}


void scene_tile_ignite(scene_tile_t * tile) {
  assert(tile);

  tile->onfire = 1;
}
void scene_tile_extinguish(scene_tile_t * tile) {
  assert(tile);

  tile->onfire = 0;
}
