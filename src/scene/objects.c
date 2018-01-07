
#include <assert.h>

#include <util/hash_ul.h>
#include <util/list.h>

#include <scene/objects.h>
#include <scene/view.h>

static hash_ul_t object_hash;
static list_t object_list;

static scene_object_t * goc_object(scene_id_t id) {
  scene_object_t * obj = hash_ul_get(&object_hash, id);

  if(obj == NULL) {
    obj = calloc(sizeof(*obj), 1);

    // save in hash
    hash_ul_set(&object_hash, id, obj);
    // store in master list
    list_append(&object_list, obj);
  }

  assert(obj != NULL);

  return obj;
}
static void destroy_object(scene_id_t id, scene_object_t * obj) {
  // deinit
  scene_object_clear(obj);
  // free
  free(obj);

  // forget
  hash_ul_set(&object_hash, id, NULL);

  // find in list and erase
  list_node_t * lo = list_begin(&object_list);

  while(lo) {
    if(list_getvalue(lo) == obj) {
      list_erase(lo);
      break;
    }

    lo = list_next(lo);
  }
}

void scene_objects_clear(void) {
  // free all objects
  list_each(&object_list, free);
  // forget all objects
  hash_ul_clear(&object_hash);
  list_clear(&object_list);
}

void scene_objects_tick(void) {
  list_node_t * lo = list_begin(&object_list);

  while(lo) {
    scene_object_t * obj = list_getvalue(lo);

    scene_object_tick(obj);

    lo = list_next(lo);
  }
}

void scene_objects_draw_sprites(void) {
  extern gfx_Sprite hero_sprite;

  list_node_t * lo = list_begin(&object_list);

  while(lo) {
    scene_object_t * obj = list_getvalue(lo);

    gfx_draw_sprite(&hero_sprite, obj->x, obj->y, &obj->color);

    lo = list_next(lo);
  }
}

scene_object_t * scene_objects_get(scene_id_t id) {
  return hash_ul_get(&object_hash, id);
}

scene_object_t * scene_objects_load(scene_id_t id, const scene_object_state_t * state) {
  scene_object_t * obj = goc_object(id);

  assert(obj);

  scene_object_setstate(obj, state);

  return obj;
}

void scene_objects_unload(scene_id_t id) {
  scene_object_t * obj = hash_ul_get(&object_hash, id);

  if(obj) {
    destroy_object(id, obj);
  }
}

