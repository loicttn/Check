# check
### Unitary test C library

## Getting started
```bash
make re && gcc tests/tests.c -Wl,--export-dynamic -L./ -ldl -lCheck -lpthread -D REENTRANT -iquote./include/
```

## Credentials
PoC, Naoufel BERRADA (for his beauty), HoopDB for being here

## License
none for the moment
