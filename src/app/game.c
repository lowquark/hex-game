
#include <stdio.h>

#include <game/game.h>
#include <game/handlers.h>
#include <gevbuf/gevbuf.h>
#include <scene/scene.h>
#include <gfx/gfx.h>

#include <app/game.h>


void on_loadtile(hex_vec2i_t pos, const game_tile_state_t * state) {
  scene_tile_state_t tst = SCENE_TILE_STATE_NULL;

  tst.color.r = state->color.r;
  tst.color.g = state->color.g;
  tst.color.b = state->color.b;
  tst.color.a = 0xFF;

  scene_tiles_load(pos, &tst);
}
void on_unloadtile(hex_vec2i_t pos) {
  scene_tiles_unload(pos);
}

void on_loadobject(game_id_t id, const game_object_state_t * state) {
  scene_object_state_t ost = SCENE_OBJECT_STATE_NULL;

  ost.pos = state->pos;
  ost.color.r = state->color.r;
  ost.color.g = state->color.g;
  ost.color.b = state->color.b;
  ost.color.a = 0xFF;

  scene_objects_load(id, &ost);
}
void on_unloadobject(game_id_t id) {
  scene_objects_unload(id);
}

void on_objectspawn(game_id_t id, int type) {
  scene_object_t * obj = scene_objects_get(id);

  if(obj) {
    scene_object_spawn(obj, type);
  }
}
void on_objectdespawn(game_id_t id, int type) {
  scene_object_t * obj = scene_objects_get(id);

  if(obj) {
    scene_object_despawn(obj, type);
  }
}

void on_objectmove(game_id_t id, hex_vec2i_t newpos, int type) {
  scene_object_t * obj = scene_objects_get(id);

  if(obj) {
    scene_object_skipanimation(obj);
    scene_object_move(obj, newpos);
  }
}

static game_handlers_t game_handlers = {
  .cleartiles = NULL,
  .clearobjects = NULL,

  .loadtile = on_loadtile,
  .unloadtile = on_unloadtile,

  .loadobject = on_loadobject,
  .unloadobject = on_unloadobject,
  .objectmove = on_objectmove,
  .objectstrike = NULL,
  .objectdespawn = on_objectdespawn,
  .objectspawn = on_objectspawn,

  .message = NULL,
};

static void tick() {
  // flush all events we can
  // TODO: stop based on animations
  while(gevbuf_step()) {}

  scene_tick();
  scene_draw();
  gfx_flush();
}


// app game states
typedef enum {
  ANIMATE = 0,
  DECIDE,
  FINISHED,
} state_t;

static state_t state;

extern void run_enter(void);
extern void decide_enter(void);
extern void finished_enter(void);

// run state - simulate game, draw animations
void run_enter(void) {
  //printf("run: entering...\n");
  state = ANIMATE;
}
void run_on_fixedupdate(void) {
  //printf("run: fixedupdate signal received\n");

  tick();

  if(scene_isanimating()) {
    // do nothing - scene still animating
  } else {
    // scene has finished animating its events
    if(game_isplayerturn()) {
      // it's the player's turn, stop and decide what to do!
      decide_enter();
    } else {
      // need more simulation
      // (this feeds events to the gevbuf)
      game_simulate(100);
    }
  }
}
void run_on_keydown(SDL_Keycode sym) {
  //printf("run: keydown signal received\n");
  // pressed a key, skip animations
  scene_skip_animations();
}
void run_on_quit() {
  //printf("run: quit signal received\n");
  // tried to quit, skip animations
  scene_skip_animations();
}

// decide state - player's turn, so decide on an action
void decide_enter(void) {
  //printf("deicde: entering...\n");
  state = DECIDE;
}
void decide_on_fixedupdate(void) {
  //printf("deicde: fixedupdate signal received\n");
  tick();
}
void decide_on_keydown(SDL_Keycode sym) {
  //printf("deicde: keydown signal received\n");

  switch(sym) {
    case SDLK_SPACE:
      // wait and run
      game_player_wait();
      run_enter();
      break;
    case SDLK_e:
      game_player_movedownright();
      run_enter();
      break;
    case SDLK_w:
      game_player_movedown();
      run_enter();
      break;
    case SDLK_q:
      game_player_movedownleft();
      run_enter();
      break;
    case SDLK_a:
      game_player_moveupleft();
      run_enter();
      break;
    case SDLK_s:
      game_player_moveup();
      run_enter();
      break;
    case SDLK_d:
      game_player_moveupright();
      run_enter();
      break;
  }
}
void decide_on_quit() {
  //printf("deicde: quit signal received\n");
  finished_enter();
}

// finished state - wait for shutdown
void finished_enter(void) {
  state = FINISHED;
}

//////// frontend ////////

// start game by loading
void app_game_load(const char * save_name) {

  // configure game module to send its events to gevbuf module
  game_set_handlers(&gevbuf_game_handlers);
  // configure gevbuf module to send its events to us
  gevbuf_set_handlers(&game_handlers);

  // load saved game
  game_load();

  // run until it's a player's turn
  run_enter();
}
void app_game_clear(void) {
  game_clear();
  scene_clear();
}

void app_game_update(void) {
  switch(state) {
    default:
      return;
  }
}
void app_game_fixedupdate(void) {
  // dispatch fixedupdate
  switch(state) {
    case ANIMATE:
      run_on_fixedupdate();
      return;
    case DECIDE:
      decide_on_fixedupdate();
      return;
    default:
      return;
  }
}
void app_game_keydown(SDL_Keycode sym) {
  switch(state) {
    case ANIMATE:
      run_on_keydown(sym);
      return;
    case DECIDE:
      decide_on_keydown(sym);
      return;
    default:
      return;
  }
}
// user quit signal
void app_game_quit(void) {
  switch(state) {
    case ANIMATE:
      run_on_quit();
      return;
    case DECIDE:
      decide_on_quit();
      return;
    default:
      return;
  }
}

bool app_game_quitsignal(app_game_quitsignal_t * sig) {
  if(state == FINISHED) {
    *sig = APP_GAME_QUIT;
    return true;
  } else {
    return false;
  }
}

