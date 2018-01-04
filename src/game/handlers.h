#ifndef GAME_HANDLERS_H
#define GAME_HANDLERS_H

#include <stdint.h>

#include <hex/hex.h>

#include <game/id.h>
#include <game/color.h>


typedef struct {
  unsigned int sprite_id;
  game_color_t color;
} game_tile_state_t;

typedef struct {
  hex_vec2i_t pos;
  unsigned int sprite_id;
  game_color_t color;
} game_object_state_t;


typedef void (* game_clear_handler_t)(void);
void game_set_clear_handler(game_clear_handler_t fn);
void game_out_clear(void);


typedef void (* game_tilestate_handler_t)(hex_vec2i_t pos, const game_tile_state_t * state);
void game_set_tilestate_handler(game_tilestate_handler_t fn);
void game_out_tilestate(hex_vec2i_t pos, const game_tile_state_t * state);


typedef void (* game_objectstate_handler_t)(game_id_t id, const game_object_state_t * obj);
void game_set_objectstate_handler(game_objectstate_handler_t fn);
void game_out_objectstate(game_id_t id, const game_object_state_t * obj);

typedef void (* game_objectmove_handler_t)(game_id_t id, hex_vec2i_t pos);
void game_set_objectmove_handler(game_objectmove_handler_t fn);
void game_out_objectmove(game_id_t id, hex_vec2i_t pos);

typedef void (* game_objectstrike_handler_t)(game_id_t id, hex_vec2i_t pos);
void game_set_objectstrike_handler(game_objectstrike_handler_t fn);
void game_out_objectstrike(game_id_t id, hex_vec2i_t pos);

typedef void (* game_objecthide_handler_t)(game_id_t id);
void game_set_objecthide_handler(game_objecthide_handler_t fn);
void game_out_objecthide(game_id_t id);

typedef void (* game_objectshow_handler_t)(game_id_t id);
void game_set_objectshow_handler(game_objectshow_handler_t fn);
void game_out_objectshow(game_id_t id);


typedef void (* game_message_handler_t)(const char * str);
void game_set_message_handler(game_message_handler_t fn);
void game_out_message(const char * str);


#endif
