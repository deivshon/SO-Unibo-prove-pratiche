#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PATH_LENGTH 4096

void link_to_absolute(char *link_path, char *dir_path, char *wd) {
    char pointed[MAX_PATH_LENGTH];
    readlink(link_path, pointed, MAX_PATH_LENGTH);

    unlink(link_path);

    char absolute_link_pointed_path[MAX_PATH_LENGTH];
    chdir(dir_path);
    realpath(pointed, absolute_link_pointed_path);
    chdir(wd);

    symlink(absolute_link_pointed_path, link_path);
}

int main(int argc, char **argv) {
    if(argc < 2) exit(EXIT_FAILURE);

    char wd[MAX_PATH_LENGTH];
    getcwd(wd, MAX_PATH_LENGTH);

    char arg_path[MAX_PATH_LENGTH];
    strcpy(arg_path, argv[1]);

    DIR *chosend_dir = opendir(argv[1]);

    struct dirent *entry;
    struct stat file_details;
    char current_path[MAX_PATH_LENGTH];
    while(entry = readdir(chosend_dir)) {
        sprintf(current_path, "%s/%s", arg_path, entry->d_name);
        lstat(current_path, &file_details);
        if(S_ISLNK(file_details.st_mode)) {
            link_to_absolute(current_path, arg_path, wd);
        }
    }

    closedir(chosend_dir);

}
