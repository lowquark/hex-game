
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include <gs/gs.h>
#include <gs/cellhash.h>

#define PRINTF(...)
//#define PRINTF(...) printf(__VA_ARGS__)

#define ZERO(_item_) \
  memset(&_item_, 0, sizeof(_item_))

static void cellhash_single_run() {
  struct test_entry_t {
    uint32_t salt;
    hex_vec2i_t pos;
    gs_cell_t * cell;
  };
  struct test_entry_t tests[100];

  // set several cells in the cellhash
  for(int i = 0 ; i < 100 ; i ++) {
    uint32_t salt = (uint32_t)rand();

    // note: impossible to have duplicates, but still very sparse
    hex_vec2i_t pos;
    pos.x = 100 * i + (rand() % 100);
    pos.y = 100 * i + (rand() % 100);

    gs_cell_t cell;
    ZERO(cell);
    cell.tile.fg_color.r = (uint8_t)(salt      );
    cell.tile.fg_color.g = (uint8_t)(salt >>  8);
    cell.tile.fg_color.b = (uint8_t)(salt >> 16);

    tests[i].salt = salt;
    tests[i].pos = pos;
    tests[i].cell = gs_cellhash_set(pos, &cell);

    PRINTF("[set] pos: %d, %d  salt: %08X  cell: %p\n", pos.x, pos.y, salt, (void *)tests[i].cell);

    ck_assert_ptr_nonnull(tests[i].cell);
  }

  // affirm that data is intact, pointers match those initially returned
  for(int i = 0 ; i < 100 ; i ++) {
    hex_vec2i_t pos = tests[i].pos;

    gs_cell_t * cell = gs_cellhash_get(pos);

    PRINTF("[get] pos: %d, %d  cell: %p\n", pos.x, pos.y, (void *)cell);

    ck_assert_ptr_nonnull(cell);
    ck_assert_ptr_eq(cell, tests[i].cell);
    ck_assert_uint_eq(cell->tile.fg_color.r, (uint8_t)(tests[i].salt      ));
    ck_assert_uint_eq(cell->tile.fg_color.g, (uint8_t)(tests[i].salt >>  8));
    ck_assert_uint_eq(cell->tile.fg_color.b, (uint8_t)(tests[i].salt >> 16));
  }

  // erase several entries
  for(int i = 0 ; i < 100 ; i ++) {
    hex_vec2i_t pos = tests[i].pos;

    if((rand() % 10) == 0) {
      PRINTF("[erase] pos: %d, %d  cell: %p\n", pos.x, pos.y, (void *)tests[i].cell);

      gs_cellhash_erase(pos);

      tests[i].cell = NULL;
    }
  }

  // affirm that those that were erased are gone,
  // affirm that those that remain are still valid
  for(int i = 0 ; i < 100 ; i ++) {
    hex_vec2i_t pos = tests[i].pos;

    gs_cell_t * cell = gs_cellhash_get(pos);

    PRINTF("[get] pos: %d, %d  cell: %p\n",
           tests[i].pos.x,
           tests[i].pos.y,
           (void *)cell);

    ck_assert_ptr_eq(tests[i].cell, cell);

    if(cell) {
      ck_assert_uint_eq(cell->tile.fg_color.r, (uint8_t)(tests[i].salt      ));
      ck_assert_uint_eq(cell->tile.fg_color.g, (uint8_t)(tests[i].salt >>  8));
      ck_assert_uint_eq(cell->tile.fg_color.b, (uint8_t)(tests[i].salt >> 16));
    }
  }

  // erase remaining entries
  for(int i = 0 ; i < 100 ; i ++) {
    if(tests[i].cell) {
      gs_cellhash_erase(tests[i].pos);

      PRINTF("[erase] pos: %d, %d  cell: %p\n",
             tests[i].pos.x,
             tests[i].pos.y,
             (void *)tests[i].cell);

      tests[i].cell = NULL;
    }
  }

  // affirm that all entries have been erased
  for(int i = 0 ; i < 100 ; i ++) {
    hex_vec2i_t pos = tests[i].pos;

    gs_cell_t * cell = gs_cellhash_get(pos);

    PRINTF("[get] pos: %d, %d  cell: %p\n",
           tests[i].pos.x,
           tests[i].pos.y,
           (void *)cell);

    ck_assert_ptr_null(cell);
  }
}

