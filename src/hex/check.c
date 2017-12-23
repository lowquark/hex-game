
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hex.h"

static void test_bresenham(int x0, int y0, int x1, int y1) {
  hex_vec2i_t src = { x0, y0 };
  hex_vec2i_t dst = { x1, y1 };

  int expected_len = hex_distance(src, dst);

  hex_vec2i_t bbuf[32];
  unsigned long n;

  n = (unsigned long)hex_bresenham_buf(bbuf, 32, src, dst);

  ck_assert_uint_gt(n,  0);
  ck_assert_uint_le(n, 32);

  ck_assert_uint_eq(n, expected_len + 1);

  ck_assert_int_eq(src.x, bbuf[0].x);
  ck_assert_int_eq(src.y, bbuf[0].y);

  ck_assert_int_eq(dst.x, bbuf[n - 1].x);
  ck_assert_int_eq(dst.y, bbuf[n - 1].y);

  for(unsigned long i = 0 ; i < n ; i ++) {
    int x = bbuf[i].x;
    int y = bbuf[i].y;
    ck_assert((src.x <= x && x <= dst.x) ||
              (src.x >= x && x >= dst.x));
    ck_assert((src.y <= y && y <= dst.y) ||
              (src.y >= y && y >= dst.y));
  }

  /*
#define MAP_WIDTH  6
#define MAP_HEIGHT 6

  char tilebuf[MAP_WIDTH][MAP_HEIGHT];
  memset(tilebuf, '.', sizeof(tilebuf));

  hex_vec2i_t bbuf[20];
  unsigned long n;

  printf("\npoints:\n-------\n");
  n = hex_bresenham_buf(bbuf, 20, src, dst);
  for(unsigned long i = 0 ; i < n ; i ++) {
    printf("%d, %d\n", bbuf[i].x, bbuf[i].y);
    int x = bbuf[i].x;
    int y = bbuf[i].y;
    if(x >= 0 && x < MAP_WIDTH &&
       y >= 0 && y < MAP_HEIGHT) {
      tilebuf[x][y] = '+';
    }
  }

  printf("\nmap:\n----\n");
  for(long yrow = 0 ; yrow <= 15 ; yrow ++) {
    for(long xcol = -1 ; xcol <= 7 ; xcol ++) {
      if(labs(xcol % 2) == labs(yrow % 2)) {
        long x = xcol;
        long y = (yrow - xcol) / 2;
        if(x >= 0 && x < MAP_WIDTH &&
           y >= 0 && y < MAP_HEIGHT) {
          printf(" %c ", tilebuf[x][y]);
        } else {
          printf("   ");
        }
      } else {
        printf("   ");
      }
    }
    printf("\n");
  }
  printf("\n");
  */

  /*
  printf("\nreference:\n----------\n");
  for(long yrow = 0 ; yrow <= 15 ; yrow ++) {
    for(long xcol = -1 ; xcol <= 7 ; xcol ++) {
      if(labs(xcol % 2) == labs(yrow % 2)) {
        long x = xcol;
        long y = (yrow - xcol) / 2;
        if(x >= 0 && x < MAP_WIDTH &&
           y >= 0 && y < MAP_HEIGHT) {
          printf("{%3ld,%3ld}", x, y);
        } else {
          printf(" %3ld,%3ld ", x, y);
        }
      } else {
        printf("         ");
      }
    }
    printf("\n\n");
  }
  printf("\n");
  */
}

START_TEST(hex_directional_inverses) {
  for(int i = 0 ; i < 100 ; i ++) {
    hex_vec2i_t p;
    p.x = (rand() % 40001) - 20000;
    p.y = (rand() % 40001) - 20000;
    ck_assert(hex_vec2i_eq(p, hex_upleft(hex_downright(p))));
    ck_assert(hex_vec2i_eq(p, hex_upright(hex_downleft(p))));
    ck_assert(hex_vec2i_eq(p, hex_up(hex_down(p))));
  }
}
END_TEST

START_TEST(hex_directional_path) {
  srand((unsigned int)time(NULL));

  hex_vec2i_t p = { 0, 0 };
  p = hex_up(p);
  p = hex_down(p);
  p = hex_upright(p);
  p = hex_upleft(p);
  p = hex_upright(p);
  p = hex_upleft(p);
  p = hex_upright(p);
  p = hex_upright(p);
  p = hex_downright(p);
  p = hex_downleft(p);
  p = hex_downleft(p);
  p = hex_downleft(p);

  ck_assert_int_eq(p.x, 0);
  ck_assert_int_eq(p.y, 1);
}
END_TEST

START_TEST(hex_distances) {
  hex_vec2i_t p0 = { 0, 0 };
  hex_vec2i_t p1 = { 1, 1 };

  int dist = hex_distance(p0, p1);

  ck_assert_int_eq(dist, 2);

  // along y = 0
  p0.x = 0;
  p0.y = 0;
  p1.x = 0;
  p1.y = 0;

  for(int i = 0 ; i < 100 ; i ++) {
    p0.x = (rand() % 40001) - 20000;

    int dist = hex_distance(p0, p1);

    ck_assert_int_eq(dist, abs(p0.x));
  }

  // along x = 0
  p0.x = 0;
  p0.y = 0;
  p1.x = 0;
  p1.y = 0;

  for(int i = 0 ; i < 100 ; i ++) {
    p0.y = (rand() % 40001) - 20000;

    int dist = hex_distance(p0, p1);

    ck_assert_int_eq(dist, abs(p0.y));
  }

  // along z = 0
  p0.x = 0;
  p0.y = 0;
  p1.x = 0;
  p1.y = 0;

  for(int i = 0 ; i < 100 ; i ++) {
    p0.x = (rand() % 40001) - 20000;
    p0.y = -p0.x;

    int dist = hex_distance(p0, p1);

    ck_assert_int_eq(dist, abs(p0.x));
  }
}
END_TEST

START_TEST(hex_bresenham) {
  test_bresenham(0, 0, 5, 5);
  test_bresenham(5, 0, 2, 3);
  test_bresenham(5, 4, 3, 1);
  test_bresenham(0, 5, 2, 0);

  for(int i = -10 ; i <= 10 ; i ++) {
    // radially outward
    test_bresenham(  0,  0,  0,  i);
    test_bresenham(  0,  0,  i,  0);
    test_bresenham(  0,  0,  0, -i);
    test_bresenham(  0,  0, -i,  0);
    test_bresenham(  0,  0,  i, -i);
    test_bresenham(  0,  0, -i,  i);

    // corner to corner
    test_bresenham( -i,  i,  0,  i);
    test_bresenham(  0,  i,  i,  0);
    test_bresenham(  i,  0,  0, -i);
    test_bresenham(  0, -i, -i,  0);
    test_bresenham( -i,  0,  i, -i);
    test_bresenham(  i, -i, -i,  i);
  }
}
END_TEST

Suite * hex_check_suite(void) {
  Suite * suite = suite_create("hex module");
  TCase * test_case;

  // test directional functionality
  test_case = tcase_create("core");
  tcase_add_test(test_case, hex_directional_inverses);
  tcase_add_test(test_case, hex_directional_path);
  tcase_add_test(test_case, hex_distances);
  suite_add_tcase(suite, test_case);

  test_case = tcase_create("bresenham");
  tcase_add_test(test_case, hex_bresenham);
  suite_add_tcase(suite, test_case);

  return suite;
}

