#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <hex/hex.h>

#include <stdint.h>

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
} game_TileState;

typedef struct {
  unsigned int sprite_id;
  game_color_t color;
} game_EntityState;

typedef struct {
  void (*entity)(unsigned int eid, hex_vec2i_t pos);
  void (*tile)(hex_vec2i_t pos, const game_TileState * state);
} game_DrawStateHandlers;

typedef struct {
  void (*mob_move)(void);
  void (*mob_strike)(void);
  void (*message)(const char * str);
} game_DrawEventHandlers;


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
void game_drawstate(const game_DrawStateHandlers * state);
// 
void game_drawevents(const game_DrawEventHandlers * handlers);


#endif
