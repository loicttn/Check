/*
*  Author: TITREN Loïc
*  Create Time: 2019-06-03 09:51:00
*  ;------------:
*  Modified by: TITREN Loïc
*  Modified time: 2019-06-03 09:39:44
*  Description: Runs unit tests one by one
*/

#include "Check.h"
#include "Check_internal.h"
#include "Check_tests_creator.h"
#include "Check_run_tests.h"

void check_crash_exit_status(ck_tests_t *test, int status)
{
    if (WIFSIGNALED(status)) {
        test->test_state = TEST_CRASH;
        if (WTERMSIG(status) == SIGSEGV)
            dprintf(STDERR, "Segmentation fault");
        else if (WTERMSIG(status) == SIGFPE)
            dprintf(STDERR, "Floating exception");
    }
    if (WCOREDUMP(status))
        dprintf(STDERR, " (core dumped)");
    if (WCOREDUMP(status) || WIFSIGNALED(status))
        dprintf(STDERR, "\n");
}

void check_test_success(ck_tests_t *test, int status)
{
    printf("%s\t", test->test_name);
    switch(test->test_state) {
        case (TEST_OK):
            printf(GREEN "SUCCESS\n" RESET);
            break;
        case (TEST_KO):
            printf(RED "FAILURE\n" RESET);
            break;
        case (TEST_CRASH):
            printf(RED "CRASH\n" RESET);
            break;
        case (TEST_TIMEOUT):
            printf(RED "TIMEOUT\n" RESET);
            break;
        case (NONE):
            printf(RED "NOT RUN\n" RESET);
    }
}