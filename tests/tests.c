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

    assert_eq_ptr(marcel, truc);
}

TEST(lul)
{
    char *marcel = "1234";
    char *truc = "1234";

    assert_eq_ptr((void *)marcel, (void *)truc);
}

TEST(lal)
{
    int marcel = 1234;
    int truc = 1234;

    assert_eq_ptr((void *)&marcel, (void *)&truc);
}

TEST(ljl)
{
    int marcel = 124;
    int truc = 1234;

    assert_eq_ptr((void *)&marcel, (void *)&truc);
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