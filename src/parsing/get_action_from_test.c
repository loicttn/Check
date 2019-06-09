/*
 *  Author: ARDOUIN théo
 *  Create Time: 2019-06-09 13:50:48
 *  :------------:
 *  Modified by: Ardouin théo
 *  Modified time: 2019-06-09 14:01:04
 *  Description:
 */

#include <stdarg.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Check_internal.h"

static bool is_nbr(const char *nb)
{
    for (int i = 0; nb[i]; i++) {
        if (nb[i] < '0' || nb[i] > '9')
            return (false);
    }
    return (true);
}

static void append_exec(args_action_t *action, const char *_act)
{
    exec_list_t *ex_l = (exec_list_t *)malloc(sizeof(exec_list_t));

    if (ex_l == NULL) {
        dprintf(STDERR, RED "An error as occured\n" RESET);
        exit(EXIT_FAILURE);
    }
    memset(ex_l, 0, sizeof(exec_list_t));

    ex_l->script   = _act;
    ex_l->next     = action->exec_l;
    action->exec_l = ex_l;
}

static void append_redirection(args_action_t *action, const char *_act)
{
    redirection_t *red_l = (redirection_t *)malloc(sizeof(redirection_t));

    if (red_l == NULL) {
        dprintf(STDERR, RED "An error as occured\n" RESET);
        exit(EXIT_FAILURE);
    }
    memset(red_l, 0, sizeof(redirection_t));

    const char *s_fd = strtok(strdup(_act), " ");
    if (s_fd == NULL || is_nbr(s_fd) == false) {
        dprintf(STDERR, RED ".redirect must be used with a number as first argument.\n" RESET);
        exit(EXIT_FAILURE);
    }

    red_l->redirected_fd = atoi(s_fd);
    red_l->next = action->red_l;
    action->red_l = red_l;
}

args_action_t *parse_external_argument(const char *name)
{
    /* local struct for redirection keyword to specifics function   */
    typedef struct local_action_s {
        const char *keyword;
        void (*fptr)(args_action_t *, const char *);
    } local_action_t;

    /* keyword handled                                              */
    static const local_action_t act[] = {
        {".exec ",      &append_exec},
        {".redirect ",  &append_redirection},
        {0, 0}
    };

    args_action_t *action = (args_action_t *)malloc(sizeof(args_action_t));
    if (action == NULL) {

        dprintf(STDERR, RED "An error as occured\n" RESET);
        exit(EXIT_FAILURE);
    }
    memset(action, 0, sizeof(args_action_t));

    for (char *keeper = strtok(strdup(name), ","); keeper != NULL; keeper = strtok(NULL, ",")) {
        for (int i = 0; act[i].keyword; i++) {
            if (strncmp(keeper, act[i].keyword, strlen(act[i].keyword)) == 0)
                act[i].fptr(action, keeper + strlen(act[i].keyword));
        }
    }
    return (action);
}