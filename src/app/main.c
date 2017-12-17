
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include <hex/hex.h>
#include <test/test.h>
#include <gfx/gfx.h>
#include <gs/gs.h>
#include <asset/png.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

static hex_vec2i_t selected_hex;

static gfx_SpriteSheet * tiles = NULL;
static gfx_Sprite single_tile_sprite;
static gfx_Sprite grass_tile_sprite;
static gfx_Sprite sub_tile_sprite;
static gfx_Sprite hero_sprite;
static gfx_Sprite wall_sprite;

static const int tile_spacing_x_pixels = 23;
static const int tile_spacing_y_pixels = 20;
static const int tile_stagger_y_pixels = tile_spacing_y_pixels / 2;

static const gs_color_t nespresso[5] = {
  GS_COLOR_FROM24(0x2e2e2c),
  GS_COLOR_FROM24(0x402108),
  GS_COLOR_FROM24(0x4b1e0d),
  GS_COLOR_FROM24(0xbd6416),
  GS_COLOR_FROM24(0xfdaf3e),
};
static const gs_color_t grassy[5] = {
  GS_COLOR_FROM24(0x67ab05),
  GS_COLOR_FROM24(0x80bf26),
  GS_COLOR_FROM24(0xa4e333),
  GS_COLOR_FROM24(0xc8ff66),
  GS_COLOR_FROM24(0xe9ff96),
};
static const gs_color_t dirty[3] = {
  GS_COLOR_FROM24(0x7e5f40),
  GS_COLOR_FROM24(0x725222),
  GS_COLOR_FROM24(0x6d4720),
};

void generate_map() {
  for(int i = 0 ; i < 5000 ; i ++) {
    gs_cell_t cell;
    cell.mobs = NULL;
    cell.items = NULL;
    cell.mob_num = 0;
    cell.item_num = 0;
    cell.tile.sprite_id = 0;

    hex_vec2i_t pos;

    int r = rand() % 3;

    if(r == 0) {
      int x = (rand() % 8);
      int y = (rand() % 8);

      //int sum = x + y + z;

      pos.x = x;
      pos.y = y;

      cell.tile.fg_color = dirty[rand() % 3];
      cell.tile.bg_color = dirty[rand() % 3];
    } else if(r == 1) {
      int y = (rand() % 8);
      int z = (rand() % 8);

      //int sum = x + y + z;

      pos.x = -y - z;
      pos.y = y;

      cell.tile.fg_color = nespresso[rand() % 5];
      cell.tile.bg_color = nespresso[rand() % 5];
    } else {
      int x = (rand() % 8);
      int z = (rand() % 8);

      //int sum = x + y + z;

      pos.x = x;
      pos.y = -x - z;

      cell.tile.fg_color = grassy[rand() % 5];
      cell.tile.bg_color = grassy[rand() % 5];
    }

    gs_set_cell(pos, &cell);
  }
}

void update_gamestate() {
  for(int i = 0 ; i < 500 ; i ++) {
    gs_cell_t cell;
    cell.mobs = NULL;
    cell.items = NULL;
    cell.mob_num = 0;
    cell.item_num = 0;
    cell.tile.sprite_id = 0;
    cell.tile.fg_color = nespresso[rand() % 5];
    cell.tile.bg_color = nespresso[rand() % 5];

    hex_vec2i_t pos;
    pos.x = (rand() % 9) - 4;
    pos.y = (rand() % 9) - 4;

    gs_set_cell(pos, &cell);
  }
}

