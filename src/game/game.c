
#include <game/game.h>

#include <string.h>


void game_init() {
}
void game_deinit() {
}

void game_step_wait() {
}
void game_step_moveupright() {
}
void game_step_moveup() {
}
void game_step_moveupleft() {
}
void game_step_movedownleft() {
}
void game_step_movedown() {
}
void game_step_movedownright() {
}

void game_load() {
}
void game_save() {
}

static const game_color_t nespresso[5] = {
  GAME_COLOR_FROM24(0x2e2e2c),
  GAME_COLOR_FROM24(0x402108),
  GAME_COLOR_FROM24(0x4b1e0d),
  GAME_COLOR_FROM24(0xbd6416),
  GAME_COLOR_FROM24(0xfdaf3e),
};
static const game_color_t grassy[5] = {
  GAME_COLOR_FROM24(0x67ab05),
  GAME_COLOR_FROM24(0x80bf26),
  GAME_COLOR_FROM24(0xa4e333),
  GAME_COLOR_FROM24(0xc8ff66),
  GAME_COLOR_FROM24(0xe9ff96),
};
static const game_color_t dirty[3] = {
  GAME_COLOR_FROM24(0x7e5f40),
  GAME_COLOR_FROM24(0x725222),
  GAME_COLOR_FROM24(0x6d4720),
};

// 
void game_drawstate(const game_DrawStateHandlers * state) {
  for(int j = 0 ; j < 8 ; j ++) {
    for(int i = 0 ; i < 8 ; i ++) {
      game_CellState cell;

      memset(&cell, 0, sizeof(cell));

      cell.pos.x = i;
      cell.pos.y = j;

      cell.tile.type_id = 1;
      cell.tile.color = grassy[rand() % 5];

      state->cell(&cell);

      memset(&cell, 0, sizeof(cell));

      cell.pos.x = i;
      cell.pos.y = -i-j;

      cell.tile.type_id = 1;
      cell.tile.color = grassy[rand() % 5];

      state->cell(&cell);

      memset(&cell, 0, sizeof(cell));

      cell.pos.x = -i-j;
      cell.pos.y = j;

      cell.tile.type_id = 1;
      cell.tile.color = grassy[rand() % 5];

      state->cell(&cell);
    }
  }
}
// 
void game_drawevents(const game_DrawEventHandlers * handlers) {
}

