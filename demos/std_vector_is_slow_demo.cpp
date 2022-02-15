// g++ std_vector_is_slow_demo.cpp -Ofast && ./a.out

// std::vector is more than 2X slower than a simple expanding array implementation

#include <vector>
#include <stdint.h>

typedef uint32_t test_t;

struct test_t_array { test_t* data; int length; int allocated; }; 
typedef struct test_t_array test_t_array;

test_t_array test_t_array_make()
{
    test_t_array arr;
    arr.length = 0;
    arr.allocated = 16;
    arr.data = (test_t*)malloc( arr.allocated * sizeof(test_t) );
    return arr;
}

void test_t_array_add(test_t_array *arr, test_t item)
{
    if ( arr->length == arr->allocated ) {
      arr->allocated *= 2;
      arr->data = (test_t*)realloc( arr->data, arr->allocated * sizeof(test_t) );
    }
    arr->data[arr->length] = item;
    arr->length += 1;
}

// copy semantics
test_t_array test_t_array_add2(test_t_array arr, test_t item)
{
    if ( arr.length == arr.allocated ) {
      arr.allocated *= 2;
      arr.data = (test_t*)realloc( arr.data, arr.allocated * sizeof(test_t) );
    }
    arr.data[arr.length] = item;
    arr.length += 1;
    return arr;
}


int main()
{
    int i;
    time_t t0 = clock();

    std::vector<test_t> std_vector;
    for(i=0;i<500*1000*1000;i+=1) std_vector.push_back(i);

    time_t t1 = clock();
    
    test_t_array arr = test_t_array_make();
    for(i=0;i<500*1000*1000;i+=1) test_t_array_add( &arr, i );

    time_t t2 = clock();

    test_t_array arr2 = test_t_array_make();
    for(i=0;i<500*1000*1000;i+=1) arr2 = test_t_array_add2( arr2, i );

    time_t t3 = clock();

    printf("\n\n");
    printf("std_vector\n");
    printf("duration: %f\n", ((double)( t1 - t0 )) / (double)CLOCKS_PER_SEC );
    printf("my expanding array\n");
    printf("duration: %f\n", ((double)( t2 - t1 )) / (double)CLOCKS_PER_SEC );
    printf("my expanding array with copy semantics\n");
    printf("duration: %f\n", ((double)( t3 - t2 )) / (double)CLOCKS_PER_SEC );

    return 0;
}



