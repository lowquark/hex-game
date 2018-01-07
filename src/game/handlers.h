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


// unload all tiles
typedef void (* game_cleartiles_handler_t)(void);

// unload all objects
typedef void (* game_clearobjects_handler_t)(void);


// load the state of a tile
// if the tile doesn't exist, it must be created
typedef void (* game_loadtile_handler_t)(hex_vec2i_t pos, const game_tile_state_t * state);

// unload a tile completely
typedef void (* game_unloadtile_handler_t)(hex_vec2i_t pos);


// load the state of an object
// if the object doesn't exist, it must be created
typedef void (* game_loadobject_handler_t)(game_id_t id, const game_object_state_t * obj);

// unload an object completely
typedef void (* game_unloadobject_handler_t)(game_id_t id);

// play a spawn animation for an object
typedef void (* game_objectspawn_handler_t)(game_id_t id, int type);

// play a despawn animation for an object
typedef void (* game_objectdespawn_handler_t)(game_id_t id, int type);

// play a move animation for an object
// the object's position must be updated afterward
typedef void (* game_objectmove_handler_t)(game_id_t id, hex_vec2i_t pos, int type);

// play a strike animation for an object
typedef void (* game_objectstrike_handler_t)(game_id_t id, hex_vec2i_t pos, int type);

// log a game message
typedef void (* game_message_handler_t)(const char * str);



typedef struct {
  game_cleartiles_handler_t    cleartiles;
  game_clearobjects_handler_t  clearobjects;

  game_loadtile_handler_t      loadtile;
  game_unloadtile_handler_t    unloadtile;

  game_loadobject_handler_t    loadobject;
  game_unloadobject_handler_t  unloadobject;
  game_objectmove_handler_t    objectmove;
  game_objectstrike_handler_t  objectstrike;
  game_objectdespawn_handler_t objectdespawn;
  game_objectspawn_handler_t   objectspawn;

  game_message_handler_t       message;
} game_handlers_t;

void game_set_handlers(const game_handlers_t * handlers);


void game_out_cleartiles(void);
void game_out_clearobjects(void);
void game_out_loadtile(hex_vec2i_t pos, const game_tile_state_t * state);
void game_out_unloadtile(hex_vec2i_t pos);
void game_out_loadobject(game_id_t id, const game_object_state_t * obj);
void game_out_unloadobject(game_id_t id);
void game_out_objectspawn(game_id_t id, int type);
void game_out_objectdespawn(game_id_t id, int type);
void game_out_objectmove(game_id_t id, hex_vec2i_t pos, int type);
void game_out_objectstrike(game_id_t id, hex_vec2i_t pos, int type);
void game_out_message(const char * str);

#endif
