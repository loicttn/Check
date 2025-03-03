/*
 *  Author: ARDOUIN théo
 *  Create Time: 2019-06-09 13:50:48
 *  :------------:
 *  Modified by: Ardouin théo
 *  Modified time: 2019-07-15 14:26:04
 *  Description:
 */

#include <stdarg.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Check_internal.h"

static volatile bool append_error = false;

static bool is_nbr(const char *nb)
{
    for (int i = 0; nb[i]; i++) {
        if ((nb[i] < '0' || nb[i] > '9') && nb[i] != ' ')
            return (false);
    }
    return (true);
}

static char *get_strtok_ite(const char *name, const char *_spliter, int i)
{
    char *keeper = strdup(name);
    char *sto = strtok(keeper, _spliter);

    for (int j = 0; j < i; j++) {
        sto = strtok(NULL, _spliter);
    }
    return (sto);
}

#define exec_failure    \
do {    \
    create_message(&(test->msg_l), STDERR, RED, "error appeared while trying to use .exec built in.\nUSAGE :\t.exec {.condition failure/succeed/timeout/crashed} SCRIPT_TO_EXEC\n"); \
    return; \
} while(false)

static void append_exec(args_action_t *action, char *_act, ck_tests_t *test)
{
    ck_exec_list_t *ex_l = (ck_exec_list_t *)malloc(sizeof(ck_exec_list_t));

    if (ex_l == NULL) {
        dprintf(STDERR, RED "An error as occured\n" RESET);
        exit(EXIT_FAILURE);
    }
    memset(ex_l, 0, sizeof(ck_exec_list_t));
    ex_l->condition = TEST_OK;

    for (char *keeper = strtok(_act, " "); keeper; keeper = strtok(NULL, " ")) {
        if (strncmp(keeper, ".condition", 10) == 0) {
            if ((keeper = strtok(NULL, " ")) == NULL)
                exec_failure;
            else {
                if      (strcmp(keeper, "failure") == 0) ex_l->condition = TEST_KO;
                else if (strcmp(keeper, "timeout") == 0) ex_l->condition = TEST_TIMEOUT;
                else if (strcmp(keeper, "succeed") == 0) ex_l->condition = TEST_OK;
                else if (strcmp(keeper, "crashed") == 0) ex_l->condition = TEST_CRASH;
            }
        } else {
            if (ex_l->script)
                exec_failure;
            else
                ex_l->script = keeper;
        }
    }

    if (ex_l->script) {
        ex_l->next     = action->exec_l;
        action->exec_l = ex_l;

        char buff[500];
        if (ex_l->condition == TEST_KO) {
            sprintf(buff, "exec :\n\texecute %s if failed\n",  ex_l->script);
        } else if (ex_l->condition == TEST_OK) {
            sprintf(buff, "exec :\n\texecute %s if succeed\n", ex_l->script);
        } else if (ex_l->condition == TEST_TIMEOUT) {
            sprintf(buff, "exec :\n\texecute %s if timeout\n", ex_l->script);
        }
        create_message(&(test->msg_l), 1, RESET, buff);
    } else {
        free(_act);
        exec_failure;
    }
}

#define time_failure    \
do {                                                                                                                        \
        create_message(&(test->msg_l), STDERR, RED,    \
        "error appeared while trying to use .timeout built in.\nUSAGE :\t.timeout TIME(in usec)\n");\
    return; \
} while(false)


static void append_timeout(args_action_t *action, char *_act, ck_tests_t *test)
{
    ck_timeout_t *tim_l = (ck_timeout_t *)malloc(sizeof(ck_timeout_t));

    if (tim_l == NULL) {
        dprintf(STDERR, RED "An error as occured\n" RESET);
        exit(EXIT_FAILURE);
    }
    memset(tim_l, 0, sizeof(ck_timeout_t));

    if (_act == NULL || is_nbr(_act) == false)
        time_failure;
    tim_l->usec = atoi(_act);
    tim_l->next = action->tim_l;
    action->tim_l = tim_l;
    char buff[500];
    sprintf(buff, "timer :\n\ttime (usec) before timeout %d\n", tim_l->usec);
    create_message(&(test->msg_l), STDERR, RESET, buff);
}

// parse all test's flag line.
args_action_t *ck_parse_external_argument(const char *name, ck_tests_t *test)
{
    char *sto;

    /* local struct for redirection keyword to specifics function   */
    typedef struct local_action_s {
        const char *keyword;
        void (*fptr)(args_action_t *, char *, ck_tests_t *);
    } local_action_t;

    /* keyword handled                                              */
    static const local_action_t act[] = {
        {".exec ",     &append_exec},
        {".timeout ",  &append_timeout},
        {0, 0}
    };

    args_action_t *action = (args_action_t *)malloc(sizeof(args_action_t));
    if (action == NULL) {

        dprintf(STDERR, RED "An error as occured\n" RESET);
        exit(EXIT_FAILURE);
    }
    memset(action, 0, sizeof(args_action_t));

    int i = 0;
    for (char *keeper = strtok(strdup(name), ","); keeper; keeper = get_strtok_ite(name, ",", i)) {
        for (int i = 0; act[i].keyword; i++) {
            if ((sto = strstr(keeper, act[i].keyword))) {
                act[i].fptr(action, strdup(sto + strlen(act[i].keyword)), test);
            }
        }
        i++;
    }
    return (action);
}