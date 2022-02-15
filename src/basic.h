#ifndef BASIC_HEADER_GUARD
#define BASIC_HEADER_GUARD


// libc
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// small types
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


// DEFINE_ARRAY(type) macro
#define DEFINE_ARRAY(TYPE)\
\
struct TYPE ## _array { \
    TYPE* data; \
    int length; \
    int allocated; \
}; \
typedef struct TYPE ## _array TYPE ## _array;\
\
TYPE ## _array TYPE ## _array_make()\
{\
    TYPE ## _array arr;\
    arr.length = 0;\
    arr.allocated = 1000;\
    arr.data = (TYPE*)malloc( arr.allocated * sizeof(TYPE) );\
    return arr;\
}\
\
void TYPE ## _array_add(TYPE ## _array *arr, TYPE item)\
{\
    if ( arr->length == arr->allocated ) {\
      arr->allocated *= 2;\
      arr->data = (TYPE*)realloc( arr->data, arr->allocated * sizeof(TYPE) );\
    }\
    arr->data[arr->length] = item;\
    arr->length += 1;\
}\



// PRINT_ERROR Macros

#define PRINT_ERROR(msg) fprintf( stderr, "ERROR %s:%d %s\n", __FILE__, __LINE__, msg );

#define PRINT_ERROR_EXIT(msg) { fprintf( stderr, "ERROR %s:%d %s\n", __FILE__, __LINE__, msg ); exit(1); } 



#endif // BASIC_HEADER_GUARD
#ifdef BASIC_IMPLEMENTATION
#ifndef BASIC_IMPLEMENTATION_GUARD
#define BASIC_IMPLEMENTATION_GUARD








#endif // BASIC_IMPLEMENTATION_GUARD 
#endif // #ifdef BASIC_IMPLEMENTATION