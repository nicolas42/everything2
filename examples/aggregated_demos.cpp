// g++ aggregated_demos.cpp -Ofast -Wfatal-errors


// g++ aggregated_demos.cpp -Iinclude -Ofast -Weverything -Wno-missing-prototypes -Wno-old-style-cast -Wno-double-promotion
// g++ aggregated_demos.cpp -Iinclude -Ofast -fPIC -Wall -Wpedantic -Wextra -Wvla -Wshadow -Wfatal-errors -Werror
// clang++ -std=c++11 aggregated_demos.cpp -Iinclude -Ofast -Weverything -Wno-missing-prototypes -Wno-old-style-cast -Wno-double-promotion -Wfatal-errors

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* caesar_cipher(char* text, int shift)
{
    char* code = (char*)calloc(strlen(text)+1, sizeof(char));

    shift %= 26;

    for (size_t i = 0; i < strlen(text); i++) {

        if (text[i] >= 'a' && text[i] <= 'z') {

            if (text[i]+shift >= 128) {
                shift -= 26;
            }

            code[i] = (char)(text[i]+shift);

            if (code[i] < 'a') {
                code[i] += 26;
            } else if (code[i] > 'z') {
                code[i] -= 26;
            }

        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            code[i] = (char)(text[i]+shift);

            if (code[i] < 'A') {
                code[i] += 26;
            } else if (code[i] > 'Z') {
                code[i] -= 26;
            }

        } else {
            code[i] = text[i];
        }
    }

    return code;
}

int caesar_cipher_demo()
{
    printf(
        "\n\ncaesar_cipher_demo\n"
        "--------------------------\n"
    );

    char text[] = "The quick brown fox jumps over the lazy dog.";
    int shift = 13;

    printf("\"%s\"\n", text );
    printf("\"%s\"\n",caesar_cipher(text, shift));
    return 0;
}





#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* vigenere_cipher(char *plaintext, const char *key)
{

    char table[27][27] = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
    "BCDEFGHIJKLMNOPQRSTUVWXYZA",
    "CDEFGHIJKLMNOPQRSTUVWXYZAB",
    "DEFGHIJKLMNOPQRSTUVWXYZABC",
    "EFGHIJKLMNOPQRSTUVWXYZABCD",
    "FGHIJKLMNOPQRSTUVWXYZABCDE",
    "GHIJKLMNOPQRSTUVWXYZABCDEF",
    "HIJKLMNOPQRSTUVWXYZABCDEFG",
    "IJKLMNOPQRSTUVWXYZABCDEFGH",
    "JKLMNOPQRSTUVWXYZABCDEFGHI",
    "KLMNOPQRSTUVWXYZABCDEFGHIJ",
    "LMNOPQRSTUVWXYZABCDEFGHIJK",
    "MNOPQRSTUVWXYZABCDEFGHIJKL",
    "NOPQRSTUVWXYZABCDEFGHIJKLM",
    "OPQRSTUVWXYZABCDEFGHIJKLMN",
    "PQRSTUVWXYZABCDEFGHIJKLMNO",
    "QRSTUVWXYZABCDEFGHIJKLMNOP",
    "RSTUVWXYZABCDEFGHIJKLMNOPQ",
    "STUVWXYZABCDEFGHIJKLMNOPQR",
    "TUVWXYZABCDEFGHIJKLMNOPQRS",
    "UVWXYZABCDEFGHIJKLMNOPQRST",
    "VWXYZABCDEFGHIJKLMNOPQRSTU",
    "WXYZABCDEFGHIJKLMNOPQRSTUV",
    "XYZABCDEFGHIJKLMNOPQRSTUVW",
    "YZABCDEFGHIJKLMNOPQRSTUVWX",
    "ZABCDEFGHIJKLMNOPQRSTUVWXY",
    };

    size_t key_length = strlen(key);

    char *ciphertext = (char*)calloc( strlen(plaintext)+1, sizeof(char) );
    if (!ciphertext) { 
        printf("ERROR %s %d %s\n", __FILE__, __LINE__, "Couldn't allocate memory"); // Don't look at me like that.  It could happen.
        exit(1);
    }
    int ciphertext_length = 0;

    for ( size_t i=0; plaintext[i] != '\0'; i+=1 ) {
        int y = toupper( plaintext[i] ) - 65;
        int x = toupper( key[i % key_length] ) - 65;
        ciphertext[ciphertext_length++] = table[y][x];
    }
    ciphertext[ciphertext_length] = '\0';


    return ciphertext;
}

void vigenere_cipher_demo()
{

    printf("\n\n");
    printf("vigenere_cipher_demo\n");
    printf("-----------------------\n");

    char plaintext[] = "attackatdawn";
    char key[] = "LEMON";
    char *ciphertext = vigenere_cipher(plaintext, key);
    
    if ( strcmp(ciphertext, "LXFOPVEFRNHR") ) printf("ERROR");
    
    printf("%s\n%s\n", plaintext, ciphertext);

}






