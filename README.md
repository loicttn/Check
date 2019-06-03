# check
Unit test C framework

compilation flags :  -Wl,--export-dynamic -ldl -l_name

tests/tests.c -Wl,--export-dynamic -L./ -ldl -lCheck -lpthread -D_REENTRANT -iquote./include/
