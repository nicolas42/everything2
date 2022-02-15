#include <stdio.h>
#include <string.h>

int reverse_string(int argc, char **argv);


int main(int argc, char **argv)
{
  reverse_string(argc, argv);
  return 0;
}

int reverse_string(int argc, char **argv)
{
  char *s = argv[1];
  int l = strlen(s);
  
  for (int i=0; i<l/2; ++i){
    char tmp = s[l-1-i];
    s[l-1-i] = s[0+i];
    s[0+i] = tmp;
  }
  printf("%s\n",s);
  return 0;
}
    
