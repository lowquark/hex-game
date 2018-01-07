#ifndef GEVBUF_EVENT_H
#define GEVBUF_EVENT_H

#include <hex/hex.h>
#include <game/handlers.h>

typedef enum {
  GEVBUF_CLEARTILES,
  GEVBUF_CLEAROBJECTS,

  GEVBUF_LOADTILE,
  GEVBUF_UNLOADTILE,

  GEVBUF_LOADOBJECT,
  GEVBUF_UNLOADOBJECT,

  GEVBUF_OBJECTSPAWN,
  GEVBUF_OBJECTDESPAWN,
  GEVBUF_OBJECTMOVE,
  GEVBUF_OBJECTSTRIKE,

  GEVBUF_MESSAGE,
} gevbuf_event_type_t;

typedef struct {
  // event type
  gevbuf_event_type_t type_;
  // position of tile
  hex_vec2i_t pos;
  // new state of tile
  game_tile_state_t state;
} gevbuf_loadtile_event_t;

typedef struct {
  // event type
  gevbuf_event_type_t type_;
  // position of tile
  hex_vec2i_t pos;
} gevbuf_unloadtile_event_t;

typedef struct {
  // event type
  gevbuf_event_type_t type_;
  // id of object
  game_id_t id;
  // new state of object
  game_object_state_t state;
} gevbuf_loadobject_event_t;

typedef struct {
  // event type
  gevbuf_event_type_t type_;
  // id of object
  game_id_t id;
} gevbuf_unloadobject_event_t;

typedef struct {
  // event type
  gevbuf_event_type_t type_;
  // id of object
  game_id_t id;
  // spawn type
  int type;
} gevbuf_objectspawn_event_t;

typedef struct {
  // event type
  gevbuf_event_type_t type_;
  // id of object
  game_id_t id;
  // despawn type
  int type;
} gevbuf_objectdespawn_event_t;

typedef struct {
  // event type
  gevbuf_event_type_t type_;
  // id of object
  game_id_t id;
  // position of object post-move
  hex_vec2i_t pos;
  // type of strike
  int type;
} gevbuf_objectmove_event_t;

typedef struct {
  // event type
  gevbuf_event_type_t type_;
  // id of object
  game_id_t id;
  // strike target position
  hex_vec2i_t pos;
  // type of strike
  int type;
} gevbuf_objectstrike_event_t;

typedef struct {
  // event type
  gevbuf_event_type_t type_;
  // pointer to message string
  char * str;
} gevbuf_message_event_t;

typedef union {
  gevbuf_event_type_t type;

  gevbuf_loadtile_event_t      loadtile;
  gevbuf_unloadtile_event_t    unloadtile;

  gevbuf_loadobject_event_t    loadobject;
  gevbuf_unloadobject_event_t  unloadobject;

  gevbuf_objectspawn_event_t   objectspawn;
  gevbuf_objectdespawn_event_t objectdespawn;

  gevbuf_objectmove_event_t    objectmove;
  gevbuf_objectstrike_event_t  objectstrike;

  gevbuf_message_event_t       message;
} gevbuf_event_t;

#endif
