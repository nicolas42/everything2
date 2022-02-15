#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void read_file(char *filename, char **output, int *num_chars_read)
{
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
        *num_chars_read = 0;
        printf("Error in opening file %s", filename);
		return;
	}

	size_t length = 0;
	size_t allocated = 10000; // 10 kilobytes
	char *data = (char*)malloc(allocated * sizeof(char));

	while (1) {
		int c = fgetc(f);
		if (feof(f)) { 
			data[length] = '\0';
			length += 1;
			break; 
		}
		data[length] = (char)c;
		length += 1;
        if (length == allocated){
            allocated *= 2;
            data = (char*)realloc(data, allocated);
        }
	}
	fclose(f);

    *output = data;
    *num_chars_read = length;
}


// size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)

#include <stdio.h>
#include <stdlib.h>

void read_whole_file(char *filename, char **output)
{
	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

	char *string = malloc(fsize + 1);
	fread(string, 1, fsize, f);
	fclose(f);

	string[fsize] = 0;
	*output = string;
}

// void replace_all(char* arg, char* to_be_replaced, char replace_with)
// {

// 	size_t length = 0;
// 	size_t allocated = 1000;
// 	char *data = (char*)malloc(allocated * sizeof(char));

// 	size_t original_string_length = strlen(arg);
// 	// printf("strlen(arg) %lu\n", strlen(arg));

// 	for (size_t i = 1; i < original_string_length; i++){
// 		for (size_t j = 0; j < strlen(to_be_replaced); j++)
// 		{
// 			if ( arg[i] == to_be_replaced[j] ){ 
//                 arg[i] = replace_with; 


// 				data[length] = (char)c;
// 				length += 1;
// 				if (length == allocated){
// 					allocated *= 2;
// 					data = (char*)realloc(data, allocated);
// 				}

//                 break; 
//             }
// 		}
// 	}
// }

// 	// strings_add(&lines, &(arg[0]));

// 	// for (size_t i = 1; i < original_string_length; i++) {

// 	// 	if (arg[i-1] == '\0' && arg[i] != '\0') {
// 	// 		strings_add(&lines, &(arg[i]));
// 	// 	}
// 	// }
// }

struct line {
	int start;
	int end;
};



void get_lines(char *buff, struct line **output, int *len)
{

	int index = 0;
	int allocated = 10;
	struct line *data = (struct line*)malloc(allocated * sizeof(struct line));

	if (index == allocated){
		allocated *= 2;
		data = (struct line*)realloc(data, allocated * sizeof(struct line));
	}
	data[index].start = 0;
	int is_within_line = 1;

	for (int i=0; ; i++){
		if (buff[i] == '\0') {
			if (is_within_line){
				data[index].end = i-1;
				is_within_line = 0;
			}
			break;
		}

		if (is_within_line && buff[i] == '\n') {
			is_within_line = 0;
			data[index].end = i-1;
		}
		if (!is_within_line && buff[i] != '\n'){
			is_within_line = 1;

			index++;
			if (index == allocated){
				allocated *= 2;
				data = (struct line*)realloc(data, allocated * sizeof(struct line));
			}
			data[index].start = i;
		}
	}

	*output = data;
	*len = index+1;

}
int main(int argc, char **argv)
{
/*
	char *str;
    int len = -1;
    read_file("working_read_file_read_lines.c", &str, &len);
    printf("\nlength: %d\n {%s}\n", len, str);

	replace_all(str, " ", 'A');
	printf("{%s}\n", str);

    free(str);







	struct line *data;
	int length = 0;
	int allocated = 10;
	data = (struct line*)malloc(allocated * sizeof(struct line));

	data[length].start = 0;
	length++;
	if (length == allocated) allocated *= 2;
	data = (struct line*) realloc(data, allocated * sizeof(struct line));

*/

	char *buff;
	read_whole_file("working_read_file_read_lines.c", &buff);
	printf("{%s}\n", buff);

	struct line *lines;
	int len = -1;
	get_lines(buff, &lines, &len);
	
	for (int j=0; j< len; j++){
		putchar('{');
		for (int i=lines[j].start; i<lines[j].end; i++) {
			putchar(buff[i]);
		}
		putchar('}'); 
		putchar('\n');
	}

	free(buff);
	free(lines);

	return 0;
}