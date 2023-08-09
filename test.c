#include <libc.h>
    void func() {system("leaks a.out");}
int main() {
    atexit(func);
    char *s = malloc (1);
    long long i = 0;
    while (i < 1000000000000)
        i++;
        return (0);
}
