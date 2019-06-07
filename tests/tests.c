#include "Check.h"
#include <string.h>

TEST(lol)
{
    while(1);
}

TEST(lil)
{
    char *marcel = "lol";
    char *truc = "xD";

    ASSERT_PTR(marcel, truc);
}

TEST(lul)
{
    char *marcel = "1234";
    char *truc = "1234";

    ASSERT_PTR((void *)marcel, (void *)truc);
}

TEST(lal)
{
    int marcel = 1234;
    int truc = 1234;

    ASSERT_PTR((void *)&marcel, (void *)&truc);
}

TEST(ljl)
{
    int marcel = 124;
    int truc = 1234;

    ASSERT_PTR((void *)&marcel, (void *)&truc);
}

TEST(naoufel_abort)
{
    abort();
}

TEST(loic_abort)
{
    char *lol = NULL;

    lol[42] = 'A';
}

TEST(null_1)
{
    int lol[] = {1, 0};

    ASSERT_PTR((int *)lol, NULL);
}

TEST(null_2)
{
    int lol[] = {1, 0};

    ASSERT_PTR(NULL, (int *)lol);
}

TEST(null_3)
{
    ASSERT_PTR(NULL, NULL);
}

TEST(_int)
{
    ASSERT(1, 1);
}

TEST(bis_int)
{
    ASSERT(-1, -1);
}

TEST(ter_int)
{
    ASSERT(41, 40);
}

TEST(_float)
{
    ck_assert_eq(1.5, 1);
}

TEST(bis_float)
{
    ASSERT(-1.1, -1.1);
}

TEST(ter_float)
{
    ASSERT(41.9, 41.99);
}