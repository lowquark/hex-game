
#include <game/game.h>

#include <string.h>


/*
static const game_color_t nespresso[5] = {
  GAME_COLOR_FROM24(0x2e2e2c),
  GAME_COLOR_FROM24(0x402108),
  GAME_COLOR_FROM24(0x4b1e0d),
  GAME_COLOR_FROM24(0xbd6416),
  GAME_COLOR_FROM24(0xfdaf3e),
};
*/
static const game_color_t grassy[5] = {
  GAME_COLOR_FROM24(0x67ab05),
  GAME_COLOR_FROM24(0x80bf26),
  GAME_COLOR_FROM24(0xa4e333),
  GAME_COLOR_FROM24(0xc8ff66),
  GAME_COLOR_FROM24(0xe9ff96),
};
/*
static const game_color_t dirty[3] = {
  GAME_COLOR_FROM24(0x7e5f40),
  GAME_COLOR_FROM24(0x725222),
  GAME_COLOR_FROM24(0x6d4720),
};
*/


void game_clear() {
}

void game_load() {
  for(int j = 0 ; j < 8 ; j ++) {
    for(int i = 0 ; i < 8 ; i ++) {
      game_tile_state_t tile;
      hex_vec2i_t pos;

      memset(&tile, 0, sizeof(tile));

      pos.x = i;
      pos.y = j;

      tile.sprite_id = 1;
      tile.color = grassy[rand() % 5];

      game_out_tilestate(pos, &tile);

      memset(&tile, 0, sizeof(tile));

      pos.x = i;
      pos.y = -i-j;

      tile.sprite_id = 1;
      tile.color = grassy[rand() % 5];

      game_out_tilestate(pos, &tile);

      memset(&tile, 0, sizeof(tile));

      pos.x = -i-j;
      pos.y = j;

      tile.sprite_id = 1;
      tile.color = grassy[rand() % 5];

      game_out_tilestate(pos, &tile);
    }
  }

  game_id_t id = 0;
  for(int i = 0 ; i < 20 ; i ++) {
    game_object_state_t obj;

    memset(&obj, 0, sizeof(obj));

    obj.pos.x = i % 4;
    obj.pos.y = i / 4;
    obj.color.r = 0xFF;
    obj.color.g = 0xFF - i*5;
    obj.color.b = 0xFF - i*10;

    game_out_objectstate(id++, &obj);
  }
}
void game_save() {
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

