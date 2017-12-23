
#include <check.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include <util/hash_2i.h>
#include <util/hash_ul.h>
#include <util/objarray.h>

#define PRINTF(...)
//#define PRINTF(...) printf(__VA_ARGS__)

#define ZERO(_item_) \
  memset(&_item_, 0, sizeof(_item_))

static void hash_2i_single_run(hash_2i_t * hash) {
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

    uint32_t * data = (uint32_t *)hash_2i_create(hash, x, y, sizeof(uint32_t));

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

    uint32_t * data = (uint32_t *)hash_2i_find(hash, x, y);

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

      hash_2i_destroy(hash, x, y);

      tests[i].data = NULL;
    }
  }

  // affirm that those that were erased are gone,
  // affirm that those that remain are still valid
  for(int i = 0 ; i < 100 ; i ++) {
    int x = tests[i].x;
    int y = tests[i].y;

    uint32_t * data = (uint32_t *)hash_2i_find(hash, x, y);

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

      hash_2i_destroy(hash, x, y);

      PRINTF("[free]  pos: %d, %d  data: %p\n", x, y, (void *)tests[i].data);

      tests[i].data = NULL;
    }
  }

  // affirm that all entries have been erased
  for(int i = 0 ; i < 100 ; i ++) {
    int x = tests[i].x;
    int y = tests[i].y;

    uint32_t * data = hash_2i_find(hash, x, y);

    PRINTF("[get]  pos: %d, %d  data: %p\n", x, y, (void *)data);

    ck_assert_ptr_null(data);
  }
}

START_TEST(test_hash_2i)
{
  srand((unsigned int)time(NULL));

  hash_2i_t * hash = calloc(sizeof(*hash), 1);

  for(int i = 0 ; i < 100 ; i ++) {
    hash_2i_single_run(hash);
  }

  hash_2i_clear(hash);
  free(hash);
}
END_TEST

static void hash_ul_single_run(hash_ul_t * hash) {
  struct test_entry_t {
    uint32_t salt;
    unsigned long key;
    uint32_t * data;
  };
  struct test_entry_t tests[100];

  // set several entries in the hash
  for(int i = 0 ; i < 100 ; i ++) {
    uint32_t salt = (uint32_t)rand();

    // note: impossible to have duplicates, but still very sparse
    unsigned long key = (unsigned long)(100 * i + (rand() % 100));

    uint32_t * data = (uint32_t *)hash_ul_create(hash, key, sizeof(uint32_t));

    ck_assert_ptr_nonnull(data);

    *data = salt;

    tests[i].salt = salt;
    tests[i].key = key;
    tests[i].data = data;

    PRINTF("[alloc]  key: %lu  salt: %08X  data: %p\n", key, salt, (void *)tests[i].data);
  }

  // affirm that data is intact, pointers match those initially returned
  for(int i = 0 ; i < 100 ; i ++) {
    unsigned long key = tests[i].key;

    uint32_t * data = (uint32_t *)hash_ul_find(hash, key);

    PRINTF("[get]  key: %lu  data: %p\n", key, (void *)data);

    ck_assert_ptr_nonnull(data);
    ck_assert_ptr_eq(data, tests[i].data);
    ck_assert_uint_eq(*data, tests[i].salt);
  }

  // erase several entries
  for(int i = 0 ; i < 100 ; i ++) {
    unsigned long key = tests[i].key;

    if((rand() % 10) == 0) {
      PRINTF("[erase]  key: %lu  data: %p\n", key, (void *)tests[i].data);

      hash_ul_destroy(hash, key);

      tests[i].data = NULL;
    }
  }

  // affirm that those that were erased are gone,
  // affirm that those that remain are still valid
  for(int i = 0 ; i < 100 ; i ++) {
    unsigned long key = tests[i].key;

    uint32_t * data = (uint32_t *)hash_ul_find(hash, key);

    PRINTF("[get]  key: %lu  data: %p\n", key, (void *)data);

    ck_assert_ptr_eq(tests[i].data, data);

    if(data) {
      ck_assert_uint_eq(*data, tests[i].salt);
    }
  }

  // erase remaining entries
  for(int i = 0 ; i < 100 ; i ++) {
    if(tests[i].data) {
      unsigned long key = tests[i].key;

      hash_ul_destroy(hash, key);

      PRINTF("[free]  key: %d, %d  data: %p\n", key, (void *)tests[i].data);

      tests[i].data = NULL;
    }
  }

  // affirm that all entries have been erased
  for(int i = 0 ; i < 100 ; i ++) {
    unsigned long key = tests[i].key;

    uint32_t * data = hash_ul_find(hash, key);

    PRINTF("[get]  key: %d, %d  data: %p\n", key, (void *)data);

    ck_assert_ptr_null(data);
  }
}

