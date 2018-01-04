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


// load the state of a tile
// if the tile doesn't exist, it must be created
typedef void (* game_loadtile_handler_t)(hex_vec2i_t pos, const game_tile_state_t * state);
void game_set_loadtile_handler(game_loadtile_handler_t fn);
void game_out_loadtile(hex_vec2i_t pos, const game_tile_state_t * state);

// unload a tile completely
typedef void (* game_unloadtile_handler_t)(hex_vec2i_t pos);
void game_set_unloadtile_handler(game_unloadtile_handler_t fn);
void game_out_unloadtile(hex_vec2i_t pos);


// load the state of an object
// if the object doesn't exist, it must be created
typedef void (* game_loadobject_handler_t)(game_id_t id, const game_object_state_t * obj);
void game_set_loadobject_handler(game_loadobject_handler_t fn);
void game_out_loadobject(game_id_t id, const game_object_state_t * obj);

// unload an object completely
typedef void (* game_unloadobject_handler_t)(game_id_t id);
void game_set_unloadobject_handler(game_unloadobject_handler_t fn);
void game_out_unloadobject(game_id_t id);

// play a spawn animation for an object
typedef void (* game_objectspawn_handler_t)(game_id_t id, int type);
void game_set_objectspawn_handler(game_objectspawn_handler_t fn);
void game_out_objectspawn(game_id_t id, int type);

// play a despawn animation for an object
typedef void (* game_objectdespawn_handler_t)(game_id_t id, int type);
void game_set_objectdespawn_handler(game_objectdespawn_handler_t fn);
void game_out_objectdespawn(game_id_t id, int type);

// play a move animation for an object
// the object's position must be updated afterward
typedef void (* game_objectmove_handler_t)(game_id_t id, hex_vec2i_t pos);
void game_set_objectmove_handler(game_objectmove_handler_t fn);
void game_out_objectmove(game_id_t id, hex_vec2i_t pos);

// play a strike animation for an object
typedef void (* game_objectstrike_handler_t)(game_id_t id, hex_vec2i_t pos);
void game_set_objectstrike_handler(game_objectstrike_handler_t fn);
void game_out_objectstrike(game_id_t id, hex_vec2i_t pos);

// log a game message
typedef void (* game_message_handler_t)(const char * str);
void game_set_message_handler(game_message_handler_t fn);
void game_out_message(const char * str);


#endif
