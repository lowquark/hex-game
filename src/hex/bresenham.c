
#include <hex/hex.h>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

// returns # of entries written to outbuf when end is reached
#define OUTBUF_WRITE(_x_) { \
  *outbuf_ptr++ = (_x_); \
  if(outbuf_ptr == outbuf_end) { return (int)(outbuf_ptr - outbuf); } }

int hex_bresenham_buf_h1(hex_vec2i_t * outbuf,
                         int outbuf_len,
                         hex_vec2i_t p0,
                         hex_vec2i_t p1,
                         int abs_cdx,
                         int abs_cdy2) {
  assert(outbuf_len > 0);
  assert(abs_cdy2 >= 0);
  assert(abs_cdx >= 0);
  assert(abs_cdy2 <= abs_cdx);

  // set buffer pos, end
        hex_vec2i_t *       outbuf_ptr = outbuf;
  const hex_vec2i_t * const outbuf_end = outbuf + outbuf_len;

  // start at p0
  hex_vec2i_t current_p = p0;
  OUTBUF_WRITE(current_p);

  int err = 0;

  while(!(current_p.x == p1.x &&
          current_p.y == p1.y)) {
    err = err + abs_cdy2;
    if(err >= 0) {
      current_p = hex_upright(current_p);
      err = err - abs_cdx;
    } else {
      current_p = hex_downright(current_p);
      err = err + abs_cdx;
    }

    OUTBUF_WRITE(current_p);
  }

  return (outbuf_ptr - outbuf);
}
int hex_bresenham_buf_v1(hex_vec2i_t * outbuf,
                         int outbuf_len,
                         hex_vec2i_t p0,
                         hex_vec2i_t p1,
                         int abs_cdx,
                         int abs_cdy2) {
  assert(outbuf_len > 0);
  assert(abs_cdy2 >= 0);
  assert(abs_cdx >= 0);
  assert(abs_cdy2 >= abs_cdx);

  // set buffer pos, end
        hex_vec2i_t *       outbuf_ptr = outbuf;
  const hex_vec2i_t * const outbuf_end = outbuf + outbuf_len;

  // start at p0
  hex_vec2i_t current_p = p0;
  OUTBUF_WRITE(current_p);

  int err = 0;

  while(!hex_vec2i_eq(current_p, p1)) {
    err = err + 3*abs_cdx;

    if(err >= abs_cdy2) {
      current_p = hex_upright(current_p);
      err = err - 3*abs_cdy2;
    } else {
      current_p = hex_up(current_p);
      err = err + 3*abs_cdx;
    }

    OUTBUF_WRITE(current_p);
  }

  return (int)(outbuf_ptr - outbuf);
}
int hex_bresenham_buf_h2(hex_vec2i_t * outbuf,
                         int outbuf_len,
                         hex_vec2i_t p0,
                         hex_vec2i_t p1,
                         int abs_cdx,
                         int abs_cdy2) {
  assert(outbuf_len > 0);
  assert(abs_cdy2 >= 0);
  assert(abs_cdx >= 0);
  assert(abs_cdy2 <= abs_cdx);

  // set buffer pos, end
        hex_vec2i_t *       outbuf_ptr = outbuf;
  const hex_vec2i_t * const outbuf_end = outbuf + outbuf_len;

  // start at p0
  hex_vec2i_t current_p = p0;
  OUTBUF_WRITE(current_p);

  int err = 0;

  while(!hex_vec2i_eq(current_p, p1)) {
    err = err + abs_cdy2;
    if(err >= 0) {
      current_p = hex_upleft(current_p);
      err = err - abs_cdx;
    } else {
      current_p = hex_downleft(current_p);
      err = err + abs_cdx;
    }

    OUTBUF_WRITE(current_p);
  }

  return (int)(outbuf_ptr - outbuf);
}
int hex_bresenham_buf_v2(hex_vec2i_t * outbuf,
                         int outbuf_len,
                         hex_vec2i_t p0,
                         hex_vec2i_t p1,
                         int abs_cdx,
                         int abs_cdy2) {
  assert(outbuf_len > 0);
  assert(abs_cdy2 >= 0);
  assert(abs_cdx >= 0);
  assert(abs_cdy2 >= abs_cdx);

  // set buffer pos, end
        hex_vec2i_t *       outbuf_ptr = outbuf;
  const hex_vec2i_t * const outbuf_end = outbuf + outbuf_len;

  // start at p0
  hex_vec2i_t current_p = p0;
  OUTBUF_WRITE(current_p);

  int err = 0;

  while(!hex_vec2i_eq(current_p, p1)) {
    err = err + 3*abs_cdx;

    if(err >= abs_cdy2) {
      current_p = hex_upleft(current_p);
      err = err - 3*abs_cdy2;
    } else {
      current_p = hex_up(current_p);
      err = err + 3*abs_cdx;
    }

    OUTBUF_WRITE(current_p);
  }

  return (int)(outbuf_ptr - outbuf);
}

