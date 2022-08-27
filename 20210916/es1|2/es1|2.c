#include <stdio.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_LENGTH 256
enum PIPES {READ, WRITE};

int print_exec(char *command, char *args[]) {
    // Something something
}

int main() {
    char buf[BUFFER_LENGTH];
    int in_instance = inotify_init();
    int l;

    if(in_instance < 0) {
        return 1;
    }

    int in_mon = inotify_add_watch(in_instance, "exec", IN_CREATE);
    while(1) {
        l = read(in_instance, buf, BUFFER_LENGTH);
        struct inotify_event *current_event = (struct inotify_event *) &buf;
        if(current_event->len) {
            char *args[32];

            char *command = strtok(current_event->name, " ");
            int i = 0;

            printf("Got command %s with arguments:\n", command);
            while(args[i] = strtok(NULL, " ")) {
                printf("%s\t", args[i]);
                i++;
            }
            printf("\n");

            args[i] = NULL;
            print_exec(command, args);
        }
    }
    printf("\n");
}
