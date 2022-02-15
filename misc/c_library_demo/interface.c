// How to do namespaces in ANSI C
// https://stackoverflow.com/questions/4396140/why-doesnt-ansi-c-have-namespaces

// /* interface.h */
// #include <stdio.h>

// struct library {
//     const int some_value;
//     void (*method1)(void);
//     void (*method2)(int);
//     /* ... */
// };

// extern const struct library Library;
// /* interface.h */

/* interface.c */
#include "interface.h"

void method1(void)
{
   printf("method1 ");
}
void method2(int arg)
{
   printf("method2 ");
}

const struct library Library = {
    .method1 = method1,
    .method2 = method2,
    .some_value = 36
};


/* end interface.c */

// /* client code */
// // #include "interface.h"

// int main(void)
// {
//     Library.method1();
//     Library.method2(5);
//     printf("%d\n", Library.some_value);
//     return 0;
// }
// /* end */
