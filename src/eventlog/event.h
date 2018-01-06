#ifndef EVENTLOG_EVENT_H
#define EVENTLOG_EVENT_H

#include <hex/hex.h>
#include <game/handlers.h>

typedef enum {
  EVENTLOG_CLEARTILES,
  EVENTLOG_CLEAROBJECTS,

  EVENTLOG_LOADTILE,
  EVENTLOG_UNLOADTILE,

  EVENTLOG_LOADOBJECT,
  EVENTLOG_UNLOADOBJECT,

  EVENTLOG_OBJECTSPAWN,
  EVENTLOG_OBJECTDESPAWN,
  EVENTLOG_OBJECTMOVE,
  EVENTLOG_OBJECTSTRIKE,

  EVENTLOG_MESSAGE,
} eventlog_event_type_t;

typedef struct {
  // event type
  eventlog_event_type_t type_;
  // position of tile
  hex_vec2i_t pos;
  // new state of tile
  game_tile_state_t state;
} eventlog_loadtile_event_t;

typedef struct {
  // event type
  eventlog_event_type_t type_;
  // position of tile
  hex_vec2i_t pos;
} eventlog_unloadtile_event_t;

typedef struct {
  // event type
  eventlog_event_type_t type_;
  // id of object
  game_id_t id;
  // new state of object
  game_object_state_t state;
} eventlog_loadobject_event_t;

typedef struct {
  // event type
  eventlog_event_type_t type_;
  // id of object
  game_id_t id;
} eventlog_unloadobject_event_t;

typedef struct {
  // event type
  eventlog_event_type_t type_;
  // id of object
  game_id_t id;
  // spawn type
  int type;
} eventlog_objectspawn_event_t;

typedef struct {
  // event type
  eventlog_event_type_t type_;
  // id of object
  game_id_t id;
  // despawn type
  int type;
} eventlog_objectdespawn_event_t;

typedef struct {
  // event type
  eventlog_event_type_t type_;
  // id of object
  game_id_t id;
  // position of object post-move
  hex_vec2i_t pos;
  // type of strike
  int type;
} eventlog_objectmove_event_t;

typedef struct {
  // event type
  eventlog_event_type_t type_;
  // id of object
  game_id_t id;
  // strike target position
  hex_vec2i_t pos;
  // type of strike
  int type;
} eventlog_objectstrike_event_t;

typedef struct {
  // event type
  eventlog_event_type_t type_;
  // pointer to message string
  char * str;
} eventlog_message_event_t;

typedef union {
  eventlog_event_type_t type;

  eventlog_loadtile_event_t      loadtile;
  eventlog_unloadtile_event_t    unloadtile;

  eventlog_loadobject_event_t    loadobject;
  eventlog_unloadobject_event_t  unloadobject;

  eventlog_objectspawn_event_t   objectspawn;
  eventlog_objectdespawn_event_t objectdespawn;

  eventlog_objectmove_event_t    objectmove;
  eventlog_objectstrike_event_t  objectstrike;

  eventlog_message_event_t       message;
} eventlog_event_t;

#endif
