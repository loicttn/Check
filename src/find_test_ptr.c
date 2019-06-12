/*
 *  Author: ARDOUIN théo
 *  Create Time: 2019-06-02 00:22:13
 *  ;------------:
 *  Modified by: Ardouin théo
 *  Modified time: 2019-06-12 01:40:47
 *  Description:
 */

#include <dlfcn.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "Check_tests_creator.h"
#include "Check_internal.h"
#include "Check_run_tests.h"

ck_tests_t *ck_get_next_test_ptr(void *handle, int n)
{
    void *keeper_ptr;
    ck_tests_t *(*fptr)();
    ck_tests_t *test_spe;
    char name[20];

    sprintf(name, "test_%d", n++);
    if ((keeper_ptr = dlsym(handle, name)) == NULL)
        return (NULL);
    fptr = keeper_ptr;
    test_spe = fptr();
    return (test_spe);
}

//  find the pointer on each test function and calls it

int ck_lunch_test(void)
{
    ck_tests_t *list = ck_init_test_list();

    // while (list) {
    //     list->fptr();
    //     list = list->next;
    // }
    run_tests(list);
    return (EXIT_SUCCESS);
}