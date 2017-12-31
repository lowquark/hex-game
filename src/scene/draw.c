
#include <assert.h>

#include <hex/hex.h>
#include <util/hash_2i.h>
#include <util/hash_ul.h>
#include <gfx/gfx.h>

#include <scene/scene.h>
#include <scene/sprites.h>

static const int tile_spacing_x_pixels = 23;
static const int tile_spacing_y_pixels = 20;
static const int tile_stagger_y_pixels = tile_spacing_y_pixels / 2;



//static hex_vec2i_t selected_hex;
void scene_load_assets() {
  scene_unload_assets();

  scene_sprites_load();
}
void scene_unload_assets(void) {
  scene_sprites_unload();
}


static void get_screen_coord(int * tile_x_pix, int * tile_y_pix, int i, int j) {
  assert(tile_x_pix);
  assert(tile_y_pix);

  *tile_x_pix = i * tile_spacing_x_pixels + 320;
  *tile_y_pix = j * tile_spacing_y_pixels + 240;

  // stagger every other row's y
  if(abs(i % 2)) {
    *tile_y_pix += tile_stagger_y_pixels;
  }
}
static void get_hex_coord(hex_vec2i_t * coord, int i, int j) {
  // hex coords
  // camera offset goes here
  coord->x = i;
  coord->y = (j*2 + abs(i % 2) - i)/2;
}

scene_id_t scene_objectat(int pixel_x, int pixel_y) {
  return 0;
}
hex_vec2i_t scene_hexat(int pixel_x, int pixel_y) {
  hex_vec2i_t h;
  h.x = 0;
  h.y = 0;
  return h;
}

static void draw_tile(int i, int j) {
  hex_vec2i_t tile_pos;
  int tile_x_pix, tile_y_pix;
  gfx_Color c;

  get_hex_coord(&tile_pos, i, j);
  get_screen_coord(&tile_x_pix, &tile_y_pix, i, j);

  const scene_tile_t * tile = scene_tile_find(tile_pos);

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

static void draw_tiles(int imin, int imax, int jmin, int jmax) {
  for(int j = jmin ; j <= jmax ; j ++) {
    for(int i = imin ; i <= imax ; i += 2) {
      draw_tile(i, j);
    }
    for(int i = imin + 1; i <= imax ; i += 2) {
      draw_tile(i, j);
    }
  }
}

static void draw_objects() {
  /*
  scene_sprites_draw();

  scene_Sprite ** s = scene_sortsprites();

  while(*s) {
    scene_Sprite * sprite = *s;

    gfx_Color c;
    c.r = 0xFF;
    c.g = 0xFF;
    c.b = 0xFF;
    c.a = 0xFF;
    gfx_draw_sprite(&hero_sprite, sprite->x, sprite->y, &c);

    s ++;
  }
  */
}

void scene_tick(void) {
  scene_tiles_tick();
}
void scene_draw(void) {
  SDL_Rect whole_window;
  whole_window.x = 0;
  whole_window.y = 0;
  whole_window.w = 640;
  whole_window.h = 480;

  const int imin = -whole_window.w/2 / tile_spacing_x_pixels - 1;
  const int imax =  whole_window.w/2 / tile_spacing_x_pixels + 1;
  const int jmin = -whole_window.h/2 / tile_spacing_y_pixels;
  const int jmax =  whole_window.h/2 / tile_spacing_y_pixels;

  gfx_Color bg_color = { 0x11, 0x11, 0x11, 0xFF };
  gfx_clear(&bg_color);

  draw_tiles(imin, imax, jmin, jmax);
  draw_objects();
}

