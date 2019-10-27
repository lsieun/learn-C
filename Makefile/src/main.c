#include <stdio.h>
#include "head.h"

int main(int argc, char* argv[])
{
    int a = 20;
    int b = 30;
    int sum = add(a, b);
    printf("=========================\n");
    printf("%d + %d = %d\n", a, b, sum);
    printf("=========================\n");
    return 0;
}
