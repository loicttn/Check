/*
 *  Author: TITREN Loïc
 *  Create Time: 2019-06-03 11:56:00
 *  :------------:
 *  Modified by: Ardouin théo
 *  Modified time: 2019-07-17 15:12:55
 *  Description:
 */

#include <stdbool.h>
#include "Check_tests_creator.h"
#include "Check_run_tests.h"

static void *check_timeout(void *timeout)
{
    usleep(*((unsigned int *)timeout));
    exit(TEST_TIMEOUT);
}

void set_timeout(ck_tests_t *test)
{
    pthread_t thread_id = 0;
    if (!test->action->tim_l)
        return;
    unsigned int timeout = test->action->tim_l->usec;

    if (pthread_create(&thread_id, NULL, &check_timeout, (void *)&timeout)) {
        dprintf(STDERR, "FATAL ERROR: cannot create a new thread\n");
        exit(EXIT_FAILURE);
    }
}
