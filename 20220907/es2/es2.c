#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define MAX_PATH_LENGTH 4096

double get_timestamp() {
	struct timeval timestamp;
	double timestamp_decimal = 0;

	gettimeofday(&timestamp, NULL);
	timestamp_decimal = (double) timestamp.tv_sec + ((double) timestamp.tv_usec / 1e6);
	return timestamp_decimal;
}

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
		args[i] = malloc(sizeof(char) * 32);
		strcpy(args[i], (char *) argv[i + 1]);
		c++;
	}
	args[c] = NULL;
	int exit_val = 0;
	double starting_ts;
	do {
		starting_ts = get_timestamp();
		printf("Launching program at %f\n", starting_ts);
		exit_val = do_ex(ex_path, args, c);
	} while (exit_val == 0 && (get_timestamp() - starting_ts) > 1);
}