#include <stdio.h>
#include <string.h>

void strtok_demo(void)
{

    printf("\n\n");
    printf("strtok_demo\n");
    printf("-----------------------\n");

    char str[] = 
    "Return Value\n"
    "This function returns a pointer to the first token found in the string. \n"
    "A null pointer is returned if there are no tokens left to retrieve.\n"
    "\n"
    "Example\n"
    "The following example shows the usage of strtok() function.\n"
    "\n";


    // strtok uses a static for the string after it's initialized
    for (char *p = strtok(str,"\n"); p != NULL; p = strtok(NULL, "\n")){
        printf("{%s}\n", p);
    }

}


#include <stdarg.h>
// https://www.tutorialspoint.com/c_standard_library/c_macro_va_start.htm

int variadic_sum(int num_args, ...)
{
   int val = 0;
   va_list ap;
   int i;

   va_start(ap, num_args);
   for(i = 0; i < num_args; i++) {
      val += va_arg(ap, int);
   }
   va_end(ap);
 
   return val;
}

int variadic_sum_demo(void)
{
    printf("\n\n");
    printf("variadic_sum_demo\n");
    printf("-----------------------\n");

   printf("Sum of 10, 20 and 30 = %d\n",  variadic_sum(3, 10, 20, 30) );
   printf("Sum of 4, 20, 25 and 30 = %d\n",  variadic_sum(4, 4, 20, 25, 30) );

   return 0;
}




#include <stdio.h>
#include <stdio.h>
#include <math.h>

// float f_dash(float x, float y, float *dx, float *dy) { return y; }

int eulers_method_demo()
{
    printf("\n\n");
    printf("Euler's Method for solving differential equations and vector fields\n");
    printf("---------------------------------------------------------------------\n");

    // Euler's Method for solving a differential equation
    // ---------------------------------------------------
    // start at a point.  calculate the slope
    // follow the slope to the next point
    // repeat

    // y1 = dydx(x0,y0) * delta_x + y0;
    // x1 = x0 + delta_x;

    // khan https://www.youtube.com/watch?v=q87L9R9v274



    //  {
    //     // Example: Draw the line y = e^x from its vector field 
    //     // dy_dx = y, y(0) = 1

    //     double x = 0;
    //     double y = 1;
    //     double slope = y; 
    //     double delta_x = 0.0001;

    //     for (int i = 0; i < 1.0/delta_x; i += 1)
    //     {

    //         slope = y;
    //         y = y + slope * delta_x;
    //         x = x + delta_x;
    //         printf("x, y, slope: [ %f %f %f ]\n", x, y, slope);
    //     }
    //     // output 
    //     // x, y, slope: [ 1.0000 2.7181 2.7179 ]
    //     // yahoo!!
    // }



    {   
        // Example: Draw a circle using the vector field < -y, x >

        double x = 1;
        double y = 0;
        double dx = -y;
        double dy = x;
        double step = 0.0001;
        const double TWOPI = 6.28318530718;

        printf("Drawing a circle using the vector field < -y, x >\n");
        printf("Starting point\n");
        printf("x, y, dx, dy: [ %f %f %f %f %f ]\n", x, y, dx, dy, step);

        for (int i = 0; i < TWOPI/step; i += 1)
        {
            dx = -y;
            dy = x;

            y = y + dy * step;
            x = x + dx * step;
            // printf("x, y, dx, dy: [ %f %f %f %f %f ]\n", x, y, dx, dy, step);
        }
        printf("End point\n");
        printf("x, y, dx, dy: [ %f %f %f %f %f ]\n", x, y, dx, dy, step);

        // output 
        // using float
        // x, y, dx, dy: [ 1.000314 0.000015 0.000085 1.000314 0.000100 ]
        // using double
        // x, y, dx, dy: [ 1.000316 0.000015 0.000085 1.000316 0.000100 ]


    }




    // Conservative Vector Fields
    // -----------------------------------------

    // A conservative vector field is one that has an associated scalar field.
    // that can be found by integrating all of the partial derivative equations

    // Here's a scalar field
    // f(x,y) = 1/4 x4y4 + 1/2 x2 + 1/2 y2 ) + c

    // The associated vector field is the gradient of f 
    // grad f(x,y) = dfdx(x,y) i  + dfdy(x,y) j 

    // let fx be dfdx and fy be dfdy

    // fx = x3y4 + x
    // fy = x4y3 + y


    // A vector field is conservative if you can integrate all of the gradient
    // components into the same scalar field
    // of if you take several derivatives with respect to the different variables
    // in all the different orders and they're all the same.



    return 0;
}





