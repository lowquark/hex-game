#ifndef GAME_COLOR_H
#define GAME_COLOR_H

typedef struct {
  uint8_t r, g, b;
} game_color_t;

#define GAME_COLOR_FROM24(_color_) { (uint8_t)(((_color_) >> 16) & 0xFF), \
                                     (uint8_t)(((_color_) >>  8) & 0xFF), \
                                     (uint8_t)(((_color_)      ) & 0xFF), }

static inline game_color_t game_color_from24(uint32_t color) {
  return (game_color_t)GAME_COLOR_FROM24(color);
}

#endif
