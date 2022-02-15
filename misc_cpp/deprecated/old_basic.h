#ifndef BASIC_HEADER_GUARD
#define BASIC_HEADER_GUARD

// Header only library
// ---------------------------

// Include this file like this
// #define BASIC_IMPLEMENTATION
// #include "basic.h"

// Only define BASIC_IMPLEMENTATION in *ONE* file.
// That's the file where the implementation will live.

#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <math.h>

// PRINT_ERROR macro with file and line number
#define PRINT_ERROR(msg) printf("ERROR %s %d %s\n",__FILE__,__LINE__,msg);


// ----------------------------------------------------------------
// Short Types 
// ----------------------------------------------------------------

typedef uint8_t     u8;
typedef int8_t      s8;
typedef uint16_t    u16;
typedef int16_t     s16;
typedef uint32_t    u32;
typedef int32_t     s32;
typedef uint64_t    u64;
typedef int64_t     s64;
typedef float       f32;
typedef double      f64;



// ----------------------------------------------------------------
// Type agnostic List datatype
// ----------------------------------------------------------------
// cause it's good enough for python

typedef struct list {
  void** data;
  int length;
  int allocated;
} List;


struct list make_list();
struct list append_list(struct list l, void* str);
// free(l.data);

// destructively split a string by converting delimiters into null bytes
// and noting down the positions after them.
struct list split_string(char *str, const char *delim);

extern int errno;

char* read_file(const char *filename);
int file_exists(const char * filename);
double time_elapsed(void);




// ----------------------------------------------------------------
// DEFINE_ARRAY(type) macro for typesafe expanding arrays 
// ----------------------------------------------------------------

// A macro for simple typesafe expanding arrays

// Example:
// To use it put something like this in the global scope. 
// DEFINE_ARRAY(int)

// Then use this kind of code
// int_array a = int_array_make();
// a = int_array_add(a, 23424234234);

// The type can be anything type that is a single word
// Each array type has a data and a length field


// Tips for using macros
// ------------------
// Use -E to see the outputs of macros
// gcc -E define_array_macro.c

// ## joins strings
// so str1 ## str2 becomes str1str2



#define DEFINE_ARRAY(TYPENAME)\
\
typedef struct {\
  TYPENAME* data;\
  int length;\
  int allocated;\
} TYPENAME ## _array;\
\
TYPENAME ## _array TYPENAME ## _array_make()\
{\
    TYPENAME ## _array arr;\
    arr.length = 0;\
    arr.allocated = 16;\
    arr.data = (TYPENAME*)malloc( arr.allocated * sizeof(TYPENAME) );\
    return arr;\
}\
\
TYPENAME ## _array TYPENAME ## _array_add(TYPENAME ## _array arr, TYPENAME item)\
{\
    if ( arr.length == arr.allocated ) {\
      arr.allocated *= 2;\
      arr.data = (TYPENAME*)realloc( arr.data, arr.allocated * sizeof(TYPENAME) );\
    }\
    arr.data[arr.length] = item;\
    arr.length += 1;\
    return arr;\
}\





#endif // BASIC_HEADER_GUARD

#ifdef BASIC_IMPLEMENTATION
#ifndef BASIC_IMPLEMENTATION_GUARD
#define BASIC_IMPLEMENTATION_GUARD






struct list make_list()
{
    struct list l;
    l.length = 0;
    l.allocated = 10;
    l.data = (void**)malloc( l.allocated * sizeof(void*) );
    return l;
}

struct list append_list(struct list l, void* str)
{
    l.data[l.length] = str;
    l.length += 1;
    if ( l.length == l.allocated ) {
      l.allocated *= 2;
      l.data = (void**)realloc( l.data, l.allocated * sizeof(void*) );
    }
    return l;
}

// free(l.data);







// destructively split a string by converting delimiters into null bytes
// and noting down the positions after them.
struct list split_string(char *str, const char *delim)
{
    // convert delimiters to null bytes
    size_t string_length = strlen(str);
    int i=0;
    for (i=0;i<string_length;i++) {
        for (int j=0;delim[j]!='\0';j+=1) {
            if (str[i]==delim[j]) { str[i] = '\0'; break; }
        }
    }

    // note down stuff after null bytes
    struct list l = make_list();
    if ( str[0] != '\0' ) l = append_list(l, str);
    for (i=1; i<string_length; i++ ) {
        if ( str[i-1] == '\0' && str[i] != '\0' ) l = append_list(l, str+i);
    }
    return l;
}

// ----------------------------------------------------------------
// Files
// ----------------------------------------------------------------



char* read_file(const char *filename)
{
    char *str;
    FILE *f = fopen(filename, "rb");
    if( !f ) { 
        printf( "ERROR %s %d %s\n", __FILE__,__LINE__, strerror(errno) ); 
        return NULL; 
    }
    fseek(f, 0, SEEK_END); // seek to end of file
    int size = ftell(f);   // get current file pointer
    fseek(f, 0, SEEK_SET); // seek back to beginning of file
    str = (char*)malloc(size * sizeof(char));
    fread(str, size, 1, f);
    fclose(f);

    return str;
}


int file_exists(const char * filename)
{
    /* try to open file to read */
    FILE *file;
    file = fopen(filename, "r");
    if (file){
        fclose(file);
        return 1;
    }
    return 0;
}



double time_elapsed(void)
{
	return ( (double)clock() ) / ( (double)CLOCKS_PER_SEC );
}








// // DEFINE_ARRAY(TYPENAME) Demo

// DEFINE_ARRAY(f64)
// DEFINE_ARRAY(char)
// typedef struct { int x; int y; } arbitrary_type;
// DEFINE_ARRAY(arbitrary_type)
// typedef void* voidptr;
// DEFINE_ARRAY(voidptr)

// int main()
// {
//     // int a;
//     // a = sqr(64);
//     // printf("%d\n", a);

//     f64_array arr = f64_array_make();
//     int i;
//     for(i=0;i<100;++i) arr = f64_array_add(arr, i);
//     for(i=0;i<100;++i) printf("%f ", arr.data[i]);
//     printf("\n");

//     char_array arr2 = char_array_make();
//     char c;
//     for(c=0;c<100;++c) arr2 = char_array_add(arr2, c+65);
//     for(i=0;i<100;++i) printf("%c ", (int)arr2.data[i]);
//     printf("\n");


//     arbitrary_type_array arr3 = arbitrary_type_array_make();
//     for(i=0;i<100;++i) { 
//         arbitrary_type a;
//         a.x = i;
//         a.y = 2*i;
//         arr3 = arbitrary_type_array_add(arr3, a);
//     }
//     for(i=0;i<100;++i) printf("[%d %d] ", arr3.data[i].x, arr3.data[i].y);
//     printf("\n");


//     voidptr_array arr4 = voidptr_array_make();
//     for(s64 i=0;i<100;++i) arr4 = voidptr_array_add(arr4, (voidptr)i);
//     for(i=0;i<100;++i) printf("%d ", (int)arr4.data[i]);
//     printf("\n");

//     return 0;
// }






int basic_main(int argc, char **argv)
{

    char string[] = "nicolas schmidt,0459 986 668,some address\nsingle female lawyer,3325 7778,another address\nomgomgomg,0459654987,omg it's like everyone has an address\n";
    struct list list;
    list = split_string(string,",\n");
    for(int i=0;i<list.length;i+=1) printf("%s\n", (char*)list.data[i]);

    return 0;
}





#endif // BASIC_IMPLEMENTATION_GUARD 
#endif // #ifdef BASIC_IMPLEMENTATION

