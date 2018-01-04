#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <stdint.h>

#include <hex/hex.h>

#include <game/handlers.h>


void game_clear(void);

void game_load(void);
void game_save(void);

void game_step_wait(void);
void game_step_moveupright(void);
void game_step_moveup(void);
void game_step_moveupleft(void);
void game_step_movedownleft(void);
void game_step_movedown(void);
void game_step_movedownright(void);


#endif
