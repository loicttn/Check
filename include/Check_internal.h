/*
 *  Author: Ardouin théo
 *  Create Time: 2019-06-02 01:20:49
 *  ;------------:
 *  Modified by: Ardouin théo
 *  Modified time: 2019-06-03 03:31:36
 *  Description:
 */

#ifndef INTERNAL_H_
#define INTERNAL_H_

#define RESET "\x1b[0m"
#define RED   "\x1b[31m"
#define GREEN "\x1b[32m"
#define BLUE  "\x1b[34m"

#define STDIN  0
#define STDOUT 1
#define STDERR 2

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define concat_(a, b)    a##b
#define ck_concat(a, b)  concat_(a, b)



/* control of out-going tests */

typedef enum ck_test_states_e {
    NONE            =   0,          // test has not been run yet
    TEST_OK         =   1,          // test has been validated
    TEST_KO         =   -1,         // test has failed
    TEST_CRASH      =   -2,         // test has crashed
    TEST_TIMEOUT    =   -3,         // test has taken too much time
} ck_test_state;


/* Unit testing function list */

typedef struct ck_tests_list_s {
    void (*fptr)(void);             // function pointers to test
    char  *test_name;               // name of the test
    ck_test_state test_state;       // out going of the test
    struct ck_tests_list_s *next;   // ptr to next test
} ck_tests_t;


/* function declaration */

ck_tests_t *get_next_test_ptr(void *handle, int n);
ck_tests_t *init_test_list(void);

#endif  /* !INTERNAL_H_ */