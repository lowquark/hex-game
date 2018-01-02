
#include <assert.h>

#include <util/hash_ul.h>
#include <util/list.h>

#include <scene/objects.h>
#include <scene/view.h>

static hash_ul_t object_hash;
static list_t object_list;

void scene_objects_clear(void) {
  hash_ul_clear(&object_hash);
  list_clear(&object_list);
}

void scene_objects_tick(void) {
}

void scene_objects_draw_sprites(void) {
  extern gfx_Sprite hero_sprite;

  list_node_t * lo = list_begin(&object_list);

  while(lo) {
    scene_object_t * obj = list_getvalue(lo);

    int x, y;
    scene_view_tilecenter(&x, &y, obj->pos);

    gfx_Color c;
    c.r = 0xFF;
    c.g = 0xFF;
    c.b = 0xFF;
    c.a = 0xFF;
    gfx_draw_sprite(&hero_sprite, x, y, &c);

    lo = list_next(lo);
  }
}

static scene_object_t * new_object(scene_id_t id) {
  scene_object_t * obj = hash_ul_create(&object_hash, id, sizeof(scene_object_t));

  assert(obj);

  list_append(&object_list, obj);

  return obj;
}

// retrieves the object for the given id
// creates if it doesn't already exist
scene_object_t * scene_objects_get(scene_id_t id) {
  scene_object_t * obj = hash_ul_find(&object_hash, id);

  if(obj) {
    return obj;
  } else {
    return new_object(id);
  }
}

