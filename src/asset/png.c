
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
      surfwidth = (int)w;
      surfheight = (int)h;

      SDL_PixelFormatEnumToMasks(
          SDL_PIXELFORMAT_RGBA32,
          &bpp, &rmask, &gmask, &bmask, &amask);

      surf = SDL_CreateRGBSurfaceFrom(image, surfwidth, surfheight, bpp, surfwidth*4,
                                      rmask, gmask, bmask, amask);
    } else {
      printf("png too large\n");
    }

    free(image);
    image = NULL;
  }

  return surf;
}

