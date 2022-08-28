#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void do_exec(char *command, char **args, int argc)
{
    // Only works with 2 or more arguments for ./hw (why?)
    int link[2];
    pid_t pid;
    char foo[4096];

    // if (pipe(link) == -1)
    //     exit(EXIT_FAILURE);
    if ((pid = fork()) == -1)
        exit(EXIT_FAILURE);

    if (pid == 0)
    {
        // dup2(link[1], STDOUT_FILENO);
        // close(link[0]);
        // close(link[1]);
        execv(command, args);
    }
    else
    {
        // close(link[1]);
        // int nbytes = read(link[0], foo, sizeof(foo));
        // // printf("Output: (%.*s)\n", nbytes, foo);
        wait(NULL);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 0;
    strcpy(argv[0], "\b");

    char *aftdot = strrchr(argv[1], '.');
    if (aftdot && strcmp(aftdot, ".so") != 0)
    {
        char *command = realpath(argv[1], NULL);
        char *args[16];
        int c = 0;
        for (int i = 1; i < argc; i++)
        {
            args[i - 1] = malloc(sizeof(char) * 32);
            strcpy(args[i - 1], argv[i]);
            c++;
        }
        do_exec(command, args, c);
        return 1;
    }

    void *handle = dlopen(argv[1], RTLD_LAZY);
    void (*hw_func)(int c, char *ar[]);
    if (handle == NULL)
    {
        return 1;
    }

    *(void **)(&hw_func) = dlsym(handle, "main");
    if (!hw_func)
    {
        printf("No such symbol");
    }
    else
    {
        hw_func(argc, argv);
    }
}
