#include "Check_asserts.h"
#include "Check_redirections.h"
#include "Check.h"
#include <string.h>
#include <unistd.h>

void ck_assert_eq_ptr(void *str1, void *str2);
void ck_assert_eq(double a, double b);

TEST(xxx, .exec /ZE/)
{
}

TEST(xxz, .exec , .redirect 2)
{
    printf("aa");
}

TEST(ez,.exec .condition failure ls, .exec pwd, .exec .condition timeout l, .timeout 200)
{
}

TEST(axx, .timeout e, .exec ls)
{
}

TEST(xax, .timeout 2000)
{
    while(1);
}

TEST(ax, .timeout 1005)
{
    sleep(1);
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
    CK_ASSERT(1, 1);
}

TEST(bis_int)
{
    CK_ASSERT(-1, -1);
}

TEST(ter_int)
{
    CK_ASSERT(41, 40);
}

TEST(_float)
{
    CK_ASSERT(1.5, 1);
}

TEST(bis_float)
{
    CK_ASSERT(-1.1, -1.1);
}

TEST(ter_float)
{
    CK_ASSERT(41.9, 41.99);
}

static void write_n_char_in_std(char c, int n, int std)
{
    for (int i = 0; i < n; i += 1)
        write(std, &c, 1);
}

TEST(redirect_std_failure)
{
    REDIRECT_STD(0);
    write_n_char_in_std('l', 5, 0);
    ASSERT_STD_EQ(0, "lllla");
}

TEST(redirect_std_failure_bis)
{
    REDIRECT_STD(0);
    write_n_char_in_std('l', 5, 0);
    ASSERT_STD_EQ(1, "lllla");
}

TEST(redirect_std_success)
{
    REDIRECT_STD(1);
    write_n_char_in_std('l', 5, 1);
    ASSERT_STD_EQ(1, "lllll");
}