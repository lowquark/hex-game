
#include <assert.h>

#include <scene/object.h>
#include <scene/view.h>

static const int MOVE_TICKS = 4;

void scene_object_tick(scene_object_t * obj) {
  assert(obj);

  int x0, y0, x1, y1;
  int lerp;

  scene_view_tilecenter(&x0, &y0, obj->pos);

  if(obj->anim_count > 1) {
    scene_view_tilecenter(&x1, &y1, obj->target_pos);

    lerp = MOVE_TICKS - obj->anim_count + 1;

    obj->x = x0 + lerp * (x1 - x0) / MOVE_TICKS;
    obj->y = y0 + lerp * (y1 - y0) / MOVE_TICKS;

    obj->anim_count --;
  } else if(obj->anim_count == 1) {
    obj->pos = obj->target_pos;

    scene_view_tilecenter(&x0, &y0, obj->pos);

    obj->x = x0;
    obj->y = y0;

    obj->anim_count --;
  } else {
    obj->x = x0;
    obj->y = y0;
  }
}
void scene_object_draw(scene_object_t * obj) {
  assert(obj);
}

int scene_object_isanimating(scene_object_t * obj) {
  assert(obj);

  return obj->anim_count > 0;
}
void scene_object_skipanimation(scene_object_t * obj) {
  assert(obj);

  if(obj->anim_count > 0) {
    obj->pos = obj->target_pos;
    obj->anim_count = 0;
  }
}


void scene_object_setstate(scene_object_t * obj, const scene_object_state_t * state) {
  assert(obj);

  obj->pos = state->pos;
  obj->onfire = state->onfire;
  obj->color = state->color;

  obj->target_pos = state->pos;

  obj->x = 0;
  obj->y = 0;
  obj->depth = 0;

  obj->anim_count = 0;
}
void scene_object_clear(scene_object_t * obj) {
  assert(obj);
}


void scene_object_spawn(scene_object_t * obj, int type) {
  assert(obj);
}
void scene_object_despawn(scene_object_t * obj, int type) {
  assert(obj);
}

void scene_object_move(scene_object_t * obj, hex_vec2i_t dst) {
  assert(obj);

  obj->anim_count = MOVE_TICKS;
  obj->target_pos = dst;
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

