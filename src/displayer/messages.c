/*
 *  Author: ARDOUIN théo
 *  Create Time: 2019-07-15 11:18:46
 *  :------------:
 *  Modified by: Ardouin théo
 *  Modified time: 2019-07-15 12:02:55
 *  Description:
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Check_internal.h"

void create_message(ck_message_t **msg, int std, const char *color, const char *text)
{
    ck_message_t *new_msg = (ck_message_t *) malloc(sizeof(ck_message_t));
    memset(new_msg, 0, sizeof(ck_message_t));

    new_msg->color = strdup(color);
    new_msg->text = strdup(text);
    new_msg->std = std;

    if (new_msg->text == NULL || new_msg->color == NULL) {
        dprintf(STDERR, RED "an error has occured" RESET);
        exit(EXIT_FAILURE);
    }

    if (*msg == NULL) {
        *msg = new_msg;
        return;
    } else {
        ck_message_t *keeper = *msg;
        for (; keeper->next; keeper = keeper->next);
        keeper->next = new_msg;
        return;
    }
}

void display_messages(ck_message_t *msg_l)
{
    void *keeper = NULL;

    for (; msg_l;) {
        dprintf(msg_l->std, msg_l->color);
        dprintf(msg_l->std, msg_l->text);
        dprintf(msg_l->std, RESET);
        free(msg_l->color);
        free(msg_l->text);
        keeper = msg_l;
        msg_l = msg_l->next;
        free(keeper);
        printf("\n");
    }
}