int newtons_method_demo()
{

    printf("\n\n");
    printf("newtons_method_demo\n");
    printf("-----------------------\n");


    // Newton's Method for solving equations of one variable
    // ---------------------------------------------------------

    // Newton's method can find real solutions to differentiable functions.
    // It will find an input value that will produce the given output value.

    // It requires that a starting x value is initially chosen.  
    // 1. The corresponding y value is easily found.
    // 2. It draws a tangent line from this point, which is followed to where it intersects
    // 3. with the x-axis.  The algorithm repeats

    // The equation of a tangent line going through ( x0, f(x0) )

    // f(x) - f(x0) = f'(x0) * ( x - x0 )

    // To find the x intercept set f(x) = 0 and solve for x. This new x value
    // is hopefully closer to a solution than the previous one.

    // x = x0 - f(x0) / f'(x0)



    // This can solve any equation of the form y = f(x).

    // Different initial conditions will give different solutions, if there are multiple.

    // Simply 
    // 1. Put the equation into homogenous form f(x) = 0
    // 2. set the initial x value
    // 3. Run the algorithm for a certain number of iterations

    // The technique is to calculate the height and derivative at the current x value
    // and follow them down to the next x value at the x-axis.
    
    // The way that polynomials curve means that this technique should bring you 
    // closer and closer to one of the closest roots of the equation.


    // set x to some value, say 0.
    // x = x - ( f(x) / f'(x) )
    double x = 0;
    for (int i=0; i<10; ++i) {
        x = x - ( (x*x + 5*x -20) / (2*x + 5) );
    }
    printf("newton's method x: %f\n", x);
    
    return 0;
}



#include <stdio.h>
#include <unistd.h>

void print_stuff_on_one_line_demo()
{
    printf("\n\n");
    printf("print_stuff_on_one_line_demo\n");
    printf("-----------------------------------\n");

    int i;    
    for (i=0;i<100;++i) { 
        fprintf(stdout, "\romg I'm printing stuff on one line [%d%%]", i ); 
        fflush(stdout); 
        usleep(1e4); 
    } 
    printf("\n");
}






#include <stdio.h>
// #include <ctype.h>
#include <stdlib.h>


void read_file (char *filename, char **ret_char_array, size_t *ret_char_length)
{
	// string
    char *char_array = (char*)malloc(1000);
	size_t chars_allocated = 1000;
	size_t char_length = 0;
	
    // open file for reading
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		char err[200];
		snprintf(err, 200, "Error in opening file %s", filename);
		perror(err);
		return;
	}

	while (1) {
		// read character
		int character = fgetc(f);
		// at the end of the file add a null byte to work with c-string functions
		if (feof(f)) { 
			char_array[char_length] = '\0'; 
			char_length += 1;
			break; 
		}
		char_array[char_length] = (char)character;
		char_length += 1;

        // maybe grow string
        if (char_length == chars_allocated){
            chars_allocated *= 2;
            char_array = (char*)realloc(char_array, chars_allocated);
            // printf("chars_allocated %d\n", chars_allocated);
        }

	}
	fclose(f);
	
    *ret_char_array = char_array;
    *ret_char_length = char_length;
}



static void print_escape_char( char the_char)
{

    switch (the_char) {

        case '\n':
            printf("\\n");
            break;
        case '\r':
            printf("\\r");
            break;
        case '\t':
            printf("\\t");
            break;
        default:
            if ((the_char < 0x20) || (the_char > 0x7f)) {
                printf("\\%03o", (unsigned char)the_char);
            } else {
                printf("%c", the_char);
            }
        break;
   }
}



int read_file_demo()
{

    printf("\n\n");
    printf("read_file_demo\n");
    printf("-----------------------------------\n");

	// __FILE__ appears to be the filename of this file
	// putting two string immediately next to each other concatenates them in c
	// "./"__FILE__
	// or "alskjdf""alksjdflka" => "alskjdfalksjdflka"

    char *data = NULL; 
	size_t length;
	char *filename = (char*)__FILE__; // the filename of this file

	printf("reading %s\n", filename);


    read_file( filename , &data, &length );

	// print slice
	int start = 0;
	int end   = 100;

	fputs("\n{", stdout);
	for (int i=start; i<end; ++i) print_escape_char( data[i] );
	fputs("}", stdout);
	printf("\n");



	free(data);
    return 0;
}





extern int errno;

int read_file2 ( const char *filename, char **ret_str, size_t *ret_length)
{
	size_t allocated = 1024;
	size_t length = 0;
    char *str = (char*)malloc(allocated);
	
	FILE *file = fopen(filename, "r");
    if (!file) { 
        printf( "ERROR %s:%d %s\n", __FILE__,__LINE__, strerror(errno) ); 
        exit(0);
    }

	while (1) {
		int character = fgetc(file);
		if (feof(file)) { 
			str[length++] = '\0'; 
			break; 
		}
        if (length == allocated){
            allocated *= 2;
            str = (char*)realloc(str, allocated);
        }
		str[length++] = (char)character;

	}
	fclose(file);
	
    *ret_str = str;
    *ret_length = length;

    return 0;
}



