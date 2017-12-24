#ifndef SCENE_SPRITES_H
#define SCENE_SPRITES_H

#include <gfx/gfx.h>

typedef struct {
  int x, y;
  gfx_Sprite sprite;
  gfx_Color color;
} scene_Sprite;

typedef struct {
  hex_vec2i_t hex;
  int off_x, off_y;

  gfx_Sprite sprite;
  gfx_Sprite altsprite;

  gfx_Color color;
  gfx_Color altcolor;

  int anim_x, anim_y;

  unsigned int flip_x : 1;
  unsigned int flip_y : 1;
} scene_Sprite2;

scene_Sprite * scene_sprite     (unsigned long id);
scene_Sprite * scene_getsprite  (unsigned long id);
void           scene_clearsprite(unsigned long id);

scene_Sprite ** scene_sortsprites();

#endif
