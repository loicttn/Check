# check
Unit test C framework

make re && gcc tests/tests.c -Wl,--export-dynamic -L./ -ldl -lCheck -lpthread -D REENTRANT -iquote./include/
