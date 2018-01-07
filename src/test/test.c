
#include <stdlib.h>
#include <check.h>

#include <test/test.h>

Suite * hex_check_suite(void);
Suite * asset_check_suite(void);
Suite * util_check_suite(void);

int test_all(void) {
  int number_failed;
  SRunner * sr;

  sr = srunner_create(hex_check_suite());
  srunner_add_suite(sr, asset_check_suite());
  srunner_add_suite(sr, util_check_suite());
  //srunner_add_suite(sr, ...);
  //srunner_add_suite(sr, ...);
  //srunner_add_suite(sr, ...);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

