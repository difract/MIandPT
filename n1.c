#include <stdio.h>

int main()
{
    freopen("nn.txt", "a+", stdout);
    freopen("nn.txt", "a+", stderr);
    fputs("STDOUT\n", stdout);
    //fflush(stdout);
    fputs("STDERR\n", stderr);
    //fflush(stderr);
    return 0;
}
