
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

#include <eventlog/eventlog.h>

#include <app/menu.h>
#include <app/game.h>


#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

typedef enum {
  MENU,
  GAME,
} state_t;

state_t state;

/*
static void menu_enter() {
  state = MENU;
}
*/

// start game by loading
static void game_enter(const char * save_name) {
  state = GAME;
  app_game_load(save_name);
}

// dispatch events
static void handle_update(void) {
  switch(state) {
    case MENU:
      app_menu_update();
      return;
    case GAME:
      app_game_update();
      return;
    default:
      return;
  }
}
static void handle_fixedupdate(void) {
  switch(state) {
    case MENU:
      app_menu_fixedupdate();
      return;
    case GAME:
      app_game_fixedupdate();
      return;
    default:
      return;
  }
}
static void handle_keydown(SDL_Keycode sym) {
  switch(state) {
    case MENU:
      app_menu_keydown(sym);
      return;
    case GAME:
      app_game_keydown(sym);
      return;
    default:
      return;
  }
}
static void handle_quit(void) {
  switch(state) {
    case MENU:
      app_menu_quit();
      return;
    case GAME:
      app_game_quit();
      return;
    default:
      return;
  }
}


void handle_sdl_events() {
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    if(event.type == SDL_QUIT) {
      // deliver quit signal
      handle_quit();
    } else if(event.type == SDL_KEYDOWN) {
      if(event.key.keysym.sym == SDLK_0) {
        // also deliver quit signal
        handle_quit();
      } else {
        // deliver keydown signal
        handle_keydown(event.key.keysym.sym);
      }
    }
  }
}

void main_loop() {
  // enter game state right away
  game_enter("gg");

  Uint32 last_update_ticks = SDL_GetTicks();

  app_game_quitsignal_t q;
  while(!app_game_quitsignal(&q)) {
    // deliver update signal
    handle_update();

    // subtract current ticks from last_update time/counter
    Uint32 ticks = SDL_GetTicks();
    if(ticks - last_update_ticks >= 16) {
      // more than 16ms have elapsed, add 16ms to last_update time/counter
      last_update_ticks += 16;

      // deliver fixedupdate signal
      handle_fixedupdate();
    }

    handle_sdl_events();

    // yield to os
    SDL_Delay(0);
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

    main_loop();

    scene_unload_assets();
    gfx_deinit();

    SDL_DestroyWindow(window);
    window = NULL;
  }

  SDL_Quit();

  return 0;
}

