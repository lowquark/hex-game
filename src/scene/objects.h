#ifndef SCENE_OBJECTS_H
#define SCENE_OBJECTS_H

#include <hex/hex.h>

#include <gfx/gfx.h>

#include <scene/id.h>


// unload all objects
void scene_objects_unload(void);

// update all objects by one tick
void scene_objects_tick(void);

// draw all objects
void scene_objects_draw(void);


#endif
