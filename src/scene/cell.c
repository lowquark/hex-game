
#include <assert.h>

#include <scene/cell.h>

#define ZERO(x) memset(&x, 0, sizeof(x))

static void scene_cell_clear(scene_cell_t * cell) {
  assert(cell);
  free(cell->mobs);
  free(cell->items);
  ZERO(*cell);
}
static void scene_cell_clear_mobs(scene_cell_t * cell) {
  assert(cell);
  free(cell->mobs);
  cell->mobs = NULL;
  cell->mob_num = 0;
}
static void scene_cell_clear_items(scene_cell_t * cell) {
  assert(cell);
  free(cell->items);
  cell->items = NULL;
  cell->item_num = 0;
}
static void scene_cell_alloc_mobs(scene_cell_t * cell, int mob_num) {
  assert(cell);
  assert(mob_num > 0);
  free(cell->mobs);
  cell->mobs = calloc(sizeof(scene_mob_t), (unsigned long)mob_num);
  cell->mob_num = mob_num;
}
static void scene_cell_alloc_items(scene_cell_t * cell, int item_num) {
  assert(cell);
  assert(item_num > 0);
  free(cell->items);
  cell->items = calloc(sizeof(scene_item_t), (unsigned long)item_num);
  cell->item_num = item_num;
}
static void scene_cell_set_mob(scene_cell_t * cell, int idx, const scene_mob_t * mob) {
  assert(cell);
  assert(idx >= 0 && idx < cell->mob_num);
  assert(mob);
  cell->mobs[idx] = *mob;
}
static void scene_cell_set_item(scene_cell_t * cell, int idx, const scene_item_t * item) {
  assert(cell);
  assert(idx >= 0 && idx < cell->item_num);
  assert(item);
  cell->items[idx] = *item;
}

