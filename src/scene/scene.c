
#include <assert.h>

#include <scene/scene.h>
#include <util/hash_2i.h>
#include <util/hash_ul.h>

typedef struct {
  hex_vec2i_t hex;
  int pixel_x, pixel_y;
  scene_Id sprite_id;
  int animation;
} Object;

hash_2i_t scene_tile_hash;
hash_ul_t scene_object_hash;


scene_Id scene_createobject() {
  return 0;
}
void scene_destroyobject(scene_Id id) {
}


void scene_clear(void) {
  scene_cleartiles();
  scene_clearobjects();
}
void scene_cleartiles(void) {
  hash_2i_clear(&scene_tile_hash);
}
void scene_clearobjects(void) {
  hash_ul_clear(&scene_object_hash);
}

void scene_settilesprite(hex_vec2i_t hex, const scene_TileSprite * spr) {
  if(spr) {
    // find tile
    scene_TileSprite * tilesprite = hash_2i_find(&scene_tile_hash, hex.x, hex.y);

    if(tilesprite == NULL) {
      // create new
      tilesprite = hash_2i_create(&scene_tile_hash, hex.x, hex.y, sizeof(*tilesprite));
    }

    *tilesprite = *spr;
  } else {
    hash_2i_destroy(&scene_tile_hash, hex.x, hex.y);
  }
}

void scene_setpos(scene_Id eid, hex_vec2i_t pos) {
}
void scene_setsprite(scene_Id eid, scene_Id sprite_id) {
}

void scene_moveanimation(scene_Id eid, hex_vec2i_t hex, int ticks) {
}
void scene_strikeanimation(scene_Id eid, hex_vec2i_t hex, int ticks) {
}

int scene_ticksremaining(void) {
  return 0;
}

