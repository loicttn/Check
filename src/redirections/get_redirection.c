#include "Check_tests_creator.h"
#include "Check_redirections.h"
#include "Check_run_tests.h"
#include <string.h>

static int fds[3][2] = {
    {0, 0},
    {0, 0},
    {0, 0}
};

void ck_redirect_std(int std)
{
    if (std < 0 || std > 3)
        return;
    if (pipe(fds[std]) == -1) {
        dprintf(2, RED"FATAL ERROR : can't execute pipe."RESET);
        exit(TEST_KO);
    }
    dup2(fds[std][CK_IN], std);
}

void ck_assert_std(int std, char *cmp)
{
    char c = 0;
    int cmp_len = 0;
    int read_chars = 0;

    if (cmp == NULL)
        return;
    cmp_len = strlen(cmp);
    close(fds[std][CK_IN]);
    for (int i = 0; i < cmp_len; i += 1) {
        read_chars = read(fds[std][CK_OUT], &c, 1);
        if (read_chars != 1 || i == cmp_len) {
            close(fds[std][CK_OUT]);
            exit(TEST_KO);
        }
        if (c != cmp[i]) {
            dprintf(STDERR, "%c != %c\n", c, cmp[i]);
            close(fds[std][CK_OUT]);
            exit(TEST_KO);
        }
    }
    close(fds[std][CK_IN]);
    exit(TEST_OK);
}