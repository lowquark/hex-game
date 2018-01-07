
#include <string.h>
#include <assert.h>

#include <gevbuf/gevbuf.h>
#include <util/list.h>


#define ZERO(x) memset(&x, 0, sizeof(x))

#define TRY_CALL(_fn_) if(_fn_) { _fn_(); }
#define TRY_CALL_ARGS(_fn_, ...) if(_fn_) { _fn_(__VA_ARGS__); }


static list_t event_list;


static void gevbuf_event_clear(gevbuf_event_t * event) {
  // only message events contain owned data atm
  if(event->type == GEVBUF_MESSAGE) {
    free(event->message.str);
  }
}


static void gevbuf_event_free_void(void * ev) {
  gevbuf_event_t * event = ev;
  gevbuf_event_clear(event);
  free(event);
}
void gevbuf_clear(void) {
  // free all
  list_each(&event_list, gevbuf_event_free_void);
  // clear all
  list_clear(&event_list);
}

static int pop_event(gevbuf_event_t * event_out) {
  list_node_t * fnode = list_begin(&event_list);

  if(fnode) {
    // get the first node's value
    gevbuf_event_t * event = list_getvalue(fnode);
    // (shallow) copy to out event
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


static void push_event(const gevbuf_event_t * ev) {
  gevbuf_event_t * event = malloc(sizeof(*event));
  *event = *ev;
  list_append(&event_list, event);
}


static void on_loadtile(hex_vec2i_t pos, const game_tile_state_t * tst) {
  assert(tst);

  gevbuf_event_t ev;
  ZERO(ev);

  ev.type = GEVBUF_LOADTILE;
  ev.loadtile.pos = pos;
  ev.loadtile.state = *tst;

  push_event(&ev);
}
static void on_unloadtile(hex_vec2i_t pos) {
  gevbuf_event_t ev;
  ZERO(ev);

  ev.type = GEVBUF_UNLOADTILE;
  ev.unloadtile.pos = pos;

  push_event(&ev);
}
static void on_cleartiles(void) {
  gevbuf_event_t ev;
  ZERO(ev);

  ev.type = GEVBUF_CLEARTILES;

  push_event(&ev);
}

static void on_loadobject(game_id_t id, const game_object_state_t * ost) {
  assert(ost);

  gevbuf_event_t ev;
  ZERO(ev);

  ev.type = GEVBUF_LOADOBJECT;
  ev.loadobject.id = id;
  ev.loadobject.state = *ost;

  push_event(&ev);
}
static void on_unloadobject(game_id_t id) {
  gevbuf_event_t ev;
  ZERO(ev);

  ev.type = GEVBUF_UNLOADOBJECT;
  ev.unloadobject.id = id;

  push_event(&ev);
}
static void on_clearobjects(void) {
  gevbuf_event_t ev;
  ZERO(ev);

  ev.type = GEVBUF_CLEAROBJECTS;

  push_event(&ev);
}

static void on_objectspawn(game_id_t id, int type) {
  gevbuf_event_t ev;
  ZERO(ev);

  ev.type = GEVBUF_OBJECTSPAWN;
  ev.objectspawn.id = id;
  ev.objectspawn.type = type;

  push_event(&ev);
}
static void on_objectdespawn(game_id_t id, int type) {
  gevbuf_event_t ev;
  ZERO(ev);

  ev.type = GEVBUF_OBJECTDESPAWN;
  ev.objectdespawn.id = id;
  ev.objectdespawn.type = type;

  push_event(&ev);
}

static void on_objectmove(game_id_t id, hex_vec2i_t pos, int type) {
  gevbuf_event_t ev;
  ZERO(ev);

  ev.type = GEVBUF_OBJECTMOVE;
  ev.objectmove.id = id;
  ev.objectmove.pos = pos;
  ev.objectmove.type = type;

  push_event(&ev);
}
static void on_objectstrike(game_id_t id, hex_vec2i_t pos, int type) {
  gevbuf_event_t ev;
  ZERO(ev);

  ev.type = GEVBUF_OBJECTSTRIKE;
  ev.objectstrike.id = id;
  ev.objectstrike.pos = pos;
  ev.objectstrike.type = type;

  push_event(&ev);
}

static void on_message(const char * str) {
  gevbuf_event_t ev;
  ZERO(ev);

  ev.type = GEVBUF_MESSAGE;

  ev.message.str = malloc(strlen(str)+1);
  if(ev.message.str) {
    strcpy(ev.message.str, str);
  }

  push_event(&ev);
}

static game_handlers_t out_handlers;

void gevbuf_set_handlers(const game_handlers_t * handlers) {
  out_handlers = *handlers;
}

static void handle(const gevbuf_event_t * event) {
  switch(event->type) {
    case GEVBUF_CLEARTILES:
      TRY_CALL(out_handlers.cleartiles);
      return;
    case GEVBUF_CLEAROBJECTS:
      TRY_CALL(out_handlers.clearobjects);
      return;

    case GEVBUF_LOADTILE:
      TRY_CALL_ARGS(out_handlers.loadtile,
                    event->loadtile.pos,
                    &event->loadtile.state);
      return;
    case GEVBUF_UNLOADTILE:
      TRY_CALL_ARGS(out_handlers.unloadtile,
                    event->unloadtile.pos);
      return;

    case GEVBUF_LOADOBJECT:
      TRY_CALL_ARGS(out_handlers.loadobject,
                    event->loadobject.id,
                    &event->loadobject.state);
      return;
    case GEVBUF_UNLOADOBJECT:
      TRY_CALL_ARGS(out_handlers.unloadobject,
                    event->unloadobject.id);
      return;

    case GEVBUF_OBJECTSPAWN:
      TRY_CALL_ARGS(out_handlers.objectspawn,
                    event->objectspawn.id,
                    event->objectspawn.type);
      return;
    case GEVBUF_OBJECTDESPAWN:
      TRY_CALL_ARGS(out_handlers.objectdespawn,
                    event->objectdespawn.id,
                    event->objectdespawn.type);
      return;
    case GEVBUF_OBJECTMOVE:
      TRY_CALL_ARGS(out_handlers.objectmove,
                    event->objectmove.id,
                    event->objectmove.pos,
                    event->objectmove.type);
      return;
    case GEVBUF_OBJECTSTRIKE:
      TRY_CALL_ARGS(out_handlers.objectstrike,
                    event->objectstrike.id,
                    event->objectstrike.pos,
                    event->objectstrike.type);
      return;

    case GEVBUF_MESSAGE:
      TRY_CALL_ARGS(out_handlers.message,
                    event->message.str);
      return;
    default:
      return;
  }
}

int gevbuf_step(void) {
  gevbuf_event_t event;
  // try to get an event
  if(pop_event(&event)) {
    // handle this event
    handle(&event);
    // free its resources
    gevbuf_event_clear(&event);
    return 1;
  } else {
    // no events, please stop calling me
    return 0;
  }
}

game_handlers_t gevbuf_game_handlers = {
  .cleartiles = on_cleartiles,
  .clearobjects = on_clearobjects,

  .loadtile = on_loadtile,
  .unloadtile = on_unloadtile,

  .loadobject = on_loadobject,
  .unloadobject = on_unloadobject,
  .objectmove = on_objectmove,
  .objectstrike = on_objectstrike,
  .objectdespawn = on_objectdespawn,
  .objectspawn = on_objectspawn,

  .message = on_message,
};

