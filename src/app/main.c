
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <hex/hex.h>
#include <test/test.h>
#include <gfx/gfx.h>
#include <gs/gs.h>
#include <asset/png.h>

#include <test/test.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

static gfx_Sprite * single_tile = NULL;

static const gs_color_t nespresso[5] = {
  GS_COLOR_FROM24(0x2e2e2c),
  GS_COLOR_FROM24(0x402108),
  GS_COLOR_FROM24(0x4b1e0d),
  GS_COLOR_FROM24(0xbd6416),
  GS_COLOR_FROM24(0xfdaf3e),
};

void generate_map() {
  for(int i = 0 ; i < 5000 ; i ++) {
    gs_cell_t cell;
    cell.mobs = NULL;
    cell.items = NULL;
    cell.mob_num = 0;
    cell.item_num = 0;
    cell.tile.sprite_id = 0;
    cell.tile.fg_color = nespresso[rand() % 5];
    cell.tile.bg_color = nespresso[rand() % 5];

    hex_vec2i_t pos;

    int r = rand() % 3;

    if(r == 0) {
      int x = (rand() % 8);
      int y = (rand() % 8);

      //int sum = x + y + z;

      pos.x = x;
      pos.y = y;
    } else if(r == 1) {
      int y = (rand() % 8);
      int z = (rand() % 8);

      //int sum = x + y + z;

      pos.x = -y - z;
      pos.y = y;
    } else {
      int x = (rand() % 8);
      int z = (rand() % 8);

      //int sum = x + y + z;

      pos.x = x;
      pos.y = -x - z;
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
  gfx_unload_sprite(single_tile);
  single_tile = NULL;
}
void load_sprites() {
  unload_sprites();

  gfx_SpriteDef single_tile_def = {
    .offset_x = 15,
    .offset_y = 15,
  };

  single_tile_def.surface = asset_png_load("test.png");

  single_tile = gfx_load_sprite(&single_tile_def);

  SDL_FreeSurface(single_tile_def.surface);
  single_tile_def.surface = NULL;
}


void draw_tiles(const rect2i_t * screen_rect_pixels) {
  int rect_center_x = screen_rect_pixels->w/2 + screen_rect_pixels->x;
  int rect_center_y = screen_rect_pixels->h/2 + screen_rect_pixels->y;

  static const int tile_spacing_x_pixels = 23;
  static const int tile_spacing_y_pixels = 20;
  static const int tile_stagger_y_pixels = tile_spacing_y_pixels / 2;

  const int imin = -screen_rect_pixels->w/2 / tile_spacing_x_pixels - 1;
  const int imax =  screen_rect_pixels->w/2 / tile_spacing_x_pixels + 1;
  const int jmin = -screen_rect_pixels->h/2 / tile_spacing_y_pixels;
  const int jmax =  screen_rect_pixels->h/2 / tile_spacing_y_pixels;

  for(int j = jmin ; j <= jmax ; j ++) {
    for(int i = imin ; i <= imax ; i ++) {
      int tile_x_pix = i * tile_spacing_x_pixels + rect_center_x;
      int tile_y_pix = j * tile_spacing_y_pixels + rect_center_y;

      // stagger every other row's y
      if(abs(i % 2)) {
        tile_y_pix += tile_stagger_y_pixels;
      }

      // hex coords
      // camera offset goes here
      hex_vec2i_t tile_pos = {
        .x = i,
        .y = (j*2 + abs(i % 2) - i)/2,
      };

      // retrieve the tile
      const gs_cell_t * cell = gs_get_cell(tile_pos);

      if(cell) {
        // draw it
        gfx_Color c;
        c.r = cell->tile.fg_color.r;
        c.g = cell->tile.fg_color.g;
        c.b = cell->tile.fg_color.b;
        if(tile_pos.x == 0) {
          c.r = 0xFF;
        }
        if(tile_pos.y == 0) {
          c.g = 0xFF;
        }
        if(tile_pos.y + tile_pos.x == 0) {
          c.b = 0xFF;
        }
        //c.r = (uint8_t)(tile_pos.x*20);
        //c.g = (uint8_t)(tile_pos.y*20);
        //c.b = 0x00;
        c.a = 0xFF;

        if(single_tile) {
          gfx_draw_sprite(single_tile, tile_x_pix + 30, tile_y_pix, &c);
        }
      }
    }
  }
}

void draw() {
  gfx_Color bg_color = { 0x11, 0x11, 0x11, 0xFF };
  gfx_clear(&bg_color);

  rect2i_t whole_window;
  whole_window.x = 0;
  whole_window.y = 0;
  whole_window.w = 640;
  whole_window.h = 480;
  draw_tiles(&whole_window);

  gfx_flush();
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

    //test_hex();

    gs_deinit();

    unload_sprites();
    gfx_deinit();

    SDL_DestroyWindow(window);
    window = NULL;
  }

  SDL_Quit();

  return 0;
}

