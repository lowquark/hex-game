#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include <hex/hex.h>

#include <gfx/gfx.h>


///////////
// types //
///////////

typedef struct {
  hex_vec2i_t pos;
  unsigned int onfire : 1;
  gfx_Color color;
} scene_object_state_t;

#define SCENE_OBJECT_STATE_NULL { { 0, 0 }, 0, { 0x00, 0x00, 0x00, 0x00 } }

typedef struct {
  hex_vec2i_t pos;
  unsigned int onfire : 1;
  gfx_Color color;

  hex_vec2i_t target_pos;

  int x, y;
  int depth;

  int anim_count;
} scene_object_t;

#define SCENE_OBJECT_NULL { { 0, 0 }, 0, { 0x00, 0x00, 0x00, 0x00 }, { 0, 0 }, 0, 0, 0, 0 }


////////////////////////
// high-level control //
////////////////////////

// update by one tick
void scene_object_tick(scene_object_t * obj);
// draw this object
void scene_object_draw(scene_object_t * obj);

// query whether object is animating
int scene_object_isanimating(scene_object_t * obj);
// skip current animation
void scene_object_skipanimation(scene_object_t * obj);


////////////////////////
// set state directly //
////////////////////////

// animations are reset
void scene_object_setstate(scene_object_t * obj, const scene_object_state_t * state);

void scene_object_clear(scene_object_t * obj);


/////////////////////////
// set state via event //
/////////////////////////

// reveal & spawn object via animation
void scene_object_spawn(scene_object_t * obj, int type);
// hide & despawn object via animation
void scene_object_despawn(scene_object_t * obj, int type);

// show object moving from src to dst
void scene_object_move(scene_object_t * obj, hex_vec2i_t dst);

// show object striking dst
void scene_object_strike(scene_object_t * obj, hex_vec2i_t dst);

// show object exploding into flames
void scene_object_ignite(scene_object_t * obj);
// show object smoking and cooling off
void scene_object_extingquish(scene_object_t * obj);


#endif
