/*
 *  Author: Ardouin théo
 *  Create Time: 2019-06-02 01:19:44
 *  ;------------:
 *  Modified by: Ardouin théo
 *  Modified time: 2019-06-03 03:30:07
 *  Description:
 */

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Check_internal.h"

ck_tests_t *init_new_test(const char *name, void (*fptr)(void))
{
    ck_tests_t *new;

    if ((new = (ck_tests_t *) malloc(sizeof(ck_tests_t))) == NULL ||
        (new->test_name = (char *) malloc(sizeof(char) * (strlen(name) + 1))) == NULL) {
        dprintf(STDERR, RED "An error as occured\n" RESET);
        exit (EXIT_FAILURE);
    }
    new->fptr = fptr;
    strcpy(new->test_name, name);
    new->test_state = NONE;
    new->next = NULL;
    return (new);
}

ck_tests_t *init_test_list(void)
{
    void *handle = dlopen(NULL, RTLD_LAZY);

    // error case
    if (handle == NULL) {
        dprintf(STDERR, RED "An error as occured\n" RESET);
        exit (EXIT_FAILURE);
    }

    // search all the test and append them to a linked list
    ck_tests_t *head = NULL;
    ck_tests_t *prev = NULL;
    ck_tests_t *keeper = NULL;

    for (int n = 0; (keeper = get_next_test_ptr(handle, n)); n++) {
        if (n == 0)
            head = keeper;
        else
            prev->next = keeper;
        prev = keeper;
    }

    dlclose(handle);
    return (head);
}