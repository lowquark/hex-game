#ifndef SCENE_SPRITES_H
#define SCENE_SPRITES_H

#include <hex/hex.h>
#include <gfx/gfx.h>

#include <scene/id.h>

struct scene_sprite;

#define SCENE_SPRITE_TILE_SOLID     0
#define SCENE_SPRITE_TILE_DITHER_0  1
#define SCENE_SPRITE_TILE_DITHER_1  2
#define SCENE_SPRITE_TILE_DITHER_2  3

#define SCENE_SPRITE_HERO           1000

typedef struct scene_sprite_list {
  struct scene_sprite_list * head;
  struct scene_sprite_list * next;
  struct scene_sprite_list * prev;
  struct scene_sprite * owner;
} scene_sprite_list_t;

typedef struct scene_sprite {
  int x, y, z;

  gfx_Sprite sprite;
  gfx_Color color;

  unsigned int flip_x : 1;
  unsigned int flip_y : 1;
} scene_sprite_t;

void scene_sprite_set_pos   (scene_sprite_t * spr, int x, int y, int z);
void scene_sprite_set_color (scene_sprite_t * spr, int idx, const gfx_Color color);
void scene_sprite_set_sprite(scene_sprite_t * spr, int sprite_id);
void scene_sprite_set_flip_x(scene_sprite_t * spr, int flip);
void scene_sprite_set_flip_y(scene_sprite_t * spr, int flip);

void scene_sprites_load(void);
void scene_sprites_unload(void);

void scene_sprites_draw_begin(void);
void scene_sprites_draw(const scene_sprite_t * sprite);
void scene_sprites_draw_end(void);

#endif
