/*
 *  Author: Ardouin théo
 *  Create Time: 2019-06-02 01:20:49
 *  ;------------:
 *  Modified by: Ardouin théo
 *  Modified time: 2019-07-15 14:32:00
 *  Description:
 */

#ifndef INTERNAL_H_
#define INTERNAL_H_

#define RESET  "\x1b[0m"
#define RED    "\x1b[31m"
#define GREEN  "\x1b[32m"
#define BLUE   "\x1b[34m"
#define ORANGE "\033[0;33m"

#define STDIN  0
#define STDOUT 1
#define STDERR 2

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define concat_(a, b)    a##b
#define ck_concat(a, b)  concat_(a, b)

/* __VA_ARGS__ counter */

#define NB_ARGS(...)                                        \
        NB_ARGS_(__VA_ARGS__, PP_RSEQ_N())

#define NB_ARGS_(...)                                       \
        PP_ARG_N(__VA_ARGS__)

#define PP_ARG_N(                                           \
        _1, _2, _3, _4, _5, _6, _7, _8, _9,_10,             \
        _11,_12,_13,_14,_15,_16,_17,_18,_19,_20,            \
        _21,_22,_23,_24,_25,_26,_27,_28,_29,_30,            \
        _31,_32,_33,_34,_35,_36,_37,_38,_39,_40,            \
        _41,_42,_43,_44,_45,_46,_47,_48,_49,_50,            \
        _51,_52,_53,_54,_55,_56,_57,_58,_59,_60,            \
        _61,_62,_63,_64,_65,_66,_67,_68,_69,_70,            \
        _71,_72,_73,_74,_75,_76,_77,_78,_79,_80,            \
        _81,_82,_83,_84,_85,_86,_87,_88,_89,_90,            \
        _91,_92,_93,_94,_95,_96,_97,_98,_99,_100,           \
        _101,_102,_103,_104,_105,_106,_107,_108,_109,_110,  \
        _111,_112,_113,_114,_115,_116,_117,_118,_119,_120,  \
        _121,_122,_123,_124,_125,_126,_127,N,...) N

#define PP_RSEQ_N()                                         \
        127,126,125,124,123,122,121,120,                    \
        119,118,117,116,115,114,113,112,111,110,            \
        109,108,107,106,105,104,103,102,101,100,            \
        99,98,97,96,95,94,93,92,91,90,                      \
        89,88,87,86,85,84,83,82,81,80,                      \
        79,78,77,76,75,74,73,72,71,70,                      \
        69,68,67,66,65,64,63,62,61,60,                      \
        59,58,57,56,55,54,53,52,51,50,                      \
        49,48,47,46,45,44,43,42,41,40,                      \
        39,38,37,36,35,34,33,32,31,30,                      \
        29,28,27,26,25,24,23,22,21,20,                      \
        19,18,17,16,15,14,13,12,11,10,                      \
        9,8,7,6,5,4,3,2,1,0

/* control of out-going tests */

typedef enum ck_test_states_e {
    NONE,                           // test has not been run yet
    TEST_OK,                        // test has been validated
    TEST_KO,                        // test has failed
    TEST_CRASH,                     // test has crashed
    TEST_TIMEOUT,                   // test has taken too much time
} ck_test_state;

typedef struct ck_message_s {
    char *color;
    char *text;
    int   std;
    struct ck_message_s *next;
} ck_message_t;

typedef struct ck_exec_list_s {
    const char              *script;
    ck_test_state            condition;
    struct ck_exec_list_s   *next;
} ck_exec_list_t;

typedef struct ck_timeout_s {
    int                  usec;
    struct ck_timeout_s *next;
} ck_timeout_t;

typedef struct args_action_s {      // parse args to set up bonus test action
    ck_exec_list_t  *exec_l;        // specifics script to exec if the test is passed, failed, etc...
    ck_timeout_t    *tim_l;         // specifics redirection
} args_action_t;

/* Unit testing function list */

typedef struct ck_tests_list_s {
    args_action_t *action;          // parsed argument passed to test
    void (*fptr)(void);             // function pointers to test
    char  *test_name;               // name of the test
    ck_test_state test_state;       // out going of the test
    ck_message_t  *msg_l;           //associated message to print while test is luncher
    struct ck_tests_list_s *next;   // ptr to next test
} ck_tests_t;


/* function declaration */

void create_message(ck_message_t **msg, int std, const char *color, const char *text);
void display_messages(ck_message_t *msg_l);

ck_tests_t *ck_get_next_test_ptr(void *handle, int n);
ck_tests_t *ck_init_test_list(void);

#endif  /* !INTERNAL_H_ */