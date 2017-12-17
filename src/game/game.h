#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <hex/hex.h>


typedef struct {
  uint8_t r, g, b;
} game_Color;

typedef struct {
  unsigned int type_id;
} game_TileState;

typedef struct {
  unsigned int type_id;
} game_MobState;

typedef struct {
  game_TileState tile;
  game_MobState mob;
} game_CellState;


void game_init();
void game_deinit();


void game_save();


void game_step_wait();
void game_step_moveupright();
void game_step_moveup();
void game_step_moveupleft();
void game_step_movedownleft();
void game_step_movedown();
void game_step_movedownright();


// logical distinction in time
extern void game_eventhook_onSync(const game_TileState * tile, hex_vec2i_t pos);
// tile updated
extern void game_eventhook_onCellUpdate(const game_TileState * tile, hex_vec2i_t pos);
// message received
extern void game_eventhook_onMessage(const char * message);
// 
void game_flushevents();


// 
extern void game_draw_tile(const game_TileState * tile, hex_vec2i_t pos);
//
extern void game_draw_object(const game_TileState * tile, hex_vec2i_t pos);
//
void game_draw();


#endif
