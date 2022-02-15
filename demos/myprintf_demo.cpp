

#include <stdarg.h>
#include <stdio.h>
#include <string.h>


char *myprintf_convert(unsigned int num, int base)
{ 
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[50]; 
    char *ptr; 

    ptr = &buffer[49]; 
    *ptr = '\0'; 

    do { 
        *--ptr = Representation[num%base]; 
        num /= base; 
        
    } while(num != 0); 

    return(ptr); 
}


void myprintf(const char* format,...)
{ 

    const char *traverse; 
    int i; 
    char *s; 

    double float_value;
    int float_decimal_places  = 6;
    int float_fraction_scaler = 1000000;
    
    va_list arg; 
    va_start(arg, format); 

    for(traverse = format; *traverse != '\0'; traverse++) 
    { 
        // print regular
        if( *traverse != '%' && *traverse != '\\' ) { 
            fputc(*traverse, stdout);
        } 
        // print escape chars
        if( *traverse == '\\' ) {
            traverse += 1;

            if      ( *traverse == 'n' ) { fputc('\n', stdout); }
            else if ( *traverse == 't' ) { fputc('\t', stdout); }
            else if ( *traverse == 'r' ) { fputc('\r', stdout); }
            else {
                printf("ERROR %s %d Unknown escape character\n", __FILE__, __LINE__ );
                fputc('\\', stdout);
                fputc( *traverse , stdout);
            }
        }
        // print numbers in various formats
        if( *traverse == '%' ) {
            traverse++;
            switch (*traverse) { 

            case 'c' : i = va_arg(arg, int);
                        fputc(i, stdout);
                        break; 

            case 'd' : i = va_arg(arg, int);
                        if(i<0){ 
                            i = -i;
                            fputc('-', stdout);
                        } 
                        fputs(myprintf_convert(i, 10), stdout);
                        break; 

            case 'o': i = va_arg(arg, unsigned int);
                        fputs(myprintf_convert(i, 8), stdout);
                        break; 

            case 's': s = va_arg(arg, char *);
                        fputs(s, stdout);
                        break; 

            case 'x': i = va_arg(arg, unsigned int);
                        fputs(myprintf_convert(i, 16), stdout);
                        break; 

            case 'f': 
                        float_value = va_arg(arg, double);

                        char sign = '\0';
                        if (float_value < 0) { sign='-'; float_value = -float_value; } 
                        int integer_part = (int)(float_value);
                        int fraction_part = (int)((float_value - integer_part) * float_fraction_scaler);


                        if (sign) fputc(sign, stdout);
                        fputs(myprintf_convert(integer_part, 10), stdout);

                        if (fraction_part != 0){
                            char *fraction_string = myprintf_convert(fraction_part, 10);
                            fputc('.', stdout);
                            for(int i=0; i < ( float_decimal_places - strlen(fraction_string) ); i+=1 ) fputc('0', stdout);
                            fputs(fraction_string, stdout);
                        }
                        break;
            }

        }
    } 


    va_end(arg); 
} 


void myprintf_demo()
{
    
    printf("\n\n");
    printf("myprintf_demo\n");
    printf("-----------------------\n");

    float a_float = 99.234234234234234234234;
    double a_double = 999.4323423423234234234;
    myprintf("char \t %c\ninteger \t %d\noctal \t %o\nstring \t {%s}\nhex \t %x\ndouble \t %f\nfloat \t %f\n", 
            'c', 999, 999, "omg", 999, a_double, a_float );

}


int main()
{
    myprintf_demo();
}