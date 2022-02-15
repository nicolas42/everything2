// g++ string_builder_demo.cpp -I../include -Wfatal-errors -Wall && ./a.out 


#include "libc.h"
// #include "stb_sprintf.h"

struct string { 
    char* data; 
    int length; 
    int allocated; 
}; 
typedef struct string string_t;

string_t string_make()
{
    string_t str;
    str.length = 0;
    str.allocated = 10;
    str.data = (char*)malloc( str.allocated * sizeof(char) );
    return str;
}

void string_add(string_t *str, char character)
{
    if ( str->length == str->allocated ) {
      str->allocated *= 2;
      str->data = (char*)realloc( str->data, str->allocated * sizeof(char) );
    }
    str->data[str->length] = character;
    str->length += 1;
}


void string_add(string_t *str, const char *str2)
{
    for ( int i=0; str2[i]!='\0'; i+=1 ) {
        string_add( str, str2[i] );
    }
}


void string_add(string_t *str, int num_args, ... ) 
{
    char *str2;
    va_list ap;
    int i;

    va_start(ap, num_args);
    for(i = 0; i < num_args; i++) {
        str2 = va_arg(ap, char*);

        for ( int i=0; str2[i]!='\0'; i+=1 ) {
            string_add( str, str2[i] );
        }

    }
    va_end(ap);

}



int main()
{

    // string_add can take a char, a string, or a variadic argument list of strings.

    // string_add can only add a null byte when adding a char.
    

    string_t s = string_make();
    string_add( &s, 'h');
    string_add( &s, "i ");

    char str1[] = "You say goodbye but I say hello. Hello, hello.\n";
    char str2[] = "I don't know why you say goodbye, I say hello\n";
    char str3[] = "Immutable truths deserve immutable strings.\n";

    string_add( &s, str1 );
    string_add( &s, str2 );
    string_add( &s, str3 );
    string_add( &s, "Oh my god it's even another string\n" );
    // string_add( &s, '\0' );


    string_add( &s, 4, str1, str2, str3, "\0" );

    const char os_sep[2] = "/";
    string_add( &s, 5, "\nfile: some_folder", os_sep, "another_folder", os_sep, "filename.extension\n" );

    string_add( &s, str2 );


    string_add(&s, '\0');

    printf("%s\n", s.data);

    free(s.data);

    return 0;
}