START_TEST(test_hash_ul)
{
  srand((unsigned int)time(NULL));

  hash_ul_t * hash = calloc(sizeof(*hash), 1);

  for(int i = 0 ; i < 100 ; i ++) {
    hash_ul_single_run(hash);
  }

  hash_ul_clear(hash);
  free(hash);
}
END_TEST

/*
static void assert_val_eq_neg_idx_if_nonnull(int idx, void * val, void * ud) {
  if(val) {
    int * myint = (int *)val;
    ck_assert_int_eq(*myint, -idx);
  }
  //printf("[%d] = %p\n", idx, val);
}

START_TEST(test_objarray)
{
  srand((unsigned int)time(NULL));

  objarray_t * array = objarray_init(malloc(sizeof(*array)), NULL);

  // insert 100 ints into the array
  for(int i = 0 ; i < 100 ; i ++) {
    int * myint = (int *)objarray_push_back(array, sizeof(int));

    // shouldn't fail
    ck_assert_ptr_nonnull(myint);

    // ensure data is zero'ed
    ck_assert_int_eq(*myint, 0);

    *myint = i;
  }

  // ensure correct size
  ck_assert_int_eq(objarray_size(array), 100);

  // ensure correct values
  for(int i = 0 ; i < 100 ; i ++) {
    int * myint = (int *)objarray_at(array, i);

    ck_assert_ptr_nonnull(myint);
    ck_assert_int_eq(*myint, i);
  }

  // ensure out-of bounds accesses return null
  for(int i = 0 ; i < 200 ; i ++) {
    int idx = (int)(rand() % 400) - 150;

    int * myint = (int *)objarray_at(array, idx);

    if(idx >= 0 && idx < 100) {
      ck_assert_ptr_nonnull(myint);
      ck_assert_int_eq(*myint, idx);
    } else {
      ck_assert_ptr_null(myint);
    }
  }

  // replacement should only work for valid indices
  for(int i = -10 ; i < 110 ; i ++) {
    int * newint = (int *)objarray_set(array, i, sizeof(int));

    if(i >= 0 && i < 100) {
      ck_assert_ptr_nonnull(newint);
      ck_assert_int_eq(*newint, 0);
      *newint = -i;
    } else {
      ck_assert_ptr_null(newint);
    }
  }

  // freeing should result in null
  for(int i = 0 ; i < 100 ; i ++) {
    int * myint = (int *)objarray_at(array, i);

    ck_assert_ptr_nonnull(myint);

    if((rand() % 3) == 0) {
      objarray_unset(array, i);

      // try to retrieve
      myint = (int *)objarray_at(array, i);

      // should be null
      ck_assert_ptr_null(myint);
    }
  }

  objarray_each(array, assert_val_eq_neg_idx_if_nonnull, NULL);

  free(objarray_deinit(array));
}
END_TEST

int n_ints_deleted = 0;
void counting_int_dtor(void * _) {
  n_ints_deleted ++;
}

START_TEST(test_objarray_dtor)
{
  srand((unsigned int)time(NULL));

  objarray_t * array = objarray_init(malloc(sizeof(*array)), counting_int_dtor);

  for(int i = 0 ; i < 100 ; i ++) {
    objarray_push_back(array, sizeof(int));
  }

  for(int i = 0 ; i < 100 ; i ++) {
    int n_ints_deleted_old = n_ints_deleted;

    objarray_set(array, i, sizeof(int));

    ck_assert_int_eq(n_ints_deleted, n_ints_deleted_old + 1);
  }

  // delete randomly
  for(int i = 0 ; i < 100 ; i ++) {
    if((rand() % 3) == 0) {
      int n_ints_deleted_old = n_ints_deleted;
      objarray_unset(array, i);
      ck_assert_int_eq(n_ints_deleted, n_ints_deleted_old + 1);
    }
  }

  free(objarray_deinit(array));

  ck_assert_int_eq(n_ints_deleted, 200);
}
END_TEST
*/

Suite * util_check_suite(void) {
  Suite * suite = suite_create("util module");
  TCase * test_case;

  test_case = tcase_create("hash_2i");
  tcase_add_test(test_case, test_hash_2i);
  suite_add_tcase(suite, test_case);

  test_case = tcase_create("hash_ul");
  tcase_add_test(test_case, test_hash_ul);
  suite_add_tcase(suite, test_case);

  //test_case = tcase_create("objarray");
  //tcase_add_test(test_case, test_objarray);
  //tcase_add_test(test_case, test_objarray_dtor);
  //suite_add_tcase(suite, test_case);

  return suite;
}

