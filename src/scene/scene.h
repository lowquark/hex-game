#ifndef SCENE_SCENE_H
#define SCENE_SCENE_H

// scene: draw and animate sprites

#include <stdbool.h>
#include <stdint.h>
#include <hex/hex.h>
#include <gfx/gfx.h>

#include <scene/tiles.h>
#include <scene/objects.h>

///////////////////////////
// high-level management //
///////////////////////////

// load required assets to gfx module
void scene_load_assets(void);
// unload loaded assets
void scene_unload_assets(void);


// clears everything
void scene_clear(void);

// update animations
void scene_tick(void);

// draw via gfx module
void scene_draw(void);


///////////////////
// scene queries //
///////////////////

// object given pixel coord
scene_id_t  scene_objectat(int pixel_x, int pixel_y);
// hex tile given pixel coord
hex_vec2i_t scene_hexat(int pixel_x, int pixel_y);


///////////////////////////
// query animation state //
///////////////////////////

// returns 1 if animations are currently in progress
bool scene_isanimating(void);
// skip all animations immediately
void scene_skip_animations(void);


#endif
