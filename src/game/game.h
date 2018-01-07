#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <stdint.h>
#include <stdbool.h>

#include <hex/hex.h>

// unload everything
void game_clear(void);

// load saved game
void game_load(void);
// save currently loaded game
void game_save(void);

// returns 1 if it is the player's turn
bool game_isplayerturn(void);

// player actions, only have an effect if it is the player's turn
void game_player_wait(void);
void game_player_moveupright(void);
void game_player_moveup(void);
void game_player_moveupleft(void);
void game_player_movedownleft(void);
void game_player_movedown(void);
void game_player_movedownright(void);

// simulates the game by up to `max_ticks` ticks
void game_simulate(int max_ticks);

#endif
