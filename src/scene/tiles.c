
#include <util/hash_2i.h>

#include <scene/tiles.h>

static hash_2i_t tiles;

void scene_tiles_unload(void) {
  hash_2i_clear(&tiles);
}

void scene_tiles_tick(void) {
}

void scene_tile_load(hex_vec2i_t hex, const scene_tile_state_t * state) {
  scene_tile_t * tile = hash_2i_find(&tiles, hex.x, hex.y);

  if(tile == NULL) {
    tile = hash_2i_create(&tiles, hex.x, hex.y, sizeof(*tile));
  }

  tile->color = state->color;
  tile->onfire = state->onfire;
}

void scene_tile_unload(hex_vec2i_t hex) {
  hash_2i_destroy(&tiles, hex.x, hex.y);
}

void scene_tile_spawn(hex_vec2i_t hex, int type, const scene_tile_state_t * state) {
  // load immediately
  scene_tile_load(hex, state);

  // TODO: set animation
}
void scene_tile_despawn(hex_vec2i_t hex, int type) {
  // not unloaded until animation finishes

  // TEMPORARY: right now!
  scene_tile_unload(hex);
}

void scene_tile_ignite(hex_vec2i_t hex) {
  scene_tile_t * tile = hash_2i_find(&tiles, hex.x, hex.y);
  if(tile) {
    tile->onfire = 1;
  }
}
void scene_tile_extinguish(hex_vec2i_t hex) {
  scene_tile_t * tile = hash_2i_find(&tiles, hex.x, hex.y);
  if(tile) {
    tile->onfire = 0;
  }
}

const scene_tile_t * scene_tile_find(hex_vec2i_t hex) {
  return hash_2i_find(&tiles, hex.x, hex.y);
}

