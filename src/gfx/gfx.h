#ifndef GFX_GFX_H
#define GFX_GFX_H

#include <SDL2/SDL.h>

typedef struct {
  uint8_t r, g, b, a;
} gfx_Color;

typedef struct {
  // pixels, in rgba format
  const uint8_t * pixels;
  // width of sprite, in pixels
  int pixels_w;
  // height of sprite, in pixels
  int pixels_h;

  // sprite origin x
  int offset_x;
  // sprite origin y
  int offset_y;
} gfx_SpriteDef;

typedef struct {
  int a;
} gfx_Sprite;


void gfx_init(SDL_Window * window);
void gfx_deinit();


gfx_Sprite * gfx_create_sprite(const gfx_SpriteDef * def);
void         gfx_destroy_sprite(gfx_Sprite * s);


void gfx_draw_sprite(gfx_Sprite * spr, int x, int y, const gfx_Color * color);

void gfx_draw_surface(SDL_Surface * surf, int x, int y, const gfx_Color * color);

void gfx_clear(const gfx_Color * color);
void gfx_flush();


#endif
