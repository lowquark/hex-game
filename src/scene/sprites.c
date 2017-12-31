
#include <assert.h>

#include <util/hash_ul.h>
#include <asset/png.h>

#include <scene/sprites.h>

scene_sprite_list_t sprites;
long sprite_num;

static gfx_SpriteSheet * tiles = NULL;
gfx_Sprite single_tile_sprite;
static gfx_Sprite grass_tile_sprite;
static gfx_Sprite hero_sprite;
static gfx_Sprite wall_sprite;

/*
static void ll_remove(scene_sprite_list_t * this) {
  this->prev->next = this->next;
  this->next->prev = this->prev;
  this->next = this;
  this->prev = this;
  this->head = this;
}
static void ll_insert_after(scene_sprite_list_t * this, scene_sprite_list_t * other) {
  ll_remove(this);
  this->prev = other;
  this->next = other->next;
  other->next = this;
  this->next->prev = this;
  this->head = other->head;
}
static scene_sprite_list_t * ll_next(scene_sprite_list_t * this) {
  if(this->next != this->head) {
    return this->next;
  } else {
    return NULL;
  }
}

static int compare_sprite_y(const void * s1, const void * s2) {
  const scene_sprite_t * sprite1 = *(const scene_sprite_t **)s1;
  const scene_sprite_t * sprite2 = *(const scene_sprite_t **)s2;

  if(sprite1->y < sprite2->y) {
    return -1;
  } else if(sprite1->y > sprite2->y) {
    return 1;
  } else {
    if(sprite1->x < sprite2->x) {
      return 1;
    } else if(sprite1->x > sprite2->x) {
      return -1;
    } else {
      return 0;
    }
  }
}
*/

void scene_sprites_load() {
  SDL_Surface * tiles_surface = asset_png_load("test.png");

  if(tiles_surface) {
    tiles = gfx_load_spritesheet(tiles_surface);

    single_tile_sprite = gfx_sprite(tiles,  0,  0, 28, 20, 14, 10);
    grass_tile_sprite  = gfx_sprite(tiles, 28,  0, 28, 20, 14, 10);
    hero_sprite        = gfx_sprite(tiles,  0, 20, 20, 20, 10, 15);
    wall_sprite        = gfx_sprite(tiles, 29, 26, 28, 25, 14, 15);

    SDL_FreeSurface(tiles_surface);
    tiles_surface = NULL;
  }
}
void scene_sprites_unload() {
  gfx_unload_spritesheet(tiles);
  tiles = NULL;
}

void scene_sprites_draw() {
  /*
  scene_sprite_list_t * spr = ll_next(&sprites);

  scene_sprite_t * sorted_sprites[sprite_num];

  extern gfx_Sprite hero_sprite;

  long i = 0;

  while(spr) {
    sorted_sprites[i ++] = spr->owner;
    spr = ll_next(spr);
  }

  qsort(sorted_sprites, (size_t)sprite_num, sizeof(sorted_sprites[0]), compare_sprite_y);

  for(i = 0 ; i < sprite_num ; i ++) {

    scene_sprite_t * spr = sorted_sprites[i];
    gfx_Color c = spr->color;

    if(spr->sprite_id == SCENE_SPRITE_TILE_SOLID) {
      gfx_draw_sprite(&single_tile_sprite, spr->x, spr->y, &c);
    } else if(spr->sprite_id == SCENE_SPRITE_TILE_DITHER_0) {
      gfx_draw_sprite(&grass_tile_sprite, spr->x, spr->y, &c);
    } else if(spr->sprite_id == SCENE_SPRITE_HERO) {
      gfx_draw_sprite(&hero_sprite, spr->x, spr->y, &c);
    }
  }
  */
}

