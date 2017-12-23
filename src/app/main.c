
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
#include <scene/scene.h>


#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

static hex_vec2i_t selected_hex;

void draw() {
  scene_draw();

  gfx_flush();
}

void draw_state_tile(hex_vec2i_t pos, const game_TileState * state) {
  scene_TileSprite spr;
  spr.id = state->sprite_id;
  spr.color.r = state->color.r;
  spr.color.g = state->color.g;
  spr.color.b = state->color.b;
  spr.color.a = 0xFF;
  scene_settilesprite(pos, &spr);

  //printf("<%d,%d>\n", pos.x, pos.y);
}

void handle_keypress(SDL_Keycode sym) {
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
    scene_load_sprites();

    scene_cleartiles();
    game_DrawStateHandlers handlers = {
      .tile = draw_state_tile,
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

    scene_unload_sprites();
    gfx_deinit();

    SDL_DestroyWindow(window);
    window = NULL;
  }

  SDL_Quit();

  return 0;
}

