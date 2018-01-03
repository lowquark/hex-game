#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <hex/hex.h>

#include <stdint.h>

typedef unsigned long game_id_t;

typedef struct {
  uint8_t r, g, b;
} game_color_t;

#define GAME_COLOR_FROM24(_color_) { (uint8_t)(((_color_) >> 16) & 0xFF), \
                                     (uint8_t)(((_color_) >>  8) & 0xFF), \
                                     (uint8_t)(((_color_)      ) & 0xFF), }

static inline game_color_t game_color_from24(uint32_t color) {
  return (game_color_t)GAME_COLOR_FROM24(color);
}

typedef struct {
  unsigned int sprite_id;
  game_color_t color;
} game_tile_state_t;

typedef struct {
  hex_vec2i_t pos;
  unsigned int sprite_id;
  game_color_t color;
} game_object_state_t;


typedef struct {
  void (*object)(game_id_t id, const game_object_state_t * obj);
  void (*tile)(hex_vec2i_t pos, const game_tile_state_t * state);
} game_state_handlers_t;

typedef struct {
  void (*mob_move)(void);
  void (*mob_strike)(void);
  void (*message)(const char * str);
} game_event_handlers_t;


void game_init(void);
void game_deinit(void);

void game_step_wait(void);
void game_step_moveupright(void);
void game_step_moveup(void);
void game_step_moveupleft(void);
void game_step_movedownleft(void);
void game_step_movedown(void);
void game_step_movedownright(void);

void game_load(void);
void game_save(void);


// 
void game_drawstate(const game_state_handlers_t * state);
// 
void game_drawevents(const game_event_handlers_t * handlers);


#endif
