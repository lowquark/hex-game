#ifndef GFX_GFX_H
#define GFX_GFX_H

#include <SDL2/SDL.h>

typedef struct {
  uint8_t r, g, b, a;
} gfx_Color;

typedef struct {
  SDL_Texture * texture;

  int size_x;
  int size_y;
} gfx_SpriteSheet;

typedef struct {
  gfx_SpriteSheet * sheet;

  // sprite position in sheet
  int sheet_x;
  int sheet_y;

  // sprite size in sheet
  int size_x;
  int size_y;

  // sprite offset origin
  int offset_x;
  int offset_y;
} gfx_Sprite;

// initializes a rendering context given `window`
void gfx_init(SDL_Window * window);
// deinitializes everything, frees all spritesheets
void gfx_deinit();

// load a texture for `surf`, stores in spritesheet
gfx_SpriteSheet * gfx_load_spritesheet(const SDL_Surface * surf);
// unload a sprite sheet
void gfx_unload_spritesheet(gfx_SpriteSheet * s);

// create a sprite from a spritesheet
// don't use this sprite after `sheet` has been freed
gfx_Sprite gfx_sprite(gfx_SpriteSheet * sheet,
                      int x, int y, int w, int h,
                      int offset_x, int offset_y);

// draw a sprite at a given location with a given shade
void gfx_draw_sprite(const gfx_Sprite * spr, int x, int y, const gfx_Color * shade);

// load a texture for `surf` and draw at a given location with a given shade
void gfx_draw_surface(const SDL_Surface * surf, int x, int y, const gfx_Color * shade);

void gfx_clear(const gfx_Color * color);
void gfx_flush();


#endif
