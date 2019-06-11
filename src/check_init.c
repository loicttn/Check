/*
 *  Author: ARDOUIN théo
 *  Create Time: 2019-06-02 01:19:44
 *  ;------------:
 *  Modified by: Ardouin théo
 *  Modified time: 2019-06-12 01:03:08
 *  Description:
 */

#include <stdarg.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Check_internal.h"

args_action_t *ck_parse_external_argument(const char *name);

char **get_args_tab(int nb_args, va_list va)
{
    char **tab;

    if ((tab = (char **) malloc(sizeof(char *) * (nb_args + 1))) == NULL) {
        dprintf(STDERR, RED "An error as occured\n" RESET);
        exit (EXIT_FAILURE);
    }

    const char *args;

    for (int i = 0; i < nb_args; i++) {
        args = va_arg(va, const char *);
        if ((tab[i] = strdup(args)) == NULL) {
            dprintf(STDERR, RED "An error as occured\n" RESET);
            exit (EXIT_FAILURE);
        }
    }
    return (tab);
}

ck_tests_t *ck_init_new_test(const char *name, void (*fptr)(void), const char *args)
{
    ck_tests_t *new;

    if ((new = (ck_tests_t *) malloc(sizeof(ck_tests_t))) == NULL ||
        (new->test_name = (char *) malloc(sizeof(char) * (strlen(name) + 1))) == NULL) {
        dprintf(STDERR, RED "An error as occured\n" RESET);
        exit (EXIT_FAILURE);
    }

    new->action = ck_parse_external_argument(args);
    new->fptr   = fptr;
    strcpy(new->test_name, name);
    new->test_state = NONE;
    new->next = NULL;
    return (new);
}

ck_tests_t *ck_init_test_list(void)
{
    void *handle = dlopen(NULL, RTLD_LAZY);

    // error case
    if (handle == NULL) {
        dprintf(STDERR, RED "An error as occured\n" RESET);
        exit (EXIT_FAILURE);
    }

    // search all the test and append them to a linked list
    ck_tests_t *head = NULL;
    ck_tests_t *prev;
    ck_tests_t *keeper;

    for (int n = 0; (keeper = ck_get_next_test_ptr(handle, n)); n++) {
        if (n == 0)
            head = keeper;
        else
            prev->next = keeper;
        prev = keeper;
    }

    dlclose(handle);
    return (head);
}