#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <vector>
#include "read_file.h"

int main(int argc, char **argv)
{
    // test read_file.h
    char *file = NULL; 
	int file_length = -1;
    read_file( "read_file.h", &file, &file_length );
    printf("%s", file);
    printf("%d\n", file_length);
	free(file);



    return 0;
}
