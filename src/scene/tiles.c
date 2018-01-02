
#include <assert.h>

#include <util/hash_2i.h>

#include <scene/tiles.h>
#include <scene/view.h>

static hash_2i_t tile_hash;

// get or create tile
// always returns a non-null tile
static scene_tile_t * goc_tile(hex_vec2i_t hex) {
  scene_tile_t * tile = hash_2i_get(&tile_hash, hex.x, hex.y);

  if(tile == NULL) {
    tile = calloc(sizeof(*tile), 1);

    hash_2i_set(&tile_hash, hex.x, hex.y, tile);
  }

  assert(tile);

  return tile;
}
static void destroy_tile(hex_vec2i_t hex, scene_tile_t * tile) {
  // deinit
  scene_tile_clear(tile);
  // free
  free(tile);
  // forget
  hash_2i_set(&tile_hash, hex.x, hex.y, NULL);
}

void scene_tiles_clear(void) {
  hash_2i_each(&tile_hash, free);
  hash_2i_clear(&tile_hash);
}

void scene_tiles_tick(void) {
  // erase tiles whos despawn flag is set
}

static void get_hex_coord(hex_vec2i_t * coord, int i, int j) {
  // hex coords
  // camera offset goes here
  coord->x = i;
  coord->y = (j*2 + abs(i % 2) - i)/2;
}

static void draw_tile(int i, int j) {
  hex_vec2i_t tile_pos;
  int tile_x_pix, tile_y_pix;
  gfx_Color c;

  get_hex_coord(&tile_pos, i, j);
  scene_view_tilecenter(&tile_x_pix, &tile_y_pix, tile_pos);

  const scene_tile_t * tile = scene_tiles_get(tile_pos);

  extern gfx_Sprite single_tile_sprite;

  if(tile) {
    c = tile->color;
    gfx_draw_sprite(&single_tile_sprite, tile_x_pix, tile_y_pix, &c);
  } else {
    c.r = 0x44;
    c.g = 0x44;
    c.b = 0x44;
    c.a = 0xFF;
    gfx_draw_sprite(&single_tile_sprite, tile_x_pix, tile_y_pix, &c);
  }
}

// draw all tiles
void scene_tiles_draw(int imin, int imax, int jmin, int jmax) {
  for(int j = jmin ; j <= jmax ; j ++) {
    for(int i = imin ; i <= imax ; i += 2) {
      draw_tile(i, j);
    }
    for(int i = imin + 1; i <= imax ; i += 2) {
      draw_tile(i, j);
    }
  }
}

scene_tile_t * scene_tiles_get(hex_vec2i_t hex) {
  return hash_2i_get(&tile_hash, hex.x, hex.y);
}

scene_tile_t * scene_tiles_load(hex_vec2i_t hex, const scene_tile_state_t * state) {
  scene_tile_t * tile = goc_tile(hex);

  assert(tile);

  scene_tile_setstate(tile, state);

  return tile;
}

void scene_tiles_unload(hex_vec2i_t hex) {
  scene_tile_t * tile = hash_2i_get(&tile_hash, hex.x, hex.y);

  if(tile) {
    destroy_tile(hex, tile);
  }
}

