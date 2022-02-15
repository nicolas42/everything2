

#include <stdio.h>
#include <stdlib.h>

#include "../src/basic.h"

DEFINE_ARRAY(f64)
DEFINE_ARRAY(char)
typedef struct { int x; int y; } arbitrary_type;
DEFINE_ARRAY(arbitrary_type)
typedef void* voidptr;
DEFINE_ARRAY(voidptr)


int main()
{
    f64_array arr = f64_array_make();
    int i;
    for(i=0;i<100;++i) f64_array_add(&arr, i);
    printf("[ ");
    for(i=0;i<100;++i) printf("%f ", arr.data[i]);
    printf("]\n\n");

    char_array arr2 = char_array_make();
    char c;
    for(c=0;c<100;++c) char_array_add(&arr2, c+65);
    printf("[ ");
    for(i=0;i<100;++i) printf("%c ", arr2.data[i] );
    printf("]\n\n");


    arbitrary_type_array arr3 = arbitrary_type_array_make();
    for(i=0;i<100;++i) { 
        arbitrary_type a;
        a.x = i;
        a.y = 2*i;
        arbitrary_type_array_add(&arr3, a);
    }
    printf("[ ");
    for(i=0;i<100;++i) printf("[%d %d] ", arr3.data[i].x, arr3.data[i].y);
    printf("]\n\n");


    voidptr_array arr4 = voidptr_array_make();
    for(s64 i=0;i<100;++i) voidptr_array_add(&arr4, (voidptr)i);
    printf("[ ");
    for(i=0;i<100;++i) printf("%lld ", (s64)arr4.data[i] );
    printf("]\n\n");

    return 0;
}



