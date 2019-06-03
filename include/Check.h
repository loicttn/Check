/*
 *  Author: Ardouin théo
 *  Create Time: 2019-06-02 01:11:46
 *  :------------:
 *  Modified by: TITREN Loïc
 *  Modified time: 2019-06-03 13:17:18
 *  Description: librairy testing include
 */

#ifndef CHECK_H_
#define CHECK_H_

#include "Check_tests_creator.h"
#include "Check_internal.h"
#include "Check_asserts.h"

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