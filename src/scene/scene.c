
#include <assert.h>

#include <hex/hex.h>
#include <util/hash_2i.h>
#include <util/hash_ul.h>
#include <util/list.h>
#include <gfx/gfx.h>

#include <scene/scene.h>
#include <scene/view.h>
#include <scene/sprites.h>
#include <scene/objects.h>
#include <scene/tiles.h>


//static hex_vec2i_t selected_hex;

void scene_load_assets() {
  scene_unload_assets();

  scene_sprites_load();
}
void scene_unload_assets(void) {
  scene_sprites_unload();
}


void scene_clear(void) {
  scene_tiles_clear();
  scene_objects_clear();
}

void scene_tick(void) {
  scene_tiles_tick();
  scene_objects_tick();
}

void scene_draw(void) {
  SDL_Rect whole_window;
  whole_window.x = 0;
  whole_window.y = 0;
  whole_window.w = 640;
  whole_window.h = 480;

  int imin, imax, jmin, jmax;
  scene_view_hexlimits_ij(&imin, &imax, &jmin, &jmax, whole_window.w, whole_window.h);

  gfx_Color bg_color = { 0x11, 0x11, 0x11, 0xFF };
  gfx_clear(&bg_color);

  scene_tiles_draw(imin, imax, jmin, jmax);

  scene_objects_draw_sprites();
}


scene_id_t scene_objectat(int pixel_x, int pixel_y) {
  return 0;
}
hex_vec2i_t scene_hexat(int pixel_x, int pixel_y) {
  hex_vec2i_t h;
  h.x = 0;
  h.y = 0;
  return h;
}

bool scene_isanimating(void) {
  return false;
}
void scene_skip_animations(void) {
}

