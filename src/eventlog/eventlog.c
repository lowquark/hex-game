
#include <string.h>
#include <assert.h>

#include <eventlog/eventlog.h>
#include <util/list.h>

#define ZERO(x) memset(&x, 0, sizeof(x))


static list_t event_list;


static void eventlog_event_free_void(void * ev) {
  eventlog_event_t * event = ev;
  eventlog_event_clear(event);
  free(event);
}
void eventlog_clear(void) {
  // free all
  list_each(&event_list, eventlog_event_free_void);
  // clear all
  list_clear(&event_list);
}

int eventlog_poll(eventlog_event_t * event_out) {
  list_node_t * fnode = list_begin(&event_list);

  if(fnode) {
    // get the first node's value
    eventlog_event_t * event = list_getvalue(fnode);
    // copy to out event
    *event_out = *event;

    // free what the node contained
    free(event);
    // erase first node
    list_erase(fnode);

    return 1;
  } else {
    return 0;
  }
}

void eventlog_event_clear(eventlog_event_t * event) {
  // only message events contain owned data atm
  if(event->type == EVENTLOG_MESSAGE) {
    free(event->message.str);
  }
}


static void push_event(const eventlog_event_t * ev) {
  eventlog_event_t * event = malloc(sizeof(*event));
  *event = *ev;
  list_append(&event_list, event);
}


void eventlog_on_loadtile(hex_vec2i_t pos, const game_tile_state_t * tst) {
  assert(tst);

  eventlog_event_t ev;
  ZERO(ev);

  ev.type = EVENTLOG_LOADTILE;
  ev.loadtile.pos = pos;
  ev.loadtile.state = *tst;

  push_event(&ev);
}
void eventlog_on_unloadtile(hex_vec2i_t pos) {
  eventlog_event_t ev;
  ZERO(ev);

  ev.type = EVENTLOG_UNLOADTILE;
  ev.unloadtile.pos = pos;

  push_event(&ev);
}
void eventlog_on_cleartiles(void) {
  eventlog_event_t ev;
  ZERO(ev);

  ev.type = EVENTLOG_CLEARTILES;

  push_event(&ev);
}

void eventlog_on_loadobject(game_id_t id, const game_object_state_t * ost) {
  assert(ost);

  eventlog_event_t ev;
  ZERO(ev);

  ev.type = EVENTLOG_LOADOBJECT;
  ev.loadobject.id = id;
  ev.loadobject.state = *ost;

  push_event(&ev);
}
void eventlog_on_unloadobject(game_id_t id) {
  eventlog_event_t ev;
  ZERO(ev);

  ev.type = EVENTLOG_UNLOADOBJECT;
  ev.unloadobject.id = id;

  push_event(&ev);
}
void eventlog_on_clearobjects(void) {
  eventlog_event_t ev;
  ZERO(ev);

  ev.type = EVENTLOG_CLEAROBJECTS;

  push_event(&ev);
}

void eventlog_on_objectspawn(game_id_t id, int type) {
  eventlog_event_t ev;
  ZERO(ev);

  ev.type = EVENTLOG_OBJECTSPAWN;
  ev.objectspawn.id = id;
  ev.objectspawn.type = type;

  push_event(&ev);
}
void eventlog_on_objectdespawn(game_id_t id, int type) {
  eventlog_event_t ev;
  ZERO(ev);

  ev.type = EVENTLOG_OBJECTDESPAWN;
  ev.objectdespawn.id = id;
  ev.objectdespawn.type = type;

  push_event(&ev);
}

void eventlog_on_objectmove(game_id_t id, hex_vec2i_t pos, int type) {
  eventlog_event_t ev;
  ZERO(ev);

  ev.type = EVENTLOG_OBJECTMOVE;
  ev.objectmove.id = id;
  ev.objectmove.pos = pos;
  ev.objectmove.type = type;

  push_event(&ev);
}
void eventlog_on_objectstrike(game_id_t id, hex_vec2i_t pos, int type) {
  eventlog_event_t ev;
  ZERO(ev);

  ev.type = EVENTLOG_OBJECTSTRIKE;
  ev.objectstrike.id = id;
  ev.objectstrike.pos = pos;
  ev.objectstrike.type = type;

  push_event(&ev);
}

void eventlog_on_message(const char * str) {
  eventlog_event_t ev;
  ZERO(ev);

  ev.type = EVENTLOG_MESSAGE;

  ev.message.str = malloc(strlen(str)+1);
  if(ev.message.str) {
    strcpy(ev.message.str, str);
  }

  push_event(&ev);
}

