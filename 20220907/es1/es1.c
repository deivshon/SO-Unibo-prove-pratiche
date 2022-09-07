#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 4096

int do_ex(char *command, char **args, int c) {
    if(fork() == 0) {
    	printf("Pid of program launched: %d\n", getpid());
	execv(command, args);
    }
    else
    {
    	int exit_val;
    	wait(&exit_val);
    	printf("Exit value %d\n", exit_val);
    	return exit_val; // Parent returns
    }
    exit(1); // Child exits
}

int main(int argc, int *argv[]) {
	if(argc < 2) exit(EXIT_FAILURE);

	// Assumendo che l'eseguibile passato sia in /usr/bin/ e che gli argomenti siano meno di 32
	char ex_path[MAX_PATH_LENGTH] = "/usr/bin/";
	char *args[32];
	strcat(ex_path, (char *) argv[1]);
	int c = 0;
	for(int i = 0; i < argc - 1; i++) {
		// Assumendo che gli argomenti abbiano meno di 32 caratteri 
		args[i] = malloc(sizeof(char) * 32);
		strcpy(args[i], (char *) argv[i + 1]);
		c++;
	}
	args[c] = NULL;
	int exit_val;
	while(do_ex(ex_path, args, c) == 0) {
		printf("Relaunching\n");
	}
}

