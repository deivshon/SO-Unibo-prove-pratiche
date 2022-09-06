#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

void do_ls_la() {
    if(fork() == 0) {
        execlp("/usr/bin/ls", "ls", "-la", NULL);
    }
}

void do_ls_la_buf() {
    int piped[2];
    if(pipe(piped) == -1) {
        printf("Couldn't initiate pipe\n");
        exit(EXIT_FAILURE);
    }

    if(fork() == 0) {
        close(piped[0]);    // close read end of child
        dup2(piped[1], 1);  // stdout to pipe
        dup2(piped[1], 2);  // stderr to pipe
        close(piped[1]);    // close write end of child: no longer needed

        execlp("/usr/bin/ls", "ls", "-la", NULL);
    }
    else {
        int c = 0; // Bytes read into buffer each time
        char buf[1024] = "";
        close(piped[1]);    // close write end of parent

        while(c = read(piped[0], buf, sizeof(buf) - 1)) {
            // Sets the byte after the last one read to '\0', terminating the string
            buf[c] = '\0';

            printf("%s", buf);
        }
        close(piped[0]);    // close read end of parent: no longer needed
    }
}

int main() {
    printf("Before fork, with PID %d\n", getpid());

    if(fork() == 0) { // Child arm
        pid_t child_pid = getpid();
        pid_t parent_pid = getppid(); // Note the extra 'p'

        printf("I'm the child process, with PID %d and parent PID %d\n", child_pid, parent_pid);

        exit(EXIT_SUCCESS);
    }
    else { // Parent arm
        wait(NULL); // Wait until the fork child arm above ends
        printf("I'm the parent process process, with PID %d\n", getpid());
    }
    printf("PID before calling do_ls_la_buf %d\n", getpid());

    do_ls_la_buf();
    wait(NULL); // Wait until the process spawned by fork + execl ends  
}
