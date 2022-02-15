/*
cl /Zi /MD demo_function_overloading.cpp
rm *.ilk *.obj *.pdb

function overloading doesn't work based on the return type.

It doesn't appear to help with type safety.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void print(char a)
{
    printf("%c ",a);
}

void print(int a)
{
    printf("%d ",a);
}

void print(float a)
{
    printf("%.20f ",a);
}

void print(double a)
{
    printf("%.40f ",a);
}





#define DEFINE_ARRAY(TYPENAME)                                                                  \
                                                                                                \
typedef struct {                                                                                \
  TYPENAME* data;                                                                               \
  int length;                                                                                   \
  int allocated;                                                                                \
} TYPENAME ## _array;                                                                           \
                                                                                                \
                                                                                                \
TYPENAME ## _array append(TYPENAME ## _array arr, TYPENAME item)                \
{                                                                                               \
    if ( arr.length == arr.allocated ) {                                                        \
      arr.allocated *= 2;                                                                       \
      arr.data = (TYPENAME*)realloc( arr.data, arr.allocated * sizeof(TYPENAME) );              \
    }                                                                                           \
    arr.data[arr.length] = item;                                                                \
    arr.length += 1;                                                                            \
    return arr;                                                                                 \
}                                                                                               \


DEFINE_ARRAY(char)
DEFINE_ARRAY(int)




int main( int argc, char* args[] )
{
    int a = 1;
    float b = 1;
    double c = 1;

    print(a); 
    print(b);
    print(c);

    int num_iterations = 1000;
    {
        char_array arr;
        arr.length = 0;        
        arr.allocated = 16;    
        arr.data = (char*)malloc( arr.allocated * sizeof(char) ); 

        for(int i=0;i<num_iterations;i+=1) arr = append(arr, (char)((i%26)+65) );

        for(int i=0;i<num_iterations;i+=1) print(arr.data[i]);

    }

    {
        int_array arr;
        arr.length = 0;        
        arr.allocated = 16;    
        arr.data = (int*)malloc( arr.allocated * sizeof(int) ); 

        for(int i=0;i<num_iterations;i+=1) arr = append(arr, i );

        for(int i=0;i<num_iterations;i+=1) print(arr.data[i]);


    }
    return 0;
}
