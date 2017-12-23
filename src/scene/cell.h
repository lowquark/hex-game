#ifndef SCENE_CELL_H
#define SCENE_CELL_H

#include <gfx/gfx.h>

typedef struct {
  gfx_Sprite sprite;
  gfx_Color color;
} scene_tile_t;

typedef struct {
  gfx_Sprite sprite;
  gfx_Color color;
} scene_mob_t;

typedef struct {
  gfx_Sprite sprite;
  gfx_Color color;
} scene_item_t;

typedef struct {
  scene_tile_t tile;

  scene_mob_t * mobs;
  int mob_num;

  scene_item_t * items;
  int item_num;
} scene_cell_t;

#endif