void read_file2_demo()
{
    printf("\n\n");
    printf("read_file2_demo\n");
    printf("-----------------------\n");

    const char *filename = __FILE__;
    char *str;
    size_t len = 0;
    read_file2(filename, &str, &len);

    printf("{");
    for(int i=0;i<100;i+=1) putc( str[i], stdout );
    printf("...}\n");
}







// Operating on the same data using different threads
//
// The intended behaviour of this program is to add 1 to a global variable 
// until it's 1000.  When several threads are used to achieve this there is
// unintended behaviour.  If two threads read the global at the same time
// then the final value of the global will be less than 1000.

// If this code is made mutually exclusive, i.e. it can only be run by 
// one thread at any given time, then this is fixed.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

static int thread_race_global = 0;
// static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* add1_to_global(void*)
{
	// pthread_mutex_lock(&mutex);
	thread_race_global += 1; // read and then write back it+1 to the same location
	// pthread_mutex_unlock(&mutex);
	pthread_exit(0);

}

void thread_race_demo()
{

    printf("\n\n");
    printf("thread_race_demo\n");
    printf("-----------------------------------\n");

    printf("\n\n");
	printf("1000 threads are adding 1 to a global.  \n");
    printf("A result less than 1000 indicates a race condition.\n");

	for (int thread_race = 0; thread_race < 10; thread_race++){
		
		printf("Thread Race %d: ", thread_race);

		thread_race_global = 0;
		// Launch threads
		pthread_t threads[1000];
		for (int i = 0; i < 1000; i++) {
			pthread_attr_t attr;
			pthread_attr_init(&attr);
			pthread_create(&threads[i], &attr, add1_to_global, NULL);
		}

		// Wait for threads
		for (int i = 0; i < 1000; i++) {
			pthread_join(threads[i], NULL);
		}

		printf("Result is %d\n", thread_race_global);
		if (thread_race_global != 1000){ 
            printf("Race condition!\n");
            break; 
        }
	}

}



#include <iostream>
#include <vector>
#include <string>
 
int cpp_vector_demo()
{

    printf("\n\n");
    printf("cpp_vector_demo\n");
    printf("-----------------------------------\n");

    using namespace std;

    // integers
	vector<int> integers;
    integers.push_back(1);
    integers.push_back(2);
    integers.push_back(4);
    integers.push_back(8);
    integers.push_back(16);
 
    integers.push_back(25);
    integers.push_back(13);
 
    cout << "integers" << endl;
    for(uint32_t i=0;i<integers.size();++i) { cout << integers[i] << '\n'; }

    cout << "\nStrings\n";
	vector<string> fruits;
    fruits.push_back("orange");
    fruits.push_back("apple");
    fruits.push_back("raspberry");

    for(uint32_t i=0;i<fruits.size();++i) { cout << fruits[i] << '\n'; }

    cout << "\ndemo for loop, count, other things like this\n";
    cout << "size " << fruits.size() << endl;


    return 0;
}





// https://www.reddit.com/r/Cprog/comments/kaapdr/prints_itself/
int print_this_file()
{
    FILE *file = fopen(__FILE__, "r");
    for (;;) {
        while (!feof(file)) {
            usleep(10*1000);
            fputc(fgetc(file), stderr);
        }
        rewind(file);
    }
}









// C89 allows two types of compilers: hosted and freestanding. The basic difference is that a 
// hosted compiler provides all of the C89 library, while a freestanding compiler need only 
// provide <float.h>, <limits.h>, <stdarg.h>, and <stddef.h>. If you limit yourself to these headers, 
// your code will be portable to any C89 compiler.


#include <stdio.h>
#include <float.h>

void float_header_demo ()
{
    // https://www.tutorialspoint.com/c_standard_library/float_h.htm
    
    printf("\n\n");
    printf("float.h demo\n");
    printf("-----------------------\n");

   printf("The maximum value of float = %.23e\n", FLT_MAX);
   printf("The minimum value of float = %.10e\n", FLT_MIN);
   printf("The number of digits in the number = %d\n", FLT_MANT_DIG);

   printf("The maximum value of double = %.10e\n", DBL_MAX);
   printf("The minimum value of double = %.10e\n", DBL_MIN);
   printf("The number of digits in the number = %d\n", DBL_MANT_DIG);

}


#include<limits.h>
#include<stdio.h>

