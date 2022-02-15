#ifndef BASH_HEADER_GUARD
#define BASH_HEADER_GUARD




int bash_ls(const char *path);
int bash_find(char *dirname, char *query);




// gcc bash.c && ./a.out .. .html

// https://en.wikibooks.org/wiki/C_Programming/POSIX_Reference/dirent.h

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <assert.h>




// d_type
// #define DT_UNKNOWN 0
// #define DT_REG S_IFREG
// #define DT_DIR S_IFDIR
// #define DT_FIFO S_IFIFO
// #define DT_SOCK S_IFSOCK
// #define DT_CHR S_IFCHR
// #define DT_BLK S_IFBLK
// #define DT_LNK S_IFLNK






#endif // BASH_HEADER_GUARD
#ifdef BASH_IMPLEMENTATION
#ifndef BASH_IMPLEMENTATION_GUARD
#define BASH_IMPLEMENTATION_GUARD




int bash_ls(const char *path)
{
  struct dirent *entry;

  DIR *dir = opendir(path);
  if ( !dir ) {
    printf("ERROR %s %d couldn't open dir\n", __FILE__,__LINE__);
    return -1;
  }

  while(( entry = readdir(dir) )) printf("%s\n", entry->d_name ); // puts(entry->d_name);

  closedir(dir);

  return 0;
}


int bash_find(char *dirname, char *query)
{
    struct dirent *entry;
    char path[1000];

    DIR *dir = opendir(dirname);
    assert(dir);
    // if ( !dir ) {
    //     printf("ERROR %s %d couldn't open dir\n", __FILE__,__LINE__);
    //     return -1;
    // }

    while(( entry = readdir(dir) )) {

        // ignore . and .. dirs
        if ( !strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..") ) {
            continue;
        }

        snprintf( path, 1000, "%s/%s", dirname, entry->d_name );
        if ( strstr( path, query ) ) printf("%s\n", path);

        // if ( entry->d_type == DT_REG ) { 
        //     // regular file
        // }
        if ( entry->d_type == DT_DIR ) {
            bash_find( path, query );
        }

    }

    closedir(dir);

    return 0;
}


int bash_main(int argc, char **argv) {

    for(int i=0;i<argc;i+=1) printf("{%s} ", argv[i]);
    printf("\n");

    char *dir = argv[1];
    char *query;
    if (argc == 3) { 
        query = argv[2];
    } else {
        query = (char*)"";
    }

    bash_find(dir, query);

  return 0;
}








#endif // BASH_IMPLEMENTATION_GUARD 
#endif // #ifdef BASH_IMPLEMENTATION


