/*
 *  Author: TITREN Loïc
 *  Create Time: 2019-06-03 11:55:37
 *  :------------:
 *  Modified by: Ardouin théo
 *  Modified time: 2019-07-18 11:00:00
 *  Description:
 */

#include "Check.h"
#include "Check_internal.h"
#include "Check_tests_creator.h"
#include "Check_run_tests.h"

extern const int CK_SEPARATOR_LENGHT;

static int run_unit_test(ck_tests_t *test)
{
    int pid = 0;
    int status = 0;

    for (int i = 0; i < CK_SEPARATOR_LENGHT; i += 1)
        printf("~");
    printf("\n");
    printf(BLUE"Name :\t%s\n\n"RESET, test->test_name);
    display_messages(test->msg_l);
    pid = fork();
    switch(pid) {
        case -1:
            dprintf(STDERR, RESET"FATAL ERROR: fork failed.");
            exit (EXIT_FAILURE);
        case 0:
            set_timeout(test);
            test->fptr();
            exit(TEST_OK);
        default:
            wait(&status);
            if (WIFSIGNALED(status) && WTERMSIG(status))
                test->test_state = TEST_CRASH;
            else
                test->test_state = WEXITSTATUS(status);
    }
    return (status);
}

void exec_luncher(ck_tests_t *test);

int run_tests(ck_tests_t *tests)
{
    int status = 0;

    for (ck_tests_t *tail = tests; tail; tail = tail->next) {
        run_unit_test(tail);
        check_test_success(tail, status);
        exec_luncher(tail);
    }
    ck_print_result();
    return (0);
}