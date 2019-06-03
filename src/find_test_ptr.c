/*
 *  Author: ARDOUIN théo
 *  Create Time: 2019-06-02 00:22:13
 *  ;------------:
 *  Modified by: ARDOUIN théo
 *  Modified time: 2019-06-03 03:34:42
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

ck_tests_t *get_next_test_ptr(void *handle, int n)
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
    printf("test internal name -> %s\n\toutput name -> %s\n\tptr to test fct %p\n", name, test_spe->test_name, test_spe->fptr);
    return (test_spe);
}

//  find the pointer on each test function and calls it

int ck_lunch_test(void)
{
    ck_tests_t *list = init_test_list();

    while (list) {
        list->fptr();
        list = list->next;
    }
    return (EXIT_SUCCESS);
}