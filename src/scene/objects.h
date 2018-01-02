#ifndef SCENE_OBJECTS_H
#define SCENE_OBJECTS_H

#include <hex/hex.h>

#include <scene/id.h>
#include <scene/object.h>


// unload all objects immediately
void scene_objects_clear(void);

// update all objects by one tick
void scene_objects_tick(void);

// draw all objects
void scene_objects_draw_sprites(void);


// retrieve a loaded object
// returns NULL if not loaded
scene_object_t * scene_objects_get(scene_id_t id);

// load a object, overwrite existing state if one already exists
scene_object_t * scene_objects_load(scene_id_t id, const scene_object_state_t * state);

// unload immediately
void             scene_objects_unload(scene_id_t id);


#endif
