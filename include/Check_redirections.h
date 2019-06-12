#ifndef CK_REDIRECT_H
#define CK_REDIRECT_H

enum {
    CK_OUT = 0,
    CK_IN = 1
};

void ck_redirect_std(int std);
void ck_assert_std(int std, char *cmp);

#define REDIRECT_STD(std) ck_redirect_std(std)
#define ASSERT_STD_EQ(std, cmp) ck_assert_std(std, cmp)

#endif