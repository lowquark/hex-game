#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <hex/hex.h>


typedef struct {
  uint8_t r, g, b;
} game_Color;

typedef struct {
  unsigned int type_id;
} game_DrawTile;

typedef struct {
  unsigned int type_id;
} game_DrawMob;

typedef struct {
  game_Tile tile;
  game_Mob mob;
} game_DrawCell;


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
extern void game_eventhook_onSync(const game_TileDraw * tile, hex_vec2i_t pos);
// tile updated
extern void game_eventhook_onTileUpdate(const game_TileDraw * tile, hex_vec2i_t pos);
// object updated
extern void game_eventhook_onObjectUpdate(const game_ObjectDraw * obj, hex_vec2i_t pos);
// message received
extern void game_eventhook_onMessage(const char * message);
// 
void game_flushevents();


// 
extern void game_draw_tile(const game_TileDraw * tile, hex_vec2i_t pos);
//
extern void game_draw_object(const game_TileDraw * tile, hex_vec2i_t pos);
//
void game_draw();


#endif
