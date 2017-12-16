
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


gfx_Sprite * gfx_load_sprite(const gfx_SpriteDef * def) {
  assert(rr);
  assert(def);
  assert(def->surface);

  gfx_Sprite * spr = malloc(sizeof *spr);

  spr->texture = SDL_CreateTextureFromSurface(rr, def->surface);

  spr->size_x = def->surface->w;
  spr->size_y = def->surface->h;
  spr->offset_x = def->offset_x;
  spr->offset_y = def->offset_y;

  return spr;
}
void gfx_unload_sprite(gfx_Sprite * s) {
  if(s) {
    SDL_DestroyTexture(s->texture);
    s->texture = NULL;
    s->offset_x = 0;
    s->offset_y = 0;
    free(s);
  }
}


void gfx_draw_sprite(gfx_Sprite * spr, int x, int y, const gfx_Color * color) {
  assert(rr);
  assert(spr);
  assert(spr->texture);

  SDL_Texture * tex = spr->texture;

  if(color) {
    SDL_SetTextureColorMod(tex, color->r, color->g, color->b);
  } else {
    SDL_SetTextureColorMod(tex, 0xFF, 0xFF, 0xFF);
  }

  SDL_Rect rekt = { x - spr->offset_x,
                    y - spr->offset_y,
                    spr->size_x,
                    spr->size_y, };

  SDL_RenderCopy(rr, tex, NULL, &rekt);
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

