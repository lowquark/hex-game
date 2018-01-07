
#include <game/handlers.h>


static game_handlers_t handlers;


#define TRY_CALL(_fn_) if(_fn_) { _fn_(); }
#define TRY_CALL_ARGS(_fn_, ...) if(_fn_) { _fn_(__VA_ARGS__); }


void game_out_cleartiles() {
  TRY_CALL(handlers.cleartiles);
}

void game_out_clearobjects() {
  TRY_CALL(handlers.clearobjects);
}


void game_out_loadtile(hex_vec2i_t pos, const game_tile_state_t * state) {
  TRY_CALL_ARGS(handlers.loadtile, pos, state);
}

void game_out_unloadtile(hex_vec2i_t pos) {
  TRY_CALL_ARGS(handlers.unloadtile, pos);
}


void game_out_loadobject(game_id_t id, const game_object_state_t * obj) {
  TRY_CALL_ARGS(handlers.loadobject, id, obj);
}

void game_out_unloadobject(game_id_t id) {
  TRY_CALL_ARGS(handlers.unloadobject, id);
}

void game_out_objectspawn(game_id_t id, int type) {
  TRY_CALL_ARGS(handlers.objectspawn, id, type);
}

void game_out_objectdespawn(game_id_t id, int type) {
  TRY_CALL_ARGS(handlers.objectdespawn, id, type);
}

void game_out_objectmove(game_id_t id, hex_vec2i_t pos, int type) {
  TRY_CALL_ARGS(handlers.objectmove, id, pos, type);
}

void game_out_objectstrike(game_id_t id, hex_vec2i_t pos, int type) {
  TRY_CALL_ARGS(handlers.objectstrike, id, pos, type);
}


void game_out_message(const char * str) {
  TRY_CALL_ARGS(handlers.message, str);
}

void game_set_handlers(const game_handlers_t * h) {
  handlers = *h;
}

