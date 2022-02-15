/**************************************************************
 * A simpler and shorter implementation of ls(1)
 * ls(1) is very similar to the DIR command on DOS and Windows.
 **************************************************************/
#include <stdio.h>
#include <dirent.h>

int listdir(const char *path) 
{
  struct dirent *entry;
  DIR *dp;

  dp = opendir(path);
  if (dp == NULL) 
  {
    perror("opendir");
    return -1;
  }

  while((entry = readdir(dp)))
    puts(entry->d_name);

  closedir(dp);
  return 0;
}

int demo_listdir(int argc, char **argv) {
  int counter = 1;

  if (argc == 1)
	listdir(".");

  while (++counter <= argc) {
    printf("\nListing %s\n", argv[counter-1]);
    listdir(argv[counter-1]);
  }

  return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <dirent.h> /* "readdir" etc. are defined here. */
#include <limits.h> /* limits.h defines "PATH_MAX". */

#include <iostream>
#include <string>
#include <vector>


void find_files(const char * dir_name, std::vector<std::string> *output)
{
    /* this function is from lemoda.net */
    std::string buff = "";
    DIR * d;
    /* Open the directory specified by "dir_name". */
    d = opendir (dir_name);
    /* Check it was opened. */
    if (! d) {
        fprintf (stderr, "Cannot open directory '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
    while (1) {
        struct dirent * entry;
        const char * d_name;

        /* "Readdir" gets subsequent entries from "d". */
        entry = readdir(d);
        if (! entry) {
            /* There are no more entries in this directory, so break
               out of the while loop. */
            break;
        }
        d_name = entry->d_name;
        /* Print the name of the file and directory. */
        // printf ("%s/%s\n", dir_name, d_name);

        buff = "";
        buff += dir_name;
        buff += "/";
        buff += d_name;
        // buff += "\n";
        output->push_back(buff);

#if 0
    	/* If you don't want to print the directories, use the
	   following line: */
       if (! (entry->d_type & DT_DIR)) {
            // printf ("%s/%s\n", dir_name, d_name);
            buff = "";
            buff += dir_name;
            buff += "/";
            buff += d_name;
            // buff += "\n";
            output->push_back(buff);
        }

#endif /* 0 */

        if (entry->d_type & DT_DIR) {
            /* Check that the directory is not "d" or d's parent. */
            if (strcmp (d_name, "..") != 0 &&
                strcmp (d_name, ".") != 0) {
                int path_length;
                char path[PATH_MAX];
 
                path_length = snprintf (path, PATH_MAX,
                                        "%s/%s", dir_name, d_name);
                // printf ("%s\n", path);
                buff = "";
                buff += path;
                // buff += "\n";
                output->push_back(buff);

                if (path_length >= PATH_MAX) {
                    fprintf (stderr, "Path length has got too long.\n");
                    exit (EXIT_FAILURE);
                }
                /* Recursively call "find_files" with the new path. */
                find_files (path,output);
            }
	    }
    }


    /* After going through all the entries, close the directory. */
    if (closedir (d)) {
        fprintf (stderr, "Could not close '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
}

int find_files_main (int argc, char **argv)
{
    const char *dir = argv[1];
    // const char *dir = "/Users/nick/Downloads";

	std::vector<std::string> files;
	find_files(dir, &files);
    for (auto f : files) { std::cout << f << std::endl; } 
	// for (auto f : files) {
	// 	const char *extension = f.substr(f.find_last_of(".") + 1).c_str();
	// 	if (strcmp(extension, "jpg")==0) std::cout << f << std::endl;
	// 	// std::cout << extension << std::endl;
	// 	// std::cout << f << std::endl;
	// }
}

int main(int argc, char **argv)
{
    find_files_main(argc, argv);
    return 0;
}