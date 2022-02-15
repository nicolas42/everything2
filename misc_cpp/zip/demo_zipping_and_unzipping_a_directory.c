// gcc demo_zipping_and_unzipping_a_directory.c zip.c && ./a.out

#include <stdio.h>
#include <dirent.h>
#include "zip.h"
#include <sys/stat.h>
#include <assert.h>

void zip_compress(struct zip_t *zip, const char *path) {
    DIR *dir;
    struct dirent *entry;
    char fullpath[MAX_PATH];
    struct stat s;

    memset(fullpath, 0, MAX_PATH);
    dir = opendir(path);
    if (!dir) return;
    // assert(dir);

    while ((entry = readdir(dir))) {
      // skip "." and ".."
      if (!strcmp(entry->d_name, ".\0") || !strcmp(entry->d_name, "..\0"))
        continue;

      snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
      stat(fullpath, &s);
      if (S_ISDIR(s.st_mode))
        zip_compress(zip, fullpath);
      else {
        zip_entry_open(zip, fullpath);
        zip_entry_fwrite(zip, fullpath);
        printf("Compressed: %s \n", fullpath);
        zip_entry_close(zip);
      }
    }
    closedir(dir);
}

int on_extract_print_filename(const char *filename, void *arg) {
    printf("Extracted: %s\n", filename);
    return 0;
}

void unzip_dir(const char *zip_filename, const char *output_dir_name)
{
    zip_extract(zip_filename, output_dir_name, on_extract_print_filename, 0);

}

void zip_dir(const char *directory, const char *output_zip_file)
{
    struct zip_t *zip = zip_open(output_zip_file, 0,'w'); //ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    zip_compress(zip, directory);
    zip_close(zip);
}

int main(int argc, char **argv)
{
    zip_dir("/Users/nick/Downloads/new", "foo.zip");

    unzip_dir("foo.zip", "uncompressed_foo");

}