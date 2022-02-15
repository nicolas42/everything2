
#include <stdio.h>
#include <stdlib.h>
#include "../src/basic.h"


int main()
{
    int a = 0;
    if (!a) PRINT_ERROR("omg!\n");

    int b = 23;
    if (b == 23) PRINT_ERROR_EXIT("omg you!\n")

    PRINT_ERROR("You shouldn't see this\n");

    return 0;
}
