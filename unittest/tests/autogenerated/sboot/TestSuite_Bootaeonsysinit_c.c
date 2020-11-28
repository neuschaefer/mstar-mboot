#include "cpptest.h"

CPPTEST_CONTEXT("/MBoot/src/drvPadConf.c");
CPPTEST_TEST_SUITE_INCLUDED_TO("/MBoot/src/drvPadConf.c");

CPPTEST_TEST_SUITE(TestSuite_Bootaeonsysinit_c_test);
CPPTEST_TEST(TestSuite_Bootaeonsysinit_c_MDrv_Pad_Init);
CPPTEST_TEST(TestSuite_Bootaeonsysinit_c_BL_Init);

CPPTEST_TEST_SUITE_END();
        

void TestSuite_Bootaeonsysinit_c_MDrv_Pad_Init();
void TestSuite_Bootaeonsysinit_c_BL_Init();


CPPTEST_TEST_SUITE_REGISTRATION(TestSuite_Bootaeonsysinit_c_test);

void TestSuite_Bootaeonsysinit_c_test_setUp()
{
}

void TestSuite_Bootaeonsysinit_c_test_tearDown()
{
}


/* CPPTEST_TEST_CASE_BEGIN TestSuite_MDrv_Pad_Init */
/* CPPTEST_TEST_CASE_CONTEXT void * MDrv_Pad_Init(void) */
void TestSuite_Bootaeonsysinit_c_MDrv_Pad_Init()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (size) */ 
    {
        /* Tested function call */
        MDrv_Pad_Init();
        /* Post-condition check */
        CPPTEST_ASSERT_UINTEGER_EQUAL("2686451712", ( u32MapBase ));
        CPPTEST_ASSERT_UINTEGER_EQUAL("2684354560", ( u32MapBase ));
    }
}
/* CPPTEST_TEST_CASE_END TestSuite_MDrv_Pad_Init */

/* CPPTEST_TEST_CASE_BEGIN TestSuite_BL_Init */
/* CPPTEST_TEST_CASE_CONTEXT void * BL_Init(void) */
void TestSuite_Bootaeonsysinit_c_BL_Init()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (size) */ 
    {
        /* Tested function call */
        void * _return  = BL_Init();
        /* Post-condition check */
        CPPTEST_POST_CONDITION_PTR("void * _return ", ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END TestSuite_BL_Init */

