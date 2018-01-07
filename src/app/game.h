#ifndef APP_GAME_H
#define APP_GAME_H

#include <stdbool.h>

#include <SDL2/SDL_keycode.h>

// clear all data owned by this module
void app_game_clear(void);

// start game by loading
void app_game_load(const char * save_name);

// update signal (of undefined period)
void app_game_update(void);
// update signal (of defined period)
void app_game_fixedupdate(void/* delta time in ms? */);

// key down signal
void app_game_keydown(SDL_Keycode sym);

// user quit signal
void app_game_quit(void);


typedef enum {
  APP_GAME_QUIT,
  APP_GAME_QUITTOMENU,
} app_game_quitsignal_t;

bool app_game_quitsignal(app_game_quitsignal_t * sig);


#endif
