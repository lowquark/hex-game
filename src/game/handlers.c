
#include <game/handlers.h>


game_clear_handler_t        clear_fn;

game_tilestate_handler_t    tilestate_fn;

game_objectstate_handler_t  objectstate_fn;
game_objectmove_handler_t   objectmove_fn;
game_objectstrike_handler_t objectstrike_fn;
game_objecthide_handler_t   objecthide_fn;
game_objectshow_handler_t   objectshow_fn;

game_message_handler_t      message_fn;


#define TRY_CALL(_fn_) if(_fn_) { _fn_(); }
#define TRY_CALL_ARGS(_fn_, ...) if(_fn_) { _fn_(__VA_ARGS__); }


void game_set_clear_handler(game_clear_handler_t fn) {
  clear_fn = fn;
}
void game_out_clear() {
  TRY_CALL(clear_fn);
}


void game_set_tilestate_handler(game_tilestate_handler_t fn) {
  tilestate_fn = fn;
}
void game_out_tilestate(hex_vec2i_t pos, const game_tile_state_t * state) {
  TRY_CALL_ARGS(tilestate_fn, pos, state);
}


void game_set_objectstate_handler(game_objectstate_handler_t fn) {
  objectstate_fn = fn;
}
void game_out_objectstate(game_id_t id, const game_object_state_t * obj) {
  TRY_CALL_ARGS(objectstate_fn, id, obj);
}

void game_set_objectmove_handler(game_objectmove_handler_t fn) {
  objectmove_fn = fn;
}
void game_out_objectmove(game_id_t id, hex_vec2i_t pos) {
  TRY_CALL_ARGS(objectmove_fn, id, pos);
}

void game_set_objectstrike_handler(game_objectstrike_handler_t fn) {
  objectstrike_fn = fn;
}
void game_out_objectstrike(game_id_t id, hex_vec2i_t pos) {
  TRY_CALL_ARGS(objectstrike_fn, id, pos);
}

void game_set_objecthide_handler(game_objecthide_handler_t fn) {
  objecthide_fn = fn;
}
void game_out_objecthide(game_id_t id) {
  TRY_CALL_ARGS(objecthide_fn, id);
}

void game_set_objectshow_handler(game_objectshow_handler_t fn) {
  objectshow_fn = fn;
}
void game_out_objectshow(game_id_t id) {
  TRY_CALL_ARGS(objectshow_fn, id);
}


void game_set_message_handler(game_message_handler_t fn) {
  message_fn = fn;
}
void game_out_message(const char * str) {
  TRY_CALL_ARGS(message_fn, str);
}

