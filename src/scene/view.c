
#include <assert.h>

#include <scene/view.h>

static const int tile_spacing_x_pixels = 23;
static const int tile_spacing_y_pixels = 20;
static const int tile_stagger_y_pixels = tile_spacing_y_pixels / 2;

void scene_view_hexlimits_ij(int * imin, int * imax,
                             int * jmin, int * jmax,
                             int windowsize_x, int windowsize_y) {
  assert(imin);
  assert(imax);
  assert(jmin);
  assert(jmax);

  *imin = -windowsize_x/2 / tile_spacing_x_pixels - 1;
  *imax =  windowsize_x/2 / tile_spacing_x_pixels + 1;
  *jmin = -windowsize_y/2 / tile_spacing_y_pixels;
  *jmax =  windowsize_y/2 / tile_spacing_y_pixels;
}

void scene_view_tilecenter(int * tile_x_pix, int * tile_y_pix, hex_vec2i_t hex) {
  assert(tile_x_pix);
  assert(tile_y_pix);

  *tile_x_pix = hex.x * tile_spacing_x_pixels + 320;
  *tile_y_pix = hex.y * tile_spacing_y_pixels + 240 + hex.x * tile_stagger_y_pixels;
}

