#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int needs_tree(struct stat *entry_stats) {
    return S_ISDIR(entry_stats->st_mode);
}

void tree_aux(char *dir, int depth, char *prefix_unit, char *prefix)  {
    struct stat entry_stats;
    lstat(dir, &entry_stats);
    if(!needs_tree(&entry_stats)) return;

    DIR *d;
    d = opendir(dir);

    struct dirent *current_dir;

    if(d != NULL) {
        while((current_dir = readdir(d)) != NULL) {
            if(strcmp(current_dir->d_name, ".") == 0 || strcmp(current_dir->d_name, "..") == 0)
                continue;

            printf("%s%s\n", prefix, current_dir->d_name);

            char new_dir[4096];
            char new_prefix[500];
            sprintf(new_dir, "%s/%s", dir, current_dir->d_name);
            sprintf(new_prefix, "%s%s", prefix_unit, prefix);

            tree_aux(new_dir, depth + 1, prefix_unit, new_prefix);
        }
    }
    closedir(d);
}

void tree(char *dir, char *prefix_unit) {
    tree_aux(dir, 0, prefix_unit, "");
}

int main(int argc, char *argv[]) {
    if(argc < 2) return 1;

    tree(argv[1], " ");
}
