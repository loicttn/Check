/*
 *  Author: Ardouin théo
 *  Create Time: 2019-06-02 01:11:46
 *  :------------:
 *  Modified by: Ardouin théo
 *  Modified time: 2019-06-03 03:24:26
 *  Description: librairy testing include
 */

#ifndef CHECK_H_
#define CHECK_H_

#include "Check_tests_creator.h"
#include "Check_internal.h"

#define TEST(name)                                                  \
    void test_##name();                                             \
    ck_tests_t *ck_concat(test_, __COUNTER__)(void) {               \
        return (init_new_test(#name, &test_##name));                \
    }                                                               \
    void test_##name()

#define ck_assert_eq(a, b)
#define ck_assert_neq(a, b)
#define ck_assert_null(a)

#endif  /* !CHECK_H_ */