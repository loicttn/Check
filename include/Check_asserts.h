/*
 *  Author: TITREN Loïc
 *  Create Time: 2019-06-03 11:59:03
 *  :------------:
 *  Modified by: TITREN Loïc
 *  Modified time: 2019-06-03 15:48:02
 *  Description:
 */

#ifndef ASSERTS_H
#define ASSERTS_H

#include <stdio.h>
#include <stdlib.h>

void ck_assert_eq_ptr(void *str1, void *str2);
#define ASSERT_PTR ck_assert_eq_ptr
#endif