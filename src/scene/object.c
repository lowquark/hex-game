
#include <assert.h>

#include <scene/object.h>

void scene_object_tick(scene_object_t * obj) {
  assert(obj);
}
void scene_object_draw(scene_object_t * obj) {
  assert(obj);
}

int scene_object_animating(scene_object_t * obj) {
  assert(obj);
  return 0;
}


void scene_object_load(scene_object_t * obj, const scene_object_state_t * state) {
  assert(obj);

  obj->pos = state->pos;
  obj->onfire = state->onfire;
  obj->color = state->color;
}
void scene_object_clear(scene_object_t * obj) {
  assert(obj);
}


void scene_object_spawn(scene_object_t * obj, int type, const scene_object_state_t * state) {
  assert(obj);
}
void scene_object_despawn(scene_object_t * obj, int type) {
  assert(obj);
}

void scene_object_move(scene_object_t * obj, hex_vec2i_t src, hex_vec2i_t dst) {
  assert(obj);
}

void scene_object_strike(scene_object_t * obj, hex_vec2i_t dst) {
  assert(obj);
}

void scene_object_ignite(scene_object_t * obj) {
  assert(obj);
}
void scene_object_extingquish(scene_object_t * obj) {
  assert(obj);
}