START_TEST(test_cellhash)
{
  srand((unsigned int)time(NULL));

  gs_cellhash_init();

  for(int i = 0 ; i < 100 ; i ++) {
    cellhash_single_run();
  }

  gs_cellhash_clear();
}
END_TEST

START_TEST(test_add_remove)
{
  srand((unsigned int)time(NULL));

  gs_init();

  for(int j = 0 ; j < 4 ; j ++) {
  for(int i = 0 ; i < 4 ; i ++) {
    gs_cell_t cell;
    cell.mobs = NULL;
    cell.items = NULL;
    cell.mob_num = 0;
    cell.item_num = 0;
    cell.tile.sprite_id = 0;
    cell.tile.fg_color.r = (uint8_t)i;
    cell.tile.bg_color.g = (uint8_t)j;
    cell.tile.bg_color.b = 0;
    cell.tile.bg_color.r = (uint8_t)i;
    cell.tile.bg_color.g = (uint8_t)j;
    cell.tile.bg_color.b = 0;

    hex_vec2i_t pos;
    pos.x = i;
    pos.y = j;

    gs_set_cell(pos, &cell);
  }}

  for(int j = 0 ; j < 4 ; j ++) {
  for(int i = 0 ; i < 4 ; i ++) {
    hex_vec2i_t pos;
    pos.x = i;
    pos.y = j;

    const gs_cell_t * cellptr = gs_get_cell(pos);

    ck_assert(cellptr->mobs == NULL);
    ck_assert(cellptr->items == NULL);
    ck_assert(cellptr->mob_num == 0);
    ck_assert(cellptr->item_num == 0);
    ck_assert(cellptr->tile.sprite_id == 0);
    ck_assert(cellptr->tile.fg_color.r == (uint8_t)i);
    ck_assert(cellptr->tile.bg_color.g == (uint8_t)j);
    ck_assert(cellptr->tile.bg_color.b == 0);
    ck_assert(cellptr->tile.bg_color.r == (uint8_t)i);
    ck_assert(cellptr->tile.bg_color.g == (uint8_t)j);
    ck_assert(cellptr->tile.bg_color.b == 0);
  }}

  for(int j = 0 ; j < 4 ; j ++) {
  for(int i = 0 ; i < 4 ; i ++) {
    gs_item_t items[4];
    gs_cell_t cell;
    ZERO(items);
    ZERO(cell);

    cell.items = items;
    cell.item_num = 4;

    for(int k = 0 ; k < 4 ; k ++) {
      cell.items[k].sprite_id = i + 20*j + 20*20*k;
      cell.items[k].name = "test";
      cell.items[k].quantity = k + 1;
    }

    hex_vec2i_t pos;
    pos.x = i;
    pos.y = j;

    // set 4 times just for shits
    gs_set_cell(pos, &cell);
    gs_set_cell(pos, &cell);
    gs_set_cell(pos, &cell);
    gs_set_cell(pos, &cell);
  }}

  for(int j = 0 ; j < 4 ; j ++) {
  for(int i = 0 ; i < 4 ; i ++) {
    hex_vec2i_t pos;
    pos.x = i;
    pos.y = j;

    const gs_cell_t * cellptr = gs_get_cell(pos);

    ck_assert(cellptr->items);
    ck_assert(cellptr->item_num == 4);
    ck_assert(cellptr->mobs == NULL);
    ck_assert(cellptr->mob_num == 0);

    for(int k = 0 ; k < 4 ; k ++) {
      ck_assert       (cellptr->items[k].sprite_id == i + 20*j + 20*20*k);
      ck_assert_str_eq(cellptr->items[k].name, "test");
      ck_assert       (cellptr->items[k].quantity == k + 1);
    }
  }}

  gs_deinit();
}
END_TEST


Suite * gs_check_suite(void) {
  Suite * suite = suite_create("gamestate module");
  TCase * test_case;

  // test core functionality
  test_case = tcase_create("cell hash");
  tcase_add_test(test_case, test_cellhash);
  suite_add_tcase(suite, test_case);

  // test core functionality
  test_case = tcase_create("core");
  tcase_add_test(test_case, test_add_remove);
  suite_add_tcase(suite, test_case);

  return suite;
}

