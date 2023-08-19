#include <libc.h>
int main()
{
    char *p;
    p = strdup("yoel-bas");
    puts(p);
    free(p);
    free(p);
}