#ifndef SCENE_MODEL_H
#define SCENE_MODEL_H

#include <stdint.h>


typedef struct {
  int sx, sy, sw, sh;
  int time_ticks;
  int next_frame_index;
} scene_modeldef_frame_t

typedef struct {
  // definition
  scene_model_frame_t * frames;
  int frame_num;

  int idle_frame_index;
  int walk_frame_index;
  int strike_frame_index;
  int cast_frame_index;
} scene_modeldef_t;


typedef struct {
  const scene_modeldef_t * def;

  int x, y;
  int frame_index;
  int frame_ticks;
} scene_model_t;


void scene_model_set_frame(scene_model_t * model, int index, const scene_model_frame_t * frame);
void scene_model_set_frame_num(scene_model_t * model, int num);

void scene_model_clear(scene_model_t * model);


void scene_model_tick(scene_model_t * model);

void scene_model_draw(
    scene_model_t * model,
    void (* sprite)(int id, int x, int y, int depth, void * ud),
    void * ud);

void scene_model_spawn_particles(
    scene_model_t * model,
    void (* spawn)(int id, int src_x, int src_y, void * ud),
    void * ud);

void scene_model_set_pos(scene_model_t * model, int x, int y)

void scene_model_idle(scene_model_t * model)
void scene_model_walk(scene_model_t * model)
void scene_model_strike(scene_model_t * model)
void scene_model_cast(scene_model_t * model)


#endif
