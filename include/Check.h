/*
 *  Author: ARDOUIN théo
 *  Create Time: 2019-06-02 01:11:46
 *  :------------:
 *  Modified by: Ardouin théo
 *  Modified time: 2019-06-12 01:40:25
 *  Description: librairy testing include
 */

#ifndef CHECK_H_
#define CHECK_H_

#include "Check_tests_creator.h"
#include "Check_internal.h"

#define TEST(...)    \
    TEST_(__VA_ARGS__)

#define TEST_(X, ...)    \
    TEST__(X, 1, __VA_ARGS__)

#define TEST__(name, X...)   \
    TEST___(name, #X + 2)

#define TEST___(name, list)                                                 \
    void test_##name();                                                     \
    ck_tests_t *ck_concat(test_, __COUNTER__)(void) {                       \
        return (ck_init_new_test(#name, &test_##name, list));               \
    }                                                                       \
    void test_##name()

#endif  /* !CHECK_H_ */