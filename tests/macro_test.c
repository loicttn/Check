/*


testing


*/


#include "Check.h"
#include <stdarg.h>
#include <stdio.h>

#define foo(...)    \
    foo_(__VA_ARGS__)

#define foo_(X, ...)    \
    foo__(#X, 1, __VA_ARGS__)

#define foo__(name, X...)   \
    foo___(name, #X + 2)

void foo___(const char *name, const char *args)
{
    printf("name %s\nargs %s\n", name, args);
}

void main(void)
{

    foo(1);
    printf("\n");

}















/*
#include "Check.h"
#include <stdarg.h>

#define __foo(...)  \
    _foo(FIRSTARG(__VA_ARGS__), 1, RESTARGS(__VA_ARGS__))

#define _foo(name, X...) \
    foo(#name, #X)

#define foo(name, X) \
    foo__(name, X)

int foo__(const char *name, const char *arg)
{
    printf("%s, args > %s\n", name, arg);
}

main()
{
    printf("a\n");
    __foo(1);
}
*/

















/*

#include "Check.h"
#include <stdarg.h>

#define __foo(...)  \
    _foo(FIRSTARG(__VA_ARGS__), 1, __VA_ARGS__)

#define _foo(name, ...) \
    foo(name, __VA_ARGS__ )

#define foo(name, ...) \
    foo_(NB_ARGS(__VA_ARGS__), name, __VA_ARGS__)

#define foo_(len, name, ...) \
    foo__(#name, len - 2, __VA_ARGS__)

int foo__(const char *name, int len, ...)
{
    va_list va;
    va_start(va, len);
    va_arg(va, int);

    printf("%d\n > len = %d\n", va_arg(va, int), len);
    for (int i = 0; i < len; i++)
    {
        printf("%d\n\n", va_arg(va, int));
    }
    va_end(va);
}

main()
{
    printf("a\n");
    __foo(2, 4, 3, 6, 7, 8, 2);
}


*/