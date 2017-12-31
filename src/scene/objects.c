
#include <util/hash_ul.h>

#include <scene/objects.h>

static hash_ul_t objects;

void scene_objects_unload(void) {
  hash_ul_clear(&objects);
}

void scene_objects_tick(void) {
}

void scene_objects_draw(void) {
}

