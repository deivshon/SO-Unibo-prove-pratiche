#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char **argv) {
	if(argc != 3){
		exit(EXIT_FAILURE);
	}

	pid_t pid = atoi(argv[1]);
	long msg = atol(argv[2]); 
	
	union sigval value;
	value.sival_ptr = (void *) msg;
	int res = sigqueue(pid, SIGUSR1, value);
	if(res != 0){
		printf("Error\n");
		exit(EXIT_FAILURE);
	}

	return 0;
}
