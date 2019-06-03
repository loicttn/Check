/*
 *  Author: TITREN Loïc
 *  Create Time: 2019-06-03 10:20:44
 *  ;------------:
 *  Modified by: TITREN Loïc
 *  Modified time: 2019-06-03 09:39:44
 *  Description: Runs unit tests one by one
 */

#include "Check_tests_creator.h"
#include "Check_run_tests.h"

static void *check_timeout(void *timeout)
{
    sleep(*((unsigned int *)timeout));
    exit(TEST_TIMEOUT);
}

void set_timeout(ck_tests_t *test)
{
    pthread_t thread_id = 0;
    // unsigned int timeout = test->timeout
    unsigned int timeout = 2;

    if (pthread_create(&thread_id, NULL, &check_timeout, (void *)&timeout)) {
        dprintf(2, "FATAL ERROR: cannot create a new thread\n");
        exit(EXIT_FAILURE);
    }
}