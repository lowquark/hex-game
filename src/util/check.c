
#include <check.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include <util/hash2d.h>

#define PRINTF(...)
//#define PRINTF(...) printf(__VA_ARGS__)

#define ZERO(_item_) \
  memset(&_item_, 0, sizeof(_item_))

static void hash2d_single_run(hash2d_t * hash) {
  struct test_entry_t {
    uint32_t salt;
    int x, y;
    uint32_t * data;
  };
  struct test_entry_t tests[100];

  // set several entries in the hash
  for(int i = 0 ; i < 100 ; i ++) {
    uint32_t salt = (uint32_t)rand();

    // note: impossible to have duplicates, but still very sparse
    int x = 100 * i + (rand() % 100);
    int y = 100 * i + (rand() % 100);

    uint32_t * data = (uint32_t *)hash2d_alloc(hash, x, y, sizeof(uint32_t));

    ck_assert_ptr_nonnull(data);

    *data = salt;

    tests[i].salt = salt;
    tests[i].x = x;
    tests[i].y = y;
    tests[i].data = data;

    PRINTF("[alloc]  pos: %d, %d  salt: %08X  data: %p\n", x, y, salt, (void *)tests[i].data);
  }

  // affirm that data is intact, pointers match those initially returned
  for(int i = 0 ; i < 100 ; i ++) {
    int x = tests[i].x;
    int y = tests[i].y;

    uint32_t * data = (uint32_t *)hash2d_get(hash, x, y);

    PRINTF("[get]  pos: %d, %d  data: %p\n", x, y, (void *)data);

    ck_assert_ptr_nonnull(data);
    ck_assert_ptr_eq(data, tests[i].data);
    ck_assert_uint_eq(*data, tests[i].salt);
  }

  // erase several entries
  for(int i = 0 ; i < 100 ; i ++) {
    int x = tests[i].x;
    int y = tests[i].y;

    if((rand() % 10) == 0) {
      PRINTF("[erase]  pos: %d, %d  data: %p\n", x, y, (void *)tests[i].data);

      hash2d_free(hash, x, y);

      tests[i].data = NULL;
    }
  }

  // affirm that those that were erased are gone,
  // affirm that those that remain are still valid
  for(int i = 0 ; i < 100 ; i ++) {
    int x = tests[i].x;
    int y = tests[i].y;

    uint32_t * data = (uint32_t *)hash2d_get(hash, x, y);

    PRINTF("[get]  pos: %d, %d  data: %p\n", x, y, (void *)data);

    ck_assert_ptr_eq(tests[i].data, data);

    if(data) {
      ck_assert_uint_eq(*data, tests[i].salt);
    }
  }

  // erase remaining entries
  for(int i = 0 ; i < 100 ; i ++) {
    if(tests[i].data) {
      int x = tests[i].x;
      int y = tests[i].y;

      hash2d_free(hash, x, y);

      PRINTF("[free]  pos: %d, %d  data: %p\n", x, y, (void *)tests[i].data);

      tests[i].data = NULL;
    }
  }

  // affirm that all entries have been erased
  for(int i = 0 ; i < 100 ; i ++) {
    int x = tests[i].x;
    int y = tests[i].y;

    uint32_t * data = hash2d_get(hash, x, y);

    PRINTF("[get]  pos: %d, %d  data: %p\n", x, y, (void *)data);

    ck_assert_ptr_null(data);
  }
}

START_TEST(test_hash2d)
{
  srand((unsigned int)time(NULL));

  hash2d_t * hash = hash2d_init(malloc(sizeof hash));

  for(int i = 0 ; i < 100 ; i ++) {
    hash2d_single_run(hash);
  }

  free(hash2d_deinit(hash));
}
END_TEST

Suite * util_check_suite(void) {
  Suite * suite = suite_create("util module");
  TCase * test_case;

  test_case = tcase_create("hash2d");
  tcase_add_test(test_case, test_hash2d);
  suite_add_tcase(suite, test_case);

  return suite;
}

