
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


gfx_SpriteSheet * gfx_load_spritesheet(const SDL_Surface * surface) {
  assert(rr);
  assert(surface);

  gfx_SpriteSheet * ss = malloc(sizeof *ss);

  // documentation specifically states surf is unmodified
  ss->texture = SDL_CreateTextureFromSurface(rr, (SDL_Surface *)surface);

  ss->size_x = surface->w;
  ss->size_y = surface->h;

  return ss;
}
void gfx_unload_spritesheet(gfx_SpriteSheet * ss) {
  if(ss) {
    SDL_DestroyTexture(ss->texture);
    ss->texture = NULL;
    ss->size_x = 0;
    ss->size_y = 0;
    free(ss);
  }
}

gfx_Sprite gfx_sprite(gfx_SpriteSheet * sheet,
                      int x, int y, int w, int h,
                      int offset_x, int offset_y)
{
  gfx_Sprite spr;
  spr.sheet = sheet;
  spr.sheet_x = x;
  spr.sheet_y = y;
  spr.size_x = w;
  spr.size_y = h;
  spr.offset_x = offset_x;
  spr.offset_y = offset_y;
  return spr;
}

void gfx_draw_sprite(const gfx_Sprite * spr, int x, int y, const gfx_Color * color) {
  assert(rr);
  assert(spr);
  assert(spr->sheet);
  assert(spr->sheet->texture);

  gfx_SpriteSheet * ss = spr->sheet;
  SDL_Texture * tex = ss->texture;

  if(color) {
    SDL_SetTextureColorMod(tex, color->r, color->g, color->b);
  } else {
    SDL_SetTextureColorMod(tex, 0xFF, 0xFF, 0xFF);
  }

  SDL_Rect src_rekt = { spr->sheet_x,
                        spr->sheet_y,
                        spr->size_x,
                        spr->size_y, };

  SDL_Rect dst_rekt = { x - spr->offset_x,
                        y - spr->offset_y,
                        spr->size_x,
                        spr->size_y, };

  SDL_RenderCopy(rr, tex, &src_rekt, &dst_rekt);

  /*
  SDL_SetRenderDrawColor(rr, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(rr, &dst_rekt);
  SDL_SetRenderDrawColor(rr, 0x00, 0x00, 0xFF, 0xFF);
  SDL_RenderDrawPoint(rr, x, y);
  */
}

void gfx_draw_surface(const SDL_Surface * surf, int x, int y, const gfx_Color * color) {
  assert(rr);
  assert(surf);

  // documentation specifically states surf is unmodified
  SDL_Texture * tex = SDL_CreateTextureFromSurface(rr, (SDL_Surface *)surf);

  if(color) {
    SDL_SetTextureColorMod(tex, color->r, color->g, color->b);
  } else {
    SDL_SetTextureColorMod(tex, 0xFF, 0xFF, 0xFF);
  }

  SDL_Rect rekt = { x, y, surf->w, surf->h };

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