int hex_bresenham_buf_h4(hex_vec2i_t * outbuf,
                         int outbuf_len,
                         hex_vec2i_t p0,
                         hex_vec2i_t p1,
                         int abs_cdx,
                         int abs_cdy2) {
  assert(outbuf_len > 0);
  assert(abs_cdy2 >= 0);
  assert(abs_cdx >= 0);
  assert(abs_cdy2 <= abs_cdx);

  // set buffer pos, end
        hex_vec2i_t *       outbuf_ptr = outbuf;
  const hex_vec2i_t * const outbuf_end = outbuf + outbuf_len;

  // start at p0
  hex_vec2i_t current_p = p0;
  OUTBUF_WRITE(current_p);

  int err = 0;

  while(!hex_vec2i_eq(current_p, p1)) {
    err = err + abs_cdy2;
    if(err >= 0) {
      current_p = hex_downright(current_p);
      err = err - abs_cdx;
    } else {
      current_p = hex_upright(current_p);
      err = err + abs_cdx;
    }

    OUTBUF_WRITE(current_p);
  }

  return (int)(outbuf_ptr - outbuf);
}
int hex_bresenham_buf_v4(hex_vec2i_t * outbuf,
                         int outbuf_len,
                         hex_vec2i_t p0,
                         hex_vec2i_t p1,
                         int abs_cdx,
                         int abs_cdy2) {
  assert(outbuf_len > 0);
  assert(abs_cdy2 >= 0);
  assert(abs_cdx >= 0);
  assert(abs_cdy2 >= abs_cdx);

  // set buffer pos, end
        hex_vec2i_t *       outbuf_ptr = outbuf;
  const hex_vec2i_t * const outbuf_end = outbuf + outbuf_len;

  // start at p0
  hex_vec2i_t current_p = p0;
  OUTBUF_WRITE(current_p);

  int err = 0;

  while(!hex_vec2i_eq(current_p, p1)) {
    err = err + 3*abs_cdx;

    if(err >= abs_cdy2) {
      current_p = hex_downright(current_p);
      err = err - 3*abs_cdy2;
    } else {
      current_p = hex_down(current_p);
      err = err + 3*abs_cdx;
    }

    OUTBUF_WRITE(current_p);
  }

  return (int)(outbuf_ptr - outbuf);
}
int hex_bresenham_buf_h3(hex_vec2i_t * outbuf,
                         int outbuf_len,
                         hex_vec2i_t p0,
                         hex_vec2i_t p1,
                         int abs_cdx,
                         int abs_cdy2) {
  assert(outbuf_len > 0);
  assert(abs_cdy2 >= 0);
  assert(abs_cdx >= 0);
  assert(abs_cdy2 <= abs_cdx);

  // set buffer pos, end
        hex_vec2i_t *       outbuf_ptr = outbuf;
  const hex_vec2i_t * const outbuf_end = outbuf + outbuf_len;

  // start at p0
  hex_vec2i_t current_p = p0;
  OUTBUF_WRITE(current_p);

  int err = 0;

  while(!hex_vec2i_eq(current_p, p1)) {
    err = err + abs_cdy2;
    if(err >= 0) {
      current_p = hex_downleft(current_p);
      err = err - abs_cdx;
    } else {
      current_p = hex_upleft(current_p);
      err = err + abs_cdx;
    }

    OUTBUF_WRITE(current_p);
  }

  return (int)(outbuf_ptr - outbuf);
}
int hex_bresenham_buf_v3(hex_vec2i_t * outbuf,
                         int outbuf_len,
                         hex_vec2i_t p0,
                         hex_vec2i_t p1,
                         int abs_cdx,
                         int abs_cdy2) {
  assert(outbuf_len > 0);
  assert(abs_cdy2 >= 0);
  assert(abs_cdx >= 0);
  assert(abs_cdy2 >= abs_cdx);

  // set buffer pos, end
        hex_vec2i_t *       outbuf_ptr = outbuf;
  const hex_vec2i_t * const outbuf_end = outbuf + outbuf_len;

  // start at p0
  hex_vec2i_t current_p = p0;
  OUTBUF_WRITE(current_p);

  int err = 0;

  while(!hex_vec2i_eq(current_p, p1)) {
    err = err + 3*abs_cdx;

    if(err >= abs_cdy2) {
      current_p = hex_downleft(current_p);
      err = err - 3*abs_cdy2;
    } else {
      current_p = hex_down(current_p);
      err = err + 3*abs_cdx;
    }

    OUTBUF_WRITE(current_p);
  }

  return (int)(outbuf_ptr - outbuf);
}

