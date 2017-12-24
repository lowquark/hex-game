#ifndef SCENE_OBJECTS_H
#define SCENE_OBJECTS_H

#include <hex/hex.h>

#include <scene/id.h>

typedef struct {
  hex_vec2i_t pos;
  unsigned int onfire : 1;
} scene_object_state_t;

#define SCENE_OBJECT_STATE_NULL { { 0, 0 }, 0 }

////////////////////////
// set state directly //
////////////////////////

// object state is overwritten if already loaded
void scene_object_load(scene_id_t oid, const scene_object_state_t * state);
// unload an object
void scene_object_unload(scene_id_t oid);

/////////////////////////
// set state via event //
/////////////////////////

// reveal & spawn object via animation
// object state is overwritten if already loaded
void scene_object_spawn(scene_id_t oid, int type, const scene_object_state_t * state);
// hide & despawn object via animation
void scene_object_despawn(scene_id_t oid, int type);

// show object moving from src to dst
void scene_object_move(scene_id_t oid, hex_vec2i_t src, hex_vec2i_t dst);

// show object striking dst
void scene_object_strike(scene_id_t oid, hex_vec2i_t dst);

// show object exploding into flames
void scene_object_ignite(scene_id_t oid);
// show object smoking and cooling off
void scene_object_extingquish(scene_id_t oid);

#endif
