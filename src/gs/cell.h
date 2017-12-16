#ifndef GS_CELL_H
#define GS_CELL_H

#include <stdint.h>

// game colors
typedef struct {
  uint8_t r, g, b;
} gs_color_t;

#define GS_COLOR_INIT   { 0x00, 0x00, 0x00 }
#define GS_COLOR_FROM24(_color_) { (uint8_t)(((_color_) >> 16) & 0xFF), \
                                   (uint8_t)(((_color_) >>  8) & 0xFF), \
                                   (uint8_t)(((_color_)      ) & 0xFF), }

static inline gs_color_t gs_color_from24(uint32_t color) {
  return (gs_color_t)GS_COLOR_FROM24(color);
}

// a segment of floor / wall
typedef struct {
  int sprite_id;
  gs_color_t fg_color;
  gs_color_t bg_color;
} gs_tile_t;

#define GS_TILE_INIT   { 0, GS_COLOR_INIT, GS_COLOR_INIT }

// something inanimate that you can step over or pick up
typedef struct {
  int sprite_id;
  const char * name;
  int quantity;
} gs_item_t;

#define GS_ITEM_INIT   { 0, NULL, 0 }

// something that you can't walk through, and might move or attack
typedef struct {
  int sprite_id;
  const char * name;
  int health;
} gs_mob_t;

#define GS_MOB_INIT   { 0, NULL, 0 }


// something that you can't walk through, and might move or attack
typedef struct {
  gs_mob_t * mobs;
  gs_item_t * items;

  int mob_num;
  int item_num;

  gs_tile_t tile;

} gs_cell_t;

#define GS_CELL_INIT   { NULL, NULL, 0, 0, GS_TILE_INIT }

#endif
