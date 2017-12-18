
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include <hex/hex.h>
#include <test/test.h>
#include <gfx/gfx.h>
#include <game/game.h>
#include <asset/png.h>
#include <util/hash2d.h>
#include <util/vector.h>

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

typedef struct {
  gfx_Sprite sprite;
  gfx_Color color;
} scene_tile_t;
typedef struct {
  gfx_Sprite sprite;
  gfx_Color color;
} scene_mob_t;
typedef struct {
  scene_tile_t tile;
  scene_mob_t * mobs;
  int mob_num;
} scene_cell_t;

hash2d_t scene_cell_hash;


/*
static void scene_cell_init(scene_cell_t * cell) {
  memset(cell, 0, sizeof(*cell));
}
static void scene_cell_deinit(scene_cell_t * cell) {
  free(cell->mobs);
  memset(cell, 0, sizeof(*cell));
}
static void scene_cell_set_mobs(scene_cell_t * cell, const scene_mob_t * mobs, int mob_num) {
  free(cell->mobs);
  cell->mobs = malloc(mob_num*sizeof(scene_mob_t));
  memcpy(cell->mobs, mobs, mob_num*sizeof(scene_mob_t));
}


static void hash2d_scene_cell_deinit(int x, int y, void * cell, void * _) {
  scene_cell_deinit((scene_cell_t *)cell);
}
static void scene_clear_cells() {
  hash2d_each(&scene_cell_hash, hash2d_scene_cell_deinit, NULL);
  hash2d_clear(&scene_cell_hash);
}
*/


static void scene_set_cell_sprites(const game_CellState * game_cell) {
  int x = game_cell->pos.x;
  int y = game_cell->pos.y;

  scene_cell_t * cell = (scene_cell_t *)hash2d_get(&scene_cell_hash, x, y);

  if(cell == NULL) {
    cell = (scene_cell_t *)hash2d_alloc(&scene_cell_hash, x, y, sizeof(*cell));
  } else {
    free(cell->mobs);
    cell->mobs = NULL;
  }

  switch(game_cell->tile.type_id) {
    case 1:
      cell->tile.sprite = grass_tile_sprite;
      break;
    default:
      cell->tile.sprite = single_tile_sprite;
      break;
  }

  cell->tile.color.r = game_cell->tile.color.r;
  cell->tile.color.g = game_cell->tile.color.g;
  cell->tile.color.b = game_cell->tile.color.b;
  cell->tile.color.a = 0xFF;
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
void draw_cell(int i, int j) {
  hex_vec2i_t tile_pos;
  int tile_x_pix, tile_y_pix;

  get_hex_coord(&tile_pos, i, j);
  get_screen_coord(&tile_x_pix, &tile_y_pix, i, j);

  // draw tile
  const scene_cell_t * cell = hash2d_get(&scene_cell_hash, tile_pos.x, tile_pos.y);

  if(cell) {
    gfx_Color c = cell->tile.color;

    gfx_draw_sprite(&cell->tile.sprite, tile_x_pix, tile_y_pix, &c);
  }

  int dist = hex_distance(tile_pos, selected_hex);

  if(tile_pos.x == selected_hex.x && tile_pos.y == selected_hex.y) {
    gfx_Color c;
    c.r = 0xA0;
    c.g = 0xA0;
    c.b = 0xA0;
    c.a = 0xFF;

    if(tiles) {
      gfx_draw_sprite(&wall_sprite, tile_x_pix, tile_y_pix, &c);
    }
  } else if(dist >= 7) {
    gfx_Color c;
    c.r = 0xA0 - 0x08 * (dist - 7);
    c.g = 0xA0 - 0x08 * (dist - 7);
    c.b = 0xA0 - 0x08 * (dist - 7);
    c.a = 0xFF;

    if(tiles) {
      gfx_draw_sprite(&wall_sprite, tile_x_pix, tile_y_pix, &c);
    }
  }
}
void draw_cells(int imin, int imax, int jmin, int jmax) {
  for(int j = jmin ; j <= jmax ; j ++) {
    for(int i = imin ; i <= imax ; i += 2) {
      draw_cell(i, j);
    }
    for(int i = imin + 1; i <= imax ; i += 2) {
      draw_cell(i, j);
    }
  }
}

void draw() {
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

  draw_cells(imin, imax, jmin, jmax);

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

    hash2d_init(&scene_cell_hash);

    game_DrawStateHandlers handlers = {
      .cell = scene_set_cell_sprites,
    };
    game_drawstate(&handlers);

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


    hash2d_deinit(&scene_cell_hash);

    unload_sprites();
    gfx_deinit();

    SDL_DestroyWindow(window);
    window = NULL;
  }

  SDL_Quit();

  return 0;
}