int limits_header_demo()
{

    printf("\n\n");
    printf("limits.h demo\n");
    printf("-----------------------\n");


   printf("The number of bits in a byte %d\n", CHAR_BIT);

   printf("The minimum value of SIGNED CHAR = %d\n", SCHAR_MIN);
   printf("The maximum value of SIGNED CHAR = %d\n", SCHAR_MAX);
   printf("The maximum value of UNSIGNED CHAR = %d\n", UCHAR_MAX);

   printf("The minimum value of SHORT INT = %d\n", SHRT_MIN);
   printf("The maximum value of SHORT INT = %d\n", SHRT_MAX); 

   printf("The minimum value of INT = %d\n", INT_MIN);
   printf("The maximum value of INT = %d\n", INT_MAX);

   printf("The minimum value of CHAR = %d\n", CHAR_MIN);
   printf("The maximum value of CHAR = %d\n", CHAR_MAX);

   printf("The minimum value of LONG = %ld\n", LONG_MIN);
   printf("The maximum value of LONG = %ld\n", LONG_MAX);
  
   return(0);
}


#include<stdarg.h>
#include<stdio.h>


int sum(int num_args, ...)
{
   int val = 0;
   va_list ap;
   int i;

   va_start(ap, num_args);
   for(i = 0; i < num_args; i++) {
      val += va_arg(ap, int);
   }
   va_end(ap);
 
   return val;
}


void stdarg_header_demo()
{

    printf("\n\n");
    printf("stdarg.h demo\n");
    printf("-----------------------\n");

   printf("Sum of 10, 20 and 30 = %d\n",  sum(3, 10, 20, 30) );
   printf("Sum of 4, 20, 25 and 30 = %d\n",  sum(4, 4, 20, 25, 30) );

}



#include <stddef.h>
#include <stdio.h>

// Offsetof 
// -----------------------------------
// offsetof returns the address of a field relative to the start address of a struct.
// offsetof(struct, name)

void stddef_header_demo ()
{

    printf("\n\n");
    printf("stddef.h demo\n");
    printf("-----------------------\n");

    struct address {
        char name[50];
        char street[50];
        int phone;
    };
    

    printf("name offset = %lu byte in address structure.\n", offsetof(struct address, name));

    printf("street offset = %lu byte in address structure.\n", offsetof(struct address, street));

    printf("phone offset = %lu byte in address structure.\n", offsetof(struct address, phone));

} 









#include <stdio.h>

void demo_2d_arrays(void)
{
    printf("\n\n");
    printf("2D array demo\n");
    printf("-----------------------\n");


    int row, col;

    int a[2][5] = {      // Initialize a 2D array
        {0, 1, 2, 3, 4},
        {5, 6, 7, 8, 9}
    };

    for (row = 0; row < 2; row++) {
        for (col = 0; col < 5; col++) {
            printf("(%d,%d) = %d\n", row, col, a[row][col]);
        }
    }
}



// 1	void *memchr(const void *str, int c, size_t n)
// Searches for the first occurrence of the character c (an unsigned char) 
// in the first n bytes of the string pointed to, by the argument str.

// 2	int memcmp(const void *str1, const void *str2, size_t n)
// Compares the first n bytes of str1 and str2.

// 3	void *memcpy(void *dest, const void *src, size_t n)
// Copies n characters from src to dest.

// 4	void *memmove(void *dest, const void *src, size_t n)
// Another function to copy n characters from str2 to str1.

// 5	void *memset(void *str, int c, size_t n)
// Copies the character c (an unsigned char) to the first n characters 
// of the string pointed to, by the argument str.





// cl /Zi test.cpp /link  "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS

#include <stdint.h>
#include <stdio.h>

int is_prime_demo()
{

    printf("\n\n");
    printf("is_prime_demo\n");
    printf("-----------------------\n");

  int candidate = 887;
  
  int is_prime = 1;
    for (int i=2; i<candidate; i++){
      if ( candidate % i == 0 ) { is_prime = 0; break; }
    }
    printf("%d\n\r", is_prime);

    
  return 0;
}


#include <stdio.h>
#include <errno.h>
#include <string.h>

extern int errno ;

int errno_demo () {

    printf("\n\n");
    printf("errno_demo\n");
    printf("-----------------------\n");

   FILE *fp;

   fp = fopen("file.txt", "r");
   if( fp == NULL ) {
      fprintf(stderr, "Value of errno: %d\n", errno);
      fprintf(stderr, "Error opening file: %s\n", strerror(errno));
   } else {
      fclose(fp);
   }
   
   return(0);
}



