#include "cpptest.h"
// 14
CPPTEST_CONTEXT("/MBoot/src/sboot.c");
CPPTEST_TEST_SUITE_INCLUDED_TO("/MBoot/src/sboot.c");

CPPTEST_TEST_SUITE(TestSuite_sboot_c_7608004f);
CPPTEST_TEST(TestSuite_sboot_c_7608004f_TestSuite_MyAlloc);
CPPTEST_TEST_SUITE_END();



void TestSuite_sboot_c_7608004f_TestSuite_MyAlloc();
CPPTEST_TEST_SUITE_REGISTRATION(TestSuite_sboot_c_7608004f);

void TestSuite_sboot_c_7608004f_setUp()
{
}

void TestSuite_sboot_c_7608004f_tearDown()
{

}


/* CPPTEST_TEST_CASE_BEGIN TestSuite_MyAlloc */
/* CPPTEST_TEST_CASE_CONTEXT void * MyAlloc(size_t) */
void TestSuite_sboot_c_7608004f_TestSuite_MyAlloc()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (size) */



    size_t _size  = 0u;
    {
        /* Tested function call */
        void * _return  = MyAlloc(_size);
        /* Post-condition check */
        CPPTEST_POST_CONDITION_PTR("void * _return ", ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END TestSuite_MyAlloc */
