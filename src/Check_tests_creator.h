/*
 *  Author: Ardouin théo
 *  Create Time: 2019-06-03 02:08:57
 *  ;------------:
 *  Modified by: Ardouin théo
 *  Modified time: 2019-06-03 02:12:37
 *  Description:
 */

#ifndef TEST_CREATOR_H_
#define TEST_CREATOR_H_

#include "Check_internal.h"

ck_tests_t *init_new_test(const char *name, void (*fptr)(void));

#endif /* !TEST_CREATOR_H_ */