int union_of_structs_demo( )
{
    // In this demo we put a bunch of structs in a union.
    // Notably we also put an integer representing the type.
    // Since this type is also (and must be) in all of the structs
    // that are in the union, this type field can be addressed directly
    // without going through one of the other unions 
    // This might be a bit confusing if you are looking at the code.


    // Each struct in the union must have as its first member 
    // uint32_t type

    // unions share the space between all possible structures.
    // So to have a type field that is directly addressable like this
    // it must be in all of the structures of the union.
    // This is the way it appears to be done in the SDL event code. 

    // An alternative way to do this is available here but it is more verbose.
    // Members would have to be addressed using another layer of indirection like this
    // shape.data.rectangle.w;
    // which would be annoying.
    // https://stackoverflow.com/questions/20752551/working-with-a-union-of-structs-in-c


    printf("\n\n");
    printf("union_of_structs_demo\n");
    printf("-----------------------\n");

    enum { RECTANGLE, CIRCLE, TRIANGLE };

    //               uint32_t type;
    typedef struct { uint32_t type; double w; double h; }  rectangle_t;
    typedef struct { uint32_t type; double r; }  circle_t;
    typedef struct { uint32_t type; double base; double height; }  triangle_t;

    // Union of Structs with type
    // The event type is shared with all events
    typedef union shape_t { 
        uint32_t type; 
        rectangle_t rectangle; 
        circle_t circle; 
        triangle_t triangle; 
    } shape_t;



    const int shapes_length = 3;
    shape_t shapes[shapes_length];

    shapes[0].type = RECTANGLE;
    shapes[0].rectangle.w = 2;
    shapes[0].rectangle.h = 3;

    shapes[1].type = CIRCLE;
    shapes[1].circle.r = 4;

    shapes[2].type = TRIANGLE;
    shapes[2].triangle.base = 2;
    shapes[2].triangle.height = 5;

    for (int i=0;i<shapes_length;i+=1) {
        double area = 0;
        const double PI = 3.14159;
        if (shapes[i].type == RECTANGLE)    area = shapes[i].rectangle.w * shapes[i].rectangle.h;
        else if (shapes[i].type == CIRCLE)  area = PI * shapes[i].circle.r * shapes[i].circle.r;
        else if (shapes[i].type == TRIANGLE)  area = 0.5 * shapes[i].triangle.base * shapes[i].triangle.height;

        printf("shape type %d shape area %f\n", shapes[i].type, area );
    }
   return 0;
}






// // It appears that strtok is better than split_string()
// // ----------------------------------------------------------


// #include "basic.h"

// typedef char* string;
// DEFINE_ARRAY(string);

// // destructively split a string by converting delimiters into null bytes
// // and noting down the positions after them.
// string_array split_string(char *str, const char *delim)
// {
//     size_t string_length = strlen(str);

//     // convert delimiters to null bytes
//     for (int i = 0; i < string_length; i++ ) {
//         for ( int j = 0; delim[j] != '\0'; j += 1 ) {
//             if (str[i]==delim[j]) { 
//                 str[i] = '\0'; 
//                 break; 
//             }
//         }
//     }

//     string_array l = string_array_make();

//     // add pointer to first element if it's not null
//     if ( str[0] != '\0' ) l = string_array_add(l, str);
//     for ( int i = 1; i < string_length; i++ ) {
//         // add locations which are directly after null bytes
//         if ( str[i-1] == '\0' && str[i] != '\0' ) l = string_array_add(l, str+i);
//     }
//     return l;
// }


// void demo_split_string()
// {
//     printf("\n\n");
//     printf("Split String Demo\n");
//     printf("-----------------------\n");

//     char text[] = 
//         "SDLK_1 play_pause_music(music) \n"
//         "SDLK_2 stop_music(music) \n"
//         "SDLK_3 play_sound_effect(scratch) \n"
//         "SDLK_4 play_sound_effect(high) \n";


//     string_array lines = split_string(text,"\n");
//     for(uint32_t i=0;i<lines.length; i++) printf("{%s}\n", lines.data[i]);

// }










/*
Use this if you can't print floats - in an embedded system for example.
*/

#include <stdio.h>
#include <math.h>

void sprint_float3(char* str, double arg)
{

    // sprint a float to 3 decimal places
    // To change the number of decimal places change 1000 and %03d
    // from https://stackoverflow.com/questions/905928/using-floats-with-sprintf-in-embedded-c

    char *sign;
    double val;
    int integer_part, fraction_part;

    if (arg < 0) { sign=(char*)"-"; val = -arg; } else { sign=(char*)""; val = arg; }

    integer_part = (int)(val);
    fraction_part = (int)((val - integer_part) * 1000);  // Get fraction then turn into integer (123).

    if (fraction_part == 0){
        sprintf (str, "%s%d", sign, integer_part);
    } else {
        sprintf (str, "%s%d.%03d", sign, integer_part, fraction_part);  
    }

}


int sprint_float3_main()
{

    printf("\n\n");
    printf("sprint_float3_main\n");
    printf("-----------------------\n");

    char str[100];

    sprint_float3(str, 0.01234);
    puts(str);
    sprint_float3(str, -3.1415926535);
    puts(str);
    sprint_float3(str, 3234);
    puts(str);

  return 0;
}





#include <stdio.h>

