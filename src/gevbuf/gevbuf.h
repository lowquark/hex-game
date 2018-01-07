#ifndef GEVBUF_H
#define GEVBUF_H

#include <hex/hex.h>
#include <game/handlers.h>
#include <gevbuf/event.h>

// clear all events in the event buffer
void gevbuf_clear(void);

// tries to handle the event at the front of the queue
// returns 1 if the event was handled, and 0 if there were no events in the queue
int gevbuf_step(void);

// output events
// registers handlers to be called by gevbuf_next()
void gevbuf_set_handlers(const game_handlers_t * handlers);

// input events
extern game_handlers_t gevbuf_game_handlers;

#endif
