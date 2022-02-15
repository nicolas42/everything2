#include <stdio.h>
#include <dirent.h>
#include "zip.h"
#include <sys/stat.h>
#include <assert.h>

void zip_walk(struct zip_t *zip, const char *path) {
    DIR *dir;
    struct dirent *entry;
    char fullpath[MAX_PATH];
    struct stat s;

    memset(fullpath, 0, MAX_PATH);
    dir = opendir(path);
    assert(dir);

    while ((entry = readdir(dir))) {
      // skip "." and ".."
      if (!strcmp(entry->d_name, ".\0") || !strcmp(entry->d_name, "..\0"))
        continue;

      snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
      stat(fullpath, &s);
      if (S_ISDIR(s.st_mode))
        zip_walk(zip, fullpath);
      else {
        zip_entry_open(zip, fullpath);
        zip_entry_fwrite(zip, fullpath);
        zip_entry_close(zip);
      }
    }

    closedir(dir);
}

int on_extract_entry(const char *filename, void *arg) {
    static int i = 0;
    int n = *(int *)arg;
    printf("Extracted: %s (%d of %d)\n", filename, ++i, n);
    return 0;
}


// zip directory then unzip it
int main(int argc, char **argv)
{

    struct zip_t *zip = zip_open("foo.zip", ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    zip_walk(zip, "foo");
    zip_close(zip);


    int arg = 5;
    zip_extract("foo.zip", "extracted_foo", on_extract_entry, &arg);

}