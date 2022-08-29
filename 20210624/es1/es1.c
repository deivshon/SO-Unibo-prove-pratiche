#include <stdio.h>
#include <sys/inotify.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_LEN 1024
#define MAX_LINE_LEN 4096

// Assuming only text files are to be handled
int main(int argc, char **argv) {
    FILE *results = fopen(argv[2], "w");

    int in_instance = inotify_init();
    int watched = inotify_add_watch(in_instance, argv[1], IN_CREATE);
    if(watched < 0) {
        return 1;
    }

    char buf[BUF_LEN];
    int i = 0;
    while(1) {
        read(in_instance, buf, BUF_LEN);
        struct inotify_event *event = (struct inotify_event *) &buf;

        if(event->len) {
            if(event->mask & IN_CREATE) {
                fprintf(results, "%s:\n", event->name);

                char file_path[4096];
                sprintf(file_path, "%s/%s", argv[1], event->name);
                printf("%s created, copying contents to %s\n", file_path, argv[2]);

                /* If the file is created directly in the folder and no time
                 * is waited, the content copied will be blank
                 */
                usleep(100); 

                FILE *new_file = fopen(file_path, "r");
                char buf[MAX_LINE_LEN];
                while(fgets(buf, MAX_LINE_LEN, new_file)) {
                    fprintf(results, "%s", buf);
                }

                fflush(results);
                remove(file_path);
            }
        }
    }
    fclose(results);

}
