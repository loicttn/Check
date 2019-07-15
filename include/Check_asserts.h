/*
 *  Author: TITREN Loïc
 *  Create Time: 2019-06-03 11:59:03
 *  :------------:
 *  Modified by: Ardouin théo
 *  Modified time: 2019-06-16 19:12:33
 *  Description:
 */

#ifndef CHECK_ASSERTS_H
#define CHECK_ASSERTS_H

#include <stdio.h>
#include <stdlib.h>

void ck_assert_eq_ptr(void *str1, void *str2);
void ck_assert_eq(double a, double b);

#define ASSERT_PTR(a, b) ck_assert_eq_ptr(a, b)
#define CK_ASSERT(a, b) ck_assert_eq(a, b)

#endif