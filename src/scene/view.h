#ifndef SCENE_VIEW_H
#define SCENE_VIEW_H

#include <hex/hex.h>

void scene_view_hexlimits_ij(int * imin, int * imax,
                             int * jmin, int * jmax,
                             int windowsize_x, int windowsize_y);

void scene_view_tilecenter(int * tile_x_pix, int * tile_y_pix, hex_vec2i_t hex);

#endif
