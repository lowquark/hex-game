
#include <png.h>
#include <assert.h>

#include <asset/lodepng.h>
#include <asset/png.h>

SDL_Surface * asset_png_load(const char * filename)
{
  unsigned int error;
  unsigned int w, h;
  unsigned char * image;

  int surfwidth;
  int surfheight;

  int bpp;
  Uint32 rmask, gmask, bmask, amask;

  SDL_Surface * surf = NULL;

  error = lodepng_decode32_file(&image, &w, &h, filename);

  if(error) {
    printf("lodepng error %u: %s\n", error, lodepng_error_text(error));
  } else {
    if(w <= INT_MAX && h <= INT_MAX) {
      surfwidth = w;
      surfheight = h;

      SDL_PixelFormatEnumToMasks(
          SDL_PIXELFORMAT_RGBA32,
          &bpp, &rmask, &gmask, &bmask, &amask);

      /*
      printf("<%dx%d>\n", surfwidth, surfheight);
      printf("bpp: %d\n", bpp);
      printf("rmask: %08X\n", rmask);
      printf("gmask: %08X\n", gmask);
      printf("bmask: %08X\n", bmask);
      printf("amask: %08X\n", amask);
      */

      surf = SDL_CreateRGBSurface(0, surfwidth, surfheight, bpp,
                                  rmask, gmask, bmask, amask);

      memcpy(surf->pixels, image, w*h*bpp/8);
    } else {
      printf("png too large\n");
    }

    free(image);
    image = NULL;
  }

  return surf;
}

