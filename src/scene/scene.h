#ifndef SCENE_SCENE_H
#define SCENE_SCENE_H

// scene: draw and animate sprites

#include <stdbool.h>
#include <stdint.h>
#include <hex/hex.h>
#include <gfx/gfx.h>


typedef uint_fast32_t scene_Id;

#define SCENE_ID_MAX UINT32_MAX


typedef struct {
  scene_Id id;
  gfx_Color color;
} scene_TileSprite;

// load required assets to gfx module
void scene_load_sprites(void);
// unload loaded assets
void scene_unload_sprites(void);

// creates an object, returns a reference id
scene_Id scene_createobject(void);
// destroys an object by reference id
void scene_destroyobject(scene_Id id);

//// clearing ////

// clears everything
void scene_clear(void);
// sets all tiles to sprite 0
void scene_cleartiles(void);
// deletes all objects, all objects' reference ids are invalidated
void scene_clearobjects(void);

//// set state directly ////

// tile state
void scene_settilesprite(hex_vec2i_t hex, const scene_TileSprite * spr);

// set position
void scene_setpos(scene_Id eid, hex_vec2i_t pos);
// set sprite
void scene_setsprite(scene_Id eid, scene_Id sprite_id);

//// animated state changes ////
//
// an object may only have one animation at a time
// new animations skip old ones immediately

// set the position and animate movement to it for the given number of ticks
void scene_moveanimation(scene_Id eid, hex_vec2i_t hex, int ticks);
// show a strike animation toward the given tile for the given number of ticks
void scene_strikeanimation(scene_Id eid, hex_vec2i_t hex, int ticks);

// # of remaining ticks until animations are finished
int  scene_ticksremaining(void);
// skip all animations immediately
void scene_skipanimations(void);

// update animations
void scene_tick(void);
// draw via gfx module
void scene_draw(void);

// object given pixel coord
scene_Id    scene_objectat(int pixel_x, int pixel_y);
// hex tile given pixel coord
hex_vec2i_t scene_hexat(int pixel_x, int pixel_y);


#endif
