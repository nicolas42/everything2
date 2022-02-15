// gcc embedded_assembly.c && ./a.out

// GCC uses AT&T syntax

// https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html

// constraint
//     A string constant specifying constraints on the placement of the operand; See Constraints, for details.
//     Output constraints must begin with either ‘=’ (a variable overwriting an existing value) or ‘+’ (when reading and writing). When using ‘=’, do not assume the location contains the existing value on entry to the asm, except when the operand is tied to an input; see Input Operands.
//     After the prefix, there must be one or more additional constraints (see Constraints) that describe where the value resides. Common constraints include ‘r’ for register and ‘m’ for memory. When you list more than one possible location (for example, "=rm"), the compiler chooses the most efficient one based on the current context. If you list as many alternates as the asm statement allows, you permit the optimizers to produce the best possible code. If you must use a specific register, but your Machine Constraints do not provide sufficient control to select the specific register you want, local register variables may provide a solution (see Local Register Variables).

#include <stdio.h>

void demo()
{
    int a = 10, b = 15;

    __asm__ __volatile__(
    "addl  %%ebx,%%eax"
    : "=r"(a) // output
    : "r"(a), "r"(b) // input
    );

    printf("a+b=%d\n", a);
}

// https://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html
static inline char * strcpy(char * dest,const char *src)
{
    int d0, d1, d2;

    __asm__ __volatile__( 

        "1: lodsb               \n\t"
        "stosb                  \n\t"
        "testb %%al,%%al        \n\t"
        "jne 1b"
        
        : "=&S" (d0), "=&D" (d1), "=&a" (d2)
        : "0" (src),"1" (dest) 
        : "memory"
    );

    return dest;
}


int main(void)
{
    char str1[] = "Hello world!";
    char str2[1000];
    strcpy(str2, str1);

    printf("%s\n", str2);


    __asm__ __volatile__( 

        pusha 
        mov ah, 0x0e
        mov al, [bx]
        int 0x10
        popa
        
    );

    return 0;
}