
#include <assert.h>

#include <hex/hex.h>
#include <util/hash_2i.h>
#include <asset/png.h>
#include <gfx/gfx.h>
#include <scene/scene.h>

extern hash_2i_t scene_tile_hash;

//static hex_vec2i_t selected_hex;

static gfx_SpriteSheet * tiles = NULL;
static gfx_Sprite single_tile_sprite;
static gfx_Sprite grass_tile_sprite;
static gfx_Sprite sub_tile_sprite;
static gfx_Sprite hero_sprite;
static gfx_Sprite wall_sprite;

static const int tile_spacing_x_pixels = 23;
static const int tile_spacing_y_pixels = 20;
static const int tile_stagger_y_pixels = tile_spacing_y_pixels / 2;


void scene_load_sprites() {
  scene_unload_sprites();

  SDL_Surface * tiles_surface = asset_png_load("test.png");

  if(tiles_surface) {
    tiles = gfx_load_spritesheet(tiles_surface);

    single_tile_sprite = gfx_sprite(tiles,  0,  0, 28, 20, 14, 10);
    grass_tile_sprite  = gfx_sprite(tiles, 28,  0, 28, 20, 14, 10);
    sub_tile_sprite    = gfx_sprite(tiles,  8,  8, 15, 15,  8,  8);
    hero_sprite        = gfx_sprite(tiles,  0, 20, 20, 20, 10, 15);
    wall_sprite        = gfx_sprite(tiles, 29, 26, 28, 25, 14, 15);

    SDL_FreeSurface(tiles_surface);
    tiles_surface = NULL;
  }
}
void scene_unload_sprites(void) {
  gfx_unload_spritesheet(tiles);
  tiles = NULL;
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

scene_Id scene_objectat(int pixel_x, int pixel_y) {
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

  scene_TileSprite * spr = hash_2i_find(&scene_tile_hash, tile_pos.x, tile_pos.y);

  if(spr) {
    c = spr->color;
    gfx_draw_sprite(&single_tile_sprite, tile_x_pix, tile_y_pix, &c);
  } else {
    c.r = 0x44;
    c.g = 0x44;
    c.b = 0x44;
    c.a = 0xFF;
    gfx_draw_sprite(&single_tile_sprite, tile_x_pix, tile_y_pix, &c);
  }
}

void draw_tiles(int imin, int imax, int jmin, int jmax) {
  for(int j = jmin ; j <= jmax ; j ++) {
    for(int i = imin ; i <= imax ; i += 2) {
      draw_tile(i, j);
    }
    for(int i = imin + 1; i <= imax ; i += 2) {
      draw_tile(i, j);
    }
  }
}

void scene_tick(void) {
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
}

