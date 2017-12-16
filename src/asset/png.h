#ifndef ASSET_PNG_H
#define ASSET_PNG_H

#include <SDL2/SDL_surface.h>

SDL_Surface * asset_png_load(const char * filename);
void          asset_png_save(const char * filename, const SDL_Surface * surf);

#endif
