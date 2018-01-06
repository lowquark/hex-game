
#include <game/handlers.h>


game_cleartiles_handler_t    cleartiles_fn;
game_clearobjects_handler_t  clearobjects_fn;

game_loadtile_handler_t      loadtile_fn;
game_unloadtile_handler_t    unloadtile_fn;

game_loadobject_handler_t    loadobject_fn;
game_unloadobject_handler_t  unloadobject_fn;
game_objectmove_handler_t    objectmove_fn;
game_objectstrike_handler_t  objectstrike_fn;
game_objectdespawn_handler_t objectdespawn_fn;
game_objectspawn_handler_t   objectspawn_fn;

game_message_handler_t       message_fn;


#define TRY_CALL(_fn_) if(_fn_) { _fn_(); }
#define TRY_CALL_ARGS(_fn_, ...) if(_fn_) { _fn_(__VA_ARGS__); }


void game_set_cleartiles_handler(game_cleartiles_handler_t fn) {
  cleartiles_fn = fn;
}
void game_out_cleartiles() {
  TRY_CALL(cleartiles_fn);
}

void game_set_clearobjects_handler(game_clearobjects_handler_t fn) {
  clearobjects_fn = fn;
}
void game_out_clearobjects() {
  TRY_CALL(clearobjects_fn);
}


void game_set_loadtile_handler(game_loadtile_handler_t fn) {
  loadtile_fn = fn;
}
void game_out_loadtile(hex_vec2i_t pos, const game_tile_state_t * state) {
  TRY_CALL_ARGS(loadtile_fn, pos, state);
}

void game_set_unloadtile_handler(game_unloadtile_handler_t fn) {
  unloadtile_fn = fn;
}
void game_out_unloadtile(hex_vec2i_t pos) {
  TRY_CALL_ARGS(unloadtile_fn, pos);
}


void game_set_loadobject_handler(game_loadobject_handler_t fn) {
  loadobject_fn = fn;
}
void game_out_loadobject(game_id_t id, const game_object_state_t * obj) {
  TRY_CALL_ARGS(loadobject_fn, id, obj);
}

void game_set_unloadobject_handler(game_unloadobject_handler_t fn) {
  unloadobject_fn = fn;
}
void game_out_unloadobject(game_id_t id) {
  TRY_CALL_ARGS(unloadobject_fn, id);
}

void game_set_objectspawn_handler(game_objectspawn_handler_t fn) {
  objectspawn_fn = fn;
}
void game_out_objectspawn(game_id_t id, int type) {
  TRY_CALL_ARGS(objectspawn_fn, id, type);
}

void game_set_objectdespawn_handler(game_objectdespawn_handler_t fn) {
  objectdespawn_fn = fn;
}
void game_out_objectdespawn(game_id_t id, int type) {
  TRY_CALL_ARGS(objectdespawn_fn, id, type);
}

void game_set_objectmove_handler(game_objectmove_handler_t fn) {
  objectmove_fn = fn;
}
void game_out_objectmove(game_id_t id, hex_vec2i_t pos, int type) {
  TRY_CALL_ARGS(objectmove_fn, id, pos, type);
}

void game_set_objectstrike_handler(game_objectstrike_handler_t fn) {
  objectstrike_fn = fn;
}
void game_out_objectstrike(game_id_t id, hex_vec2i_t pos, int type) {
  TRY_CALL_ARGS(objectstrike_fn, id, pos, type);
}


void game_set_message_handler(game_message_handler_t fn) {
  message_fn = fn;
}
void game_out_message(const char * str) {
  TRY_CALL_ARGS(message_fn, str);
}