int hex_bresenham_buf(hex_vec2i_t * outbuf,
                      int outbuf_len,
                      hex_vec2i_t p0,
                      hex_vec2i_t p1) {
  if(outbuf_len == 0) { return 0; }

  // cx, cy in units of tile size

  // cartesian delta y * 2
  int cdy2 = 2 * (p1.y - p0.y) + p1.x - p0.x;
  // cartesian delta x
  int cdx = p1.x - p0.x;

  //printf("p0.x: %d  p0.y: %d\n", p0.x, p0.y);
  //printf("p1.x: %d  p1.y: %d\n", p1.x, p1.y);
  //printf("cdx: %d  cdy2: %d\n", cdx, cdy2);

  if(cdx >= 0) {
    if(cdy2 >= 0) {
      // first quadrant
      if(cdx >= cdy2) {
        // horizontally dominant line
        return hex_bresenham_buf_h1(outbuf, outbuf_len, p0, p1, cdx, cdy2);
      } else {
        // vertically dominant line
        return hex_bresenham_buf_v1(outbuf, outbuf_len, p0, p1, cdx, cdy2);
      }
    } else {
      // fourth quadrant
      if(cdx >= -cdy2) {
        // horizontally dominant line
        return hex_bresenham_buf_h4(outbuf, outbuf_len, p0, p1, cdx, -cdy2);
      } else {
        // vertically dominant line
        return hex_bresenham_buf_v4(outbuf, outbuf_len, p0, p1, cdx, -cdy2);
      }
    }
  } else {
    if(cdy2 >= 0) {
      // second quadrant
      if(-cdx >= cdy2) {
        // horizontally dominant line
        return hex_bresenham_buf_h2(outbuf, outbuf_len, p0, p1, -cdx, cdy2);
      } else {
        // vertically dominant line
        return hex_bresenham_buf_v2(outbuf, outbuf_len, p0, p1, -cdx, cdy2);
      }
    } else {
      // third quadrant
      if(-cdx >= -cdy2) {
        // horizontally dominant line
        return hex_bresenham_buf_h3(outbuf, outbuf_len, p0, p1, -cdx, -cdy2);
      } else {
        // vertically dominant line
        return hex_bresenham_buf_v3(outbuf, outbuf_len, p0, p1, -cdx, -cdy2);
      }
    }
  }

  return 0;
}

#undef OUTBUF_WRITE
