#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define MAX_PATH_LENGTH 4096

int invert_link(char *link) {
    char link_value[MAX_PATH_LENGTH];
    char path[MAX_PATH_LENGTH];
    int is_link = readlink(link, link_value, MAX_PATH_LENGTH);
    if(is_link == -1) {
        printf("File specified is not a symlink\n");
        return 0;
    }

    unlink(link);
    char real_link_path[MAX_PATH_LENGTH];
    realpath(link, real_link_path);

    realpath(link_value, path);
    rename(path, real_link_path);

    symlink(real_link_path, path);
    
    return 1;
}

void isl_in_dir(char *dir) {
    struct dirent *dptr;

    DIR *directory = opendir(dir);
    if(directory == NULL) {
        printf("Could not open directory %s", dir);
        return;
    }

    char current_path[MAX_PATH_LENGTH];
    struct stat current_stats;
    while((dptr = readdir(directory)) != NULL) {
        sprintf(current_path, "%s/%s", dir, dptr->d_name);
        lstat(current_path, &current_stats);
        if(S_ISLNK(current_stats.st_mode)) {
            if(invert_link(current_path))
                printf("Inverted link: %s\n", current_path);
        }
    }

}

int main(int argc, char *argv[]) {
    // Partial solution

    if(argc < 2) {
        printf("Provide a paramter\n");
        return 0;
    }

    struct stat file_stats;
    lstat(argv[1], &file_stats);
    if(S_ISDIR(file_stats.st_mode)) {
        printf("Checking links in directory %s\n", argv[1]);
        isl_in_dir(argv[1]);
    }
    else {
        if(invert_link(argv[1]))
            printf("Inverted link: %s\n", argv[1]);
    }
}
