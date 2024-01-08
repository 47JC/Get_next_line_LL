#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    char *p;

    p = argv[1];

    printf("p = %c\n", *p);
}