/*
 *  Author: Ardouin théo
 *  Create Time: 2019-05-25 19:31:15
 *  ;------------:
 *  Modified by: Ardouin théo
 *  Modified time: 2019-05-25 19:43:52
 *  Description:
 */

#include <dlfcn.h>
#include <stdio.h>
#include <stddef.h>

int main(void)
{
    void *handle = dlopen(NULL, RTLD_LAZY);

    void *fptr = dlsym(handle, "test_1");
    int (*f)() = fptr;
    f();
}
