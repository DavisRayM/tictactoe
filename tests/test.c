#include "test_board.h"
#include <CUnit/Basic.h>

int main(void) {
  CU_pSuite suite = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  suite = CU_add_suite("BoardSuite", init_boardsuite, clean_boardsuite);
  if (NULL == suite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (register_boardtests(suite) != 0) {
      CU_cleanup_registry();
      return CU_get_error();
  }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  if (CU_get_number_of_tests_failed() != 0) {   
    CU_cleanup_registry();
    return 1;
  }
  CU_cleanup_registry();
  return CU_get_error();
}
