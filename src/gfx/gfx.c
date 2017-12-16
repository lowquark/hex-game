
#include <gfx/gfx.h>

#include <assert.h>

static SDL_Renderer * rr = NULL;

void gfx_init(SDL_Window * window) {
  gfx_deinit();

  rr = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if(rr) {
    gfx_clear(NULL);
    gfx_flush();
  }
}
void gfx_deinit() {
  SDL_DestroyRenderer(rr);
  rr = NULL;
}


gfx_Sprite * gfx_create_sprite(const gfx_SpriteDef * def) {
  return NULL;
}
void gfx_destroy_sprite(gfx_Sprite * s) {
}


void gfx_draw_sprite(gfx_Sprite * spr, int x, int y, const gfx_Color * color) {
  SDL_Rect rekt_outer = { x - 8, y - 9, 18, 20 };
  SDL_Rect rekt_inner = { x - 7, y - 8, 16, 18 };

  if(color) {
    SDL_SetRenderDrawColor(rr, color->r, color->g, color->b, 0xFF);
  } else {
    SDL_SetRenderDrawColor(rr, 0x88, 0x88, 0x88, 0xFF);
  }
  SDL_RenderFillRect(rr, &rekt_outer);

  if(color) {
    SDL_SetRenderDrawColor(rr,
                           color->r - color->r / 4,
                           color->g - color->g / 4,
                           color->b - color->b / 4, 0xFF);
  } else {
    SDL_SetRenderDrawColor(rr, 0x44, 0x44, 0x44, 0xFF);
  }
  SDL_RenderFillRect(rr, &rekt_inner);
}

void gfx_draw_surface(SDL_Surface * surf, int x, int y, const gfx_Color * color) {
  assert(rr);
  assert(surf);

  SDL_Texture * tex = SDL_CreateTextureFromSurface(rr, surf);

  if(color) {
    SDL_SetTextureColorMod(tex, color->r, color->g, color->b);
  } else {
    SDL_SetTextureColorMod(tex, 0xFF, 0xFF, 0xFF);
  }

  SDL_Rect rekt = { x - surf->w/2, y - surf->h/2, surf->w, surf->h };

  SDL_RenderCopy(rr, tex, NULL, &rekt);

  SDL_DestroyTexture(tex);
  tex = NULL;
}

void gfx_clear(const gfx_Color * color) {
  if(color) {
    SDL_SetRenderDrawColor(rr, color->r, color->g, color->b, 0xFF);
  } else {
    SDL_SetRenderDrawColor(rr, 0x00, 0x00, 0x00, 0xFF);
  }

  SDL_RenderFillRect(rr, NULL);
}
void gfx_flush() {
  SDL_RenderPresent(rr);
}

