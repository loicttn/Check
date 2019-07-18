/*
 *  Author: TITREN Loïc
 *  Create Time: 2019-06-03 11:26:36
 *  :------------:
 *  Modified by: Ardouin théo
 *  Modified time: 2019-07-17 11:57:15
 *  Description:
 */

#include "Check.h"
#include "Check_internal.h"
#include "Check_tests_creator.h"
#include "Check_run_tests.h"

static unsigned int success = 0;
static unsigned int total = 0;
extern const int CK_SEPARATOR_LENGHT;

void ck_print_result(void)
{
    double percentage = (float)(success * 100 / total);

    for (int i = 0; i < CK_SEPARATOR_LENGHT; i += 1)
        printf("_");
    printf("\n\n");
    printf("Total: %d\t"GREEN"Success: %d\t"RESET""RED"Failed: %d"RESET"\n", total, success, total - success);
    if (percentage < 25)
        write(1, RED, sizeof(RED));
    else if (percentage < 75) {
        write(1, RESET, sizeof(RESET));
        write(1, ORANGE, sizeof(ORANGE));
    } else
        write(1, GREEN, sizeof(GREEN));
    printf("\n%.1f%%\n", percentage);
    write(1, RESET, sizeof(RESET));
}

void check_test_success(ck_tests_t *test, __attribute__((unused)) int status)
{
    printf("\n");
    total += 1;
    switch(test->test_state) {
        case (TEST_OK):
            printf(GREEN "SUCCESS\n" RESET);
            success += 1;
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
            total -= 1;
    }
}

void exec_luncher(ck_tests_t *test)
{
    int pid = 0;
    int status = 0;

    for (;test->action->exec_l; test->action->exec_l = test->action->exec_l->next) {
        pid = fork();
        switch(pid) {
            case -1:
                dprintf(STDERR, RED"FATAL ERROR: fork failed."RESET);
                exit (EXIT_FAILURE);
            case 0:
                if (test->test_state == test->action->exec_l->condition) {
                    write(1, RESET, sizeof(RESET));
                    system(test->action->exec_l->script);
                }
                else
                    printf(ORANGE"Condition weren't satisfying execution's condition.\n"RESET);
                exit(TEST_OK);
            default:
                wait(&status);
                if (WTERMSIG(status))
                    printf(RED"Script crashed\n"RESET);
        }
    }
}
