#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void do_ls_l_a() {
    if(fork() == 0) {
        execlp("/usr/bin/ls", "ls", "-la");
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
    printf("PID before calling do_ls_la %d\n", getpid());

    do_ls_l_a();
    wait(NULL); // Wait until the process spawned by fork + execl ends  
}
