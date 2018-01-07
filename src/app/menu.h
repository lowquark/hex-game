#ifndef APP_MENU_H
#define APP_MENU_H

#include <stdbool.h>

#include <SDL2/SDL_keycode.h>

// clear all data owned by this module
void app_menu_clear(void);

// update signal (of undefined period)
void app_menu_update(void);
// update signal (of defined period)
void app_menu_fixedupdate(void);

// key down signal
void app_menu_keydown(SDL_Keycode sym);
// user quit signal
void app_menu_quit(void);

#endif
