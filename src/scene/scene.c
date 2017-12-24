
#include <assert.h>

#include <util/hash_2i.h>
#include <util/hash_ul.h>

#include <scene/scene.h>
#include <scene/tiles.h>

void scene_clear(void) {
  scene_tiles_unload();
}

