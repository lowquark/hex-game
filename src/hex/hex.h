#ifndef HEX_HEX_H
#define HEX_HEX_H

#include <stdlib.h>

typedef struct {
  int x;
  int y;
} hex_vec2i_t;

typedef struct {
  int x;
  int y;
  int z;
} hex_vec3i_t;

inline static int hex_vec2i_eq(hex_vec2i_t p0, hex_vec2i_t p1) {
  return p0.x == p1.x && p0.y == p1.y;
}

inline static hex_vec2i_t hex_up(hex_vec2i_t p) {
  p.y ++;
  return p;
}
inline static hex_vec2i_t hex_down(hex_vec2i_t p) {
  p.y --;
  return p;
}

inline static hex_vec2i_t hex_upright(hex_vec2i_t p) {
  p.x ++;
  return p;
}
inline static hex_vec2i_t hex_downright(hex_vec2i_t p) {
  p.x ++;
  p.y --;
  return p;
}

inline static hex_vec2i_t hex_upleft(hex_vec2i_t p) {
  p.x --;
  p.y ++;
  return p;
}
inline static hex_vec2i_t hex_downleft(hex_vec2i_t p) {
  p.x --;
  return p;
}

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

int hex_bresenham_buf(hex_vec2i_t * outbuf,
                      int outbuf_len,
                      hex_vec2i_t p0,
                      hex_vec2i_t p1);

inline static int hex_distance(hex_vec2i_t p0, hex_vec2i_t p1) {
  int dx = abs(p1.x - p0.x);
  int dy = abs(p1.y - p0.y);
  int dz = abs(-p1.x-p1.y +p0.x+p0.y);
  return (dx + dy + dz) / 2;
}

#endif
