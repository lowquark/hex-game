
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
#include <scene/sprites.h>


#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>


static hex_vec2i_t selected_hex;

void draw() {
  scene_draw();

  gfx_flush();
}

void on_loadtile(hex_vec2i_t pos, const game_tile_state_t * state) {
  scene_tile_state_t tst = SCENE_TILE_STATE_NULL;

  tst.color.r = state->color.r;
  tst.color.g = state->color.g;
  tst.color.b = state->color.b;
  tst.color.a = 0xFF;

  scene_tiles_load(pos, &tst);
}
void on_unloadtile(hex_vec2i_t pos) {
  scene_tiles_unload(pos);
}

void on_loadobject(game_id_t id, const game_object_state_t * state) {
  scene_object_state_t ost = SCENE_OBJECT_STATE_NULL;

  ost.pos = state->pos;
  ost.color.r = state->color.r;
  ost.color.g = state->color.g;
  ost.color.b = state->color.b;
  ost.color.a = 0xFF;

  scene_objects_load(id, &ost);
}
void on_unloadobject(game_id_t id) {
  scene_objects_unload(id);
}

void on_objectspawn(game_id_t id, int type) {
  scene_object_t * obj = scene_objects_get(id);

  if(obj) {
    scene_object_spawn(obj, type);
  }
}
void on_objectdespawn(game_id_t id, int type) {
  scene_object_t * obj = scene_objects_get(id);

  if(obj) {
    scene_object_despawn(obj, type);
  }
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
  SDL_SetMainReady();

  test_all();

  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
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
    scene_load_assets();

    game_set_loadtile_handler(on_loadtile);
    game_set_unloadtile_handler(on_unloadtile);

    game_set_loadobject_handler(on_loadobject);
    game_set_unloadobject_handler(on_unloadobject);

    game_set_objectspawn_handler(on_objectspawn);
    game_set_objectdespawn_handler(on_objectdespawn);

    game_load();

    draw();

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
      SDL_Delay(0);
    }

    game_clear();

    scene_clear();
    scene_unload_assets();
    gfx_deinit();

    SDL_DestroyWindow(window);
    window = NULL;
  }

  SDL_Quit();

  return 0;
}

