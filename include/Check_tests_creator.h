/*
 *  Author: ARDOUIN théo
 *  Create Time: 2019-06-03 02:08:57
 *  :------------:
 *  Modified by: Ardouin théo
 *  Modified time: 2019-06-11 18:53:28
 *  Description:
 */

#ifndef TEST_CREATOR_H_
#define TEST_CREATOR_H_

#include "Check_internal.h"

ck_tests_t *ck_init_new_test(const char *name, void (*fptr)(void), const char *args);

#endif /* !TEST_CREATOR_H_ */