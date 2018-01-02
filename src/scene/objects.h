#ifndef SCENE_OBJECTS_H
#define SCENE_OBJECTS_H

#include <hex/hex.h>
#include <gfx/gfx.h>

#include <scene/id.h>
#include <scene/object.h>


// unload all objects immediately
void scene_objects_clear(void);

// update all objects by one tick
void scene_objects_tick(void);

// draw all objects
void scene_objects_draw_sprites(void);

// retrieves the object for the given id
// creates if it doesn't already exist
scene_object_t * scene_objects_get(scene_id_t id);


#endif
