/*
 *  Author: TITREN Loïc
 *  Create Time: 2019-06-03 09:39:44
 *  ;------------:
 *  Modified by: Ardouin théo
 *  Modified time: 2019-06-16 18:56:02
 *  Description: Runs unit tests one by one
 */

#ifndef RUN_TESTS_H_
#define RUN_TESTS_H_

#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

/// Checks all possible crashes of the latest executed test
void check_crash_exit_status(ck_tests_t *test, int status);

/// Prints the latest test result
void check_test_success(ck_tests_t *test, int status);

/// Handles timeout in child process
void set_timeout(ck_tests_t *test);

/// Calls all loaded tests one by one
int run_tests(ck_tests_t *tests);

/// Prints tests result and percentage
void ck_print_result(void);

#endif