void unload_sprites() {
  gfx_unload_spritesheet(tiles);
  tiles = NULL;
}
void load_sprites() {
  unload_sprites();

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

void get_screen_coord(int * tile_x_pix, int * tile_y_pix, int i, int j) {
  assert(tile_x_pix);
  assert(tile_y_pix);

  *tile_x_pix = i * tile_spacing_x_pixels + 320;
  *tile_y_pix = j * tile_spacing_y_pixels + 240;

  // stagger every other row's y
  if(abs(i % 2)) {
    *tile_y_pix += tile_stagger_y_pixels;
  }
}
void get_hex_coord(hex_vec2i_t * coord, int i, int j) {
  // hex coords
  // camera offset goes here
  coord->x = i;
  coord->y = (j*2 + abs(i % 2) - i)/2;
}
void draw_tiles(int imin, int imax, int jmin, int jmax) {
  for(int j = jmin ; j <= jmax ; j ++) {
    for(int i = imin ; i <= imax ; i ++) {
      hex_vec2i_t tile_pos;
      int tile_x_pix, tile_y_pix;

      get_hex_coord(&tile_pos, i, j);
      get_screen_coord(&tile_x_pix, &tile_y_pix, i, j);

      // retrieve the tile
      const gs_cell_t * cell = gs_get_cell(tile_pos);

      if(cell && tiles) {
        gfx_Color c;
        c.r = cell->tile.fg_color.r;
        c.g = cell->tile.fg_color.g;
        c.b = cell->tile.fg_color.b;
        c.a = 0xFF;

        //gfx_draw_sprite(&single_tile, tile_x_pix, tile_y_pix, &c);
        //gfx_draw_sprite(&sub_tile_sprite, tile_x_pix, tile_y_pix, &c);
        gfx_draw_sprite(&single_tile_sprite, tile_x_pix, tile_y_pix, &c);
      }
    }
  }
}
void draw_mobs(int imin, int imax, int jmin, int jmax) {
  for(int j = jmin ; j <= jmax ; j ++) {
    for(int i = imin ; i <= imax ; i ++) {
      hex_vec2i_t tile_pos;
      int tile_x_pix, tile_y_pix;

      get_hex_coord(&tile_pos, i, j);
      get_screen_coord(&tile_x_pix, &tile_y_pix, i, j);

      if(tile_pos.x == selected_hex.x && tile_pos.y == selected_hex.y) {
        gfx_Color c;
        c.r = 0x80;
        c.g = 0x80;
        c.b = 0x80;
        c.a = 0xFF;

        if(tiles) {
          gfx_draw_sprite(&wall_sprite, tile_x_pix, tile_y_pix, &c);
        }
      }
    }
  }
}

void draw() {
  rect2i_t whole_window;
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
  draw_mobs(imin, imax, jmin, jmax);

  gfx_flush();
}

void handle_keypress(SDL_Keycode sym)
{
  switch(sym) {
    case SDLK_e:
      selected_hex = hex_downright(selected_hex);
      break;
    case SDLK_w:
      selected_hex = hex_down(selected_hex);
      break;
    case SDLK_q:
      selected_hex = hex_downleft(selected_hex);
      break;
    case SDLK_a:
      selected_hex = hex_upleft(selected_hex);
      break;
    case SDLK_s:
      selected_hex = hex_up(selected_hex);
      break;
    case SDLK_d:
      selected_hex = hex_upright(selected_hex);
      break;
  }
}

int main(int argc, char ** argv) {
  test_all();

  SDL_SetMainReady();

  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    printf("Unable to initialize SDL: %s", SDL_GetError());
    return 1;
  }

  SDL_Window * window = SDL_CreateWindow(
      "test",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, 
      640,
      480,
      0
  );

  if(window) {
    gfx_init(window);

    load_sprites();
    gs_init();

    generate_map();

    draw();

    //update_gamestate();

    bool quit = false;
    while(!quit) {
      SDL_Event event;
      while(SDL_PollEvent(&event)) {
        if(event.type == SDL_KEYDOWN) {
          if(event.key.keysym.sym == SDLK_0) {
            quit = true;
            break;
          } else {
            handle_keypress(event.key.keysym.sym);
            draw();
          }
        } else if(event.type == SDL_WINDOWEVENT) {
          if(event.window.event == SDL_WINDOWEVENT_EXPOSED) {
            draw();
          }
        } else if(event.type == SDL_QUIT) {
          quit = true;
          break;
        }
      }
    }

    gs_deinit();

    unload_sprites();
    gfx_deinit();

    SDL_DestroyWindow(window);
    window = NULL;
  }

  SDL_Quit();

  return 0;
}