int snprintf_demo()
{
    // int snprintf ( char * s, size_t n, const char * format, ... );
    // returns the number of characters written.
    // returns negative if there's an error.
    // the output string is not guaranteed to be null terminated.
    // source: https://www.cplusplus.com/reference/cstdio/snprintf/


    printf("\n\n");
    printf("snprintf_demo\n");
    printf("-----------------------\n");

    char buffer [100];
    int cx;

    cx = snprintf ( buffer, 100, "The half of %d is %d", 60, 60/2 );

    if (cx>=0 && cx<100) {
        size_t remaining_size = (size_t)(100-cx);
        snprintf ( buffer+cx, remaining_size, ", and the half of that is %d.", 60/2/2 );
    }

    puts (buffer);

  return 0;
}








/*
** showip.c -- show IP addresses for a host
** from beej
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// hostname_to_ip_address
int showip( const char* hostname )
{
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    // if (argc != 2) {
    //     fprintf(stderr,"usage: showip hostname\n");
    //     return 1;
    // }
    // char *hostname = argv[1];
    

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(hostname, NULL, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }

    printf("IP addresses for %s:\n\n", hostname);

    for(p = res;p != NULL; p = p->ai_next) {
        void *addr;
        char ipver[] = "0000";

        // get the pointer to the address itself,
        // different fields in IPv4 and IPv6:
        if (p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            strcpy(ipver, "IPv4");
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            strcpy(ipver, "IPv6");
        }

        // convert the IP to a string and print it:
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf("%s: %s\n", ipver, ipstr);
    }

    freeaddrinfo(res); // free the linked list

    return 0;
}

void showip_demo()
{

    printf("\n\n");
    printf("showip_demo\n");
    printf("-----------------------\n");

    showip("www.google.com");
}







void reverse_string(char *str)
{
  size_t len = strlen(str);
  size_t i;

  for ( i = 0; i < len / 2; i += 1 ){
    char c = str[len-1-i]; 
    str[len-1-i] = str[0+i]; 
    str[0+i] = c;
  }

}
    
int reverse_string_demo()
{
    printf("\n\n");
    printf("reverse_string_demo\n");
    printf("-----------------------\n");

    char s[] = "Hannah";
    reverse_string(s);
    printf("%s\n", s);
    return 0;
}











#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>


typedef struct {
	uint64_t input;
	uint64_t output;
} thread_arg_t;

void* factorial_thread(void* voidptr_arg)
{
    thread_arg_t *arg = (thread_arg_t*) voidptr_arg;
    uint64_t accumulator = 1;
    uint64_t i;

    for ( i = 1; i <= arg->input; i++) {
        accumulator *= i;
    }
    arg->output = accumulator;
    
	pthread_exit(0);
}


void pthreads_demo()
{

    printf("\n\n");
    printf("pthreads_demo\n");
    printf("-----------------------\n");

   time_t t;
   srand( (uint32_t) time(&t));


    #define NUM_THREADS 10
    uint64_t i;
	pthread_t threads[NUM_THREADS];
	thread_arg_t thread_args[NUM_THREADS];

	for ( i = 0; i < NUM_THREADS; i+=1 ) {

		thread_args[i].input = rand() % 30;
		thread_args[i].output = 0;
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		pthread_create(&threads[i], &attr, factorial_thread, &thread_args[i]);
	}

	// wait for threads to exit, pthread_join blocks
	for ( i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL); 
    }

    for ( i = 0; i < NUM_THREADS; i++) {
        printf("thread %llu. factorial %llu = %llu\n", i, thread_args[i].input, thread_args[i].output);
    }

}





// Memory Speed Demo 

// It's fastest to write memory 32 bits at a time.
// Writing individual bytes on my machine is really slow.

// gcc -Iinclude -Ofast memory_allocation_demo.c -Weverything -Wno-missing-prototypes -Wno-cast-align && ./a.out

// Writing 4gb in 8,16,32,64 bytes
// duration: 1.977829
// duration: 0.612975
// duration: 0.515521
// duration: 0.631118


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double diffclock( clock_t t2, clock_t t1 )
{
    return ( (double)(t2 - t1) ) / ( (double)(CLOCKS_PER_SEC) );
}



int memory_write_speed_demo()
{

    printf("\n\n");
    printf("memory write speed demo\n");
    printf("-----------------------\n");

    printf("Writing 1gb of memory 8,16,32, and 64 bits at a time on a 64 bit machine. \n");
    printf("It's fastest to write memory 32 bits at a time.\n\n");

    const uint64_t memory_size = (uint64_t)(1.0*1024.0*1024.0*1024.0); // there's can be an integer overflow here floats aren't used.
    uint8_t *memory = (uint8_t*)malloc( memory_size * sizeof(uint8_t) );

    clock_t t[10] = {0};
    uint64_t tl = 0;

    t[tl++] = clock();

    // for(i=0;i<memory_size;i++) memory[i] = (uint8_t)(i % 99);
    // t[tl++] = clock();

    for(uint64_t i=0;i<memory_size;i++) ((uint8_t*)memory)[i] = (uint8_t)i;
    for(int i=0;i<100;++i) printf("%02x ", memory[i]);
    printf("\n\n");
    t[tl++] = clock();

    for(uint64_t i=0;i<memory_size / 2;i++) ((uint16_t*)memory)[i] = (uint16_t)i;
    for(int i=0;i<100;++i) printf("%02x ", memory[i]);
    printf("\n\n");
    t[tl++] = clock();

    for(uint64_t i=0;i<memory_size / 4;i++) ((uint32_t*)memory)[i] = (uint32_t)i;
    for(int i=0;i<100;++i) printf("%02x ", memory[i]);
    printf("\n\n");
    t[tl++] = clock();

    for(uint64_t i=0;i<memory_size / 8;i++) ((uint64_t*)memory)[i] = (uint64_t)i;
    for(int i=0;i<100;++i) printf("%02x ", memory[i]);
    printf("\n\n");
    t[tl++] = clock();

    for (uint64_t i=1; i<tl; ++i) printf("duration: %f\n",  diffclock( t[i], t[i-1] ) );


    return 0;
}







// gcc demo_endianness.c && ./a.out

#include <stdio.h>
#include <stdint.h>

int endianness_demo()
{

    printf("\n\n");
    printf("endianness_demo\n");
    printf("-----------------------\n");

    {
        uint32_t a[2] = {0x01020304, 0x01020304 };
        uint8_t *b = (uint8_t*)a;
        int i;
        // printf("The pointer points to the first byte in the array, independent of the data, apparently. address = %u, %u", a,b);

        printf("The two integers ");
        for(i=0;i<2;++i){ printf("%08x ", a[i]); }
        printf("\n");

        printf("are represented in memory as ");
        for(i=0;i<2*4;++i){ printf("%02x ", b[i]); }
        printf("\n\n");

        printf("If we declare two integers in an array and then print them out we get the top result.\n");
        printf("If the memory is cast to an uint8_t*, we get the second result.\n");
        printf("In most systems x86 systems, multi-byte data is flipped around in memory.\n");
        printf("Registers are not byte addressable.  So it doesn't make sense comment on their endianness.\n");
    }


    // let's do the same thing again why not?
    if((0)){
        uint8_t bytes[8] = {0x01, 0x02, 0x03, 0x04, 0x01, 0x02, 0x03, 0x04 };
        uint32_t* integers = (uint32_t*)bytes;
        int i;

        printf("Put some bytes in memory\n");
        for(i=0;i<2*4;++i){ printf("%02x ", bytes[i]); }
        printf("\n");

        printf("Retype them as integers and print the array again\n");
        for(i=0;i<2;++i){ printf("%08x ", integers[i]); }
        printf("\n");


        // why not do it again with laborious bitwise operations
        printf("Do it again with laborious bitwise operations\n");
        for(i=0;i<2;++i){ 
            printf("%02x %02x %02x %02x ", 
                (uint8_t)((integers[i] & 0xff000000)>>24), 
                (uint8_t)((integers[i] & 0x00ff0000)>>16),
                (uint8_t)((integers[i] & 0x0000ff00)>>8), 
                (uint8_t)((integers[i] & 0x000000ff)>>0) 
            ); 
        }
        printf("\n");
    }


    return 0;
}






#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int atof()
{

    printf("\n\n");
    printf("endianness_demo\n");
    printf("-----------------------\n");

    printf("These functions return 0 if there's an error\n\n");

   double val;
   char str[20];
   
    // float.h demo
    // -----------------------
    // The maximum value of float = 3.40282346638528859811704e+38
    // The minimum value of float = 1.1754943508e-38
    // The number of digits in the number = 24
    // The maximum value of double = 1.7976931349e+308
    // The minimum value of double = 2.2250738585e-308
    // The number of digits in the number = 53

   strcpy(str, "1234234.7976931348e+200");
   printf("String value = %s, Float value = %.6e, int value = %d \n", str, atof(str), atoi(str) );

   strcpy(str, "tutorialspoint.com");
   printf("String value = %s, Float value = %.6e, int value = %d \n", str, atof(str), atoi(str) );


   return(0);
}



int main()
{
    caesar_cipher_demo();
    strtok_demo();
    variadic_sum_demo();
    eulers_method_demo();
    newtons_method_demo();

    read_file_demo();
    read_file2_demo();

    cpp_vector_demo();

    // header file demos
    float_header_demo();  // print float limits
    limits_header_demo(); // print integral limits
    stdarg_header_demo(); // va_arg
    stddef_header_demo(); // offsetof

    demo_2d_arrays();
    is_prime_demo();

    errno_demo();
    // demo_split_string();
    // print_this_file();

    union_of_structs_demo();
    sprint_float3_main();
    snprintf_demo();
    vigenere_cipher_demo();

    reverse_string_demo();
    pthreads_demo();

    // // these take a little time
    // showip_demo();
    // print_stuff_on_one_line_demo();
    // thread_race_demo();
    // memory_write_speed_demo();


    endianness_demo();
    atof();

    return 0;
}





