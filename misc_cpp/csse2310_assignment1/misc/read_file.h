#include <stdio.h>
// #include <ctype.h>
#include <stdlib.h>




void read_file (char *filename, char **ret_char_array, int *ret_char_length)
{
	// string
    char *char_array = (char*)malloc(1000);
	int chars_allocated = 1000;
	int char_length = 0;
	
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
            printf("chars_allocated %d\n", chars_allocated);
        }

	}
	fclose(f);
	
    *ret_char_array = char_array;
    *ret_char_length = char_length;
}



int demo_read_file(int argc, char **argv)
{
    char *file = NULL; 
	int file_length = -1;
    read_file( "read_file.h", &file, &file_length );
    printf("%s", file);
    printf("%d\n", file_length);
	free(file);
	
    return 0;
}
