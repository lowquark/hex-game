
#include <assert.h>

#include <util/hash_ul.h>
#include <scene/sprites.h>

hash_ul_t scene_sprites;

static scene_Sprite ** sorted_sprites;

scene_Sprite * scene_sprite(unsigned long id) {
  scene_Sprite * s = hash_ul_find(&scene_sprites, id);
  if(!s) {
    s = hash_ul_create(&scene_sprites, id, sizeof(scene_Sprite));
  }
  return s;
}
scene_Sprite * scene_getsprite(unsigned long id) {
  return hash_ul_find(&scene_sprites, id);
}
void scene_clearsprite(unsigned long id) {
  hash_ul_destroy(&scene_sprites, id);
}

static void add_to_sorted_sprites(unsigned long id, void * s, void * i) {
  unsigned long * idx = i;
  scene_Sprite * sprite = s;

  sorted_sprites[*idx] = sprite;
  *idx = *idx + 1;;
}

static int compare_sprite_y(const void * s1, const void * s2) {
  const scene_Sprite * sprite1 = *(const scene_Sprite **)s1;
  const scene_Sprite * sprite2 = *(const scene_Sprite **)s2;

  if(sprite1->y < sprite2->y) {
    return -1;
  } else if(sprite1->y > sprite2->y) {
    return 1;
  } else {
    return 0;
  }
}

// allocated once, ends with a sentinel NULL
scene_Sprite ** scene_sortsprites() {
  unsigned long sprite_num = scene_sprites.entry_count;

  // +1 for sentinel
  sorted_sprites = realloc(sorted_sprites, sizeof(sorted_sprites[0])*(sprite_num + 1));

  unsigned long idx = 0;
  hash_ul_each(&scene_sprites, add_to_sorted_sprites, &idx);

  assert(sprite_num == idx);

  // set sentinel
  sorted_sprites[sprite_num] = NULL;

  qsort(sorted_sprites, sprite_num, sizeof(sorted_sprites[0]), compare_sprite_y);

  return sorted_sprites;
}

