
int strlen(char *str)
{
  int i=0;
  while (str[i] != '\0') i+=1;
  return i;
}


void kmain(void)
{
  // there are 25 lines each of 80 columns; each element takes 2 bytes */

  char *str = "h e l l o   w o r l d ! ";
  char *video_memory = (char*)0xb8000;
  for( int i=0; i<strlen(str); i++ ) { video_memory[i++] = str[i]; }

}

