/*
 *  Author: TITREN Loïc
 *  Create Time: 2019-06-03 16:16:47
 *  :------------:
 *  Modified by: TITREN Loïc
 *  Modified time: 2019-06-03 16:20:18
 *  Description:
 */

#include "Check_asserts.h"
#include "Check_tests_creator.h"

void ck_assert_eq_ptr(void *str1, void *str2)
{
    char *strA = (char *)str1;
    char *strB = (char *)str2;

    if ((str1 && !str2) || (!str1 && str2))
        exit(TEST_KO);
    if (!str1 && !str2)
        exit(TEST_OK);
    while (*strA && *strB && *strA == *strB) {
        strA += 1;
        strB += 1;
    }
    if (*strA || *strB) {
        dprintf(STDERR, RED "%s != %s\n" RESET, (char *)str1, (char *)str2);
        exit(TEST_KO);
    }
}

void ck_assert_eq(double a, double b)
{
    if (a != b)
        exit(TEST_KO);
}