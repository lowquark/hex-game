#ifndef EVENTLOG_H
#define EVENTLOG_H

#include <hex/hex.h>
#include <game/handlers.h>
#include <eventlog/event.h>

// clear all events in the event log
void eventlog_clear(void);

// tries to pop an event from the queue and stores it in `*event_out`
// returns 1 if an event was copied, 0 otherwise
int eventlog_poll(eventlog_event_t * event_out);

// clears the event, frees any of its owned data
void eventlog_event_clear(eventlog_event_t * event);


// compatible with game out signals

void eventlog_on_loadtile      (hex_vec2i_t pos, const game_tile_state_t * state);
void eventlog_on_unloadtile    (hex_vec2i_t pos);
void eventlog_on_cleartiles    (void);

void eventlog_on_loadobject    (game_id_t id, const game_object_state_t * obj);
void eventlog_on_unloadobject  (game_id_t id);
void eventlog_on_clearobjects  (void);

void eventlog_on_objectspawn   (game_id_t id, int type);
void eventlog_on_objectdespawn (game_id_t id, int type);

void eventlog_on_objectmove    (game_id_t id, hex_vec2i_t pos, int type);
void eventlog_on_objectstrike  (game_id_t id, hex_vec2i_t pos, int type);

void eventlog_on_message       (const char * str);


#endif
