#include "CUnit.h"
#include "Console.h"
static int TestInit(void) {return 0;}
static int TestClean(void) {return 0;}

void testAssertTrue(void)
{
  CU_ASSERT_TRUE(CU_TRUE);
  CU_ASSERT_TRUE(!CU_FALSE);

  CU_ASSERT_TRUE(!CU_TRUE);
  CU_ASSERT_TRUE(CU_FALSE);
}

void main(void)
{
    CU_pSuite pSuite;

    CU_initialize_registry();

    pSuite = CU_add_suite("TestHello", TestInit, TestClean);
    CU_add_test(pSuite, "testAssertTrue", testAssertTrue);

    CU_console_run_tests();
    CU_cleanup_registry();
}