
#include <png.h>
#include <assert.h>

#include <asset/png.h>

SDL_Surface * asset_png_load(const char * filename)
{
  FILE * fp = fopen(filename, "rb");
  SDL_Surface * surface_out = NULL;

  if(fp) {
    unsigned char header[8];

    fread(header, 1, 8, fp);

    if(!png_sig_cmp(header, 0, 8)) {
      // Header is good so far, get ready to read
      png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
      png_infop info_ptr = NULL;

      if(png_ptr) {
        info_ptr = png_create_info_struct(png_ptr);

        if(info_ptr) {
          png_byte * data = NULL;

          if(!setjmp(png_jmpbuf(png_ptr))) {
            png_init_io(png_ptr, fp);
            png_set_sig_bytes(png_ptr, 8);

            png_read_info(png_ptr, info_ptr);

            png_uint_32 width = png_get_image_width(png_ptr, info_ptr);
            png_uint_32 height = png_get_image_height(png_ptr, info_ptr);
            int color_type = png_get_color_type(png_ptr, info_ptr);

            if((color_type == PNG_COLOR_TYPE_RGB || 
                 color_type == PNG_COLOR_TYPE_RGB_ALPHA ||
                 color_type == PNG_COLOR_TYPE_GRAY ||
                 color_type == PNG_COLOR_TYPE_GRAY_ALPHA)) {
              png_read_update_info(png_ptr, info_ptr);
              png_size_t row_bytes = png_get_rowbytes(png_ptr, info_ptr);

              // allocate enough data for all rows
              data = malloc(row_bytes * height);

              // read all rows
              for(unsigned int i = 0 ; i < height ; i ++) {
                png_read_row(png_ptr, data + i*row_bytes, NULL);
              }

              printf("Read PNG %s: width=%u, height=%u, color_type=%u\n",
                     filename,
                     width,
                     height,
                     color_type);

              int bpp;
              Uint32 rmask, gmask, bmask, amask;

              // depending on the format, load the data into an SDL surface
              if(color_type == PNG_COLOR_TYPE_RGB)
              {
                SDL_PixelFormatEnumToMasks(
                    SDL_PIXELFORMAT_RGB24,
                    &bpp, &rmask, &gmask, &bmask, &amask);
                surface_out = SDL_CreateRGBSurface(
                    0, (int)width, (int)height,
                    bpp, rmask, gmask, bmask, amask);

                uint8_t * p = (uint8_t *)surface_out->pixels;

                assert(surface_out->pitch >= row_bytes);

                for(unsigned int j = 0 ; j < height ; j ++) {
                  memcpy(p + j * (unsigned int)surface_out->pitch,
                         data + j * row_bytes,
                         row_bytes);
                }
              }
              else if(color_type == PNG_COLOR_TYPE_RGB_ALPHA)
              {
                SDL_PixelFormatEnumToMasks(
                    SDL_PIXELFORMAT_RGBA32,
                    &bpp, &rmask, &gmask, &bmask, &amask);
                surface_out = SDL_CreateRGBSurface(
                    0, (int)width, (int)height,
                    bpp, rmask, gmask, bmask, amask);

                uint8_t * p = (uint8_t *)surface_out->pixels;

                assert(surface_out->pitch >= row_bytes);

                for(unsigned int j = 0 ; j < height ; j ++) {
                  memcpy(p + j * (unsigned int)surface_out->pitch,
                         data + j * row_bytes,
                         row_bytes);
                }
              }
              else if(color_type == PNG_COLOR_TYPE_GRAY)
              {
                SDL_PixelFormatEnumToMasks(
                    SDL_PIXELFORMAT_RGB24,
                    &bpp, &rmask, &gmask, &bmask, &amask);
                surface_out = SDL_CreateRGBSurface(
                    0, (int)width, (int)height,
                    bpp, rmask, gmask, bmask, amask);

                uint8_t * p = (uint8_t *)surface_out->pixels;

                assert(surface_out->pitch >= row_bytes);

                for(unsigned int j = 0 ; j < height ; j ++) {
                for(unsigned int i = 0 ; i < width ; i ++) {
                  p[i*3 + 0] = data[i];
                  p[i*3 + 1] = data[i];
                  p[i*3 + 2] = data[i];
                }}
              }
              else if(color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
              {
                SDL_PixelFormatEnumToMasks(
                    SDL_PIXELFORMAT_RGBA32,
                    &bpp, &rmask, &gmask, &bmask, &amask);
                surface_out = SDL_CreateRGBSurface(
                    0, (int)width, (int)height,
                    bpp, rmask, gmask, bmask, amask);

                uint8_t * p = (uint8_t *)surface_out->pixels;

                assert(surface_out->pitch >= row_bytes);

                for(unsigned int j = 0 ; j < height ; j ++) {
                for(unsigned int i = 0 ; i < width ; i ++) {
                  p[i*4 + 0] = data[i*2 + 0];
                  p[i*4 + 1] = data[i*2 + 0];
                  p[i*4 + 2] = data[i*2 + 0];
                  p[i*4 + 3] = data[i*2 + 1];
                }}
              }

              // done!
            } else {
              printf("PNG ERROR: Unsupported color type: %d.\n", color_type);
            }
          } else {
            printf("PNG ERROR: Failed to read png internals. (longjmp).\n");
          }

        } else {
          printf("PNG ERROR: png_create_info_struct() failed.\n");
        }

        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
      } else {
        printf("PNG ERROR: png_create_read_struct() failed.\n");
      }
    } else {
      printf("PNG ERROR: %s is not a PNG file.\n", filename);
    }

    fclose(fp);
    fp = NULL;
  } else {
    printf("PNG ERROR: Could not open PNG file for reading at %s\n", filename);
  }

  return surface_out;
}

