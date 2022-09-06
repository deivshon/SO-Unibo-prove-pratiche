#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int sig, siginfo_t *info, void *ucontext){
	union sigval value = info->si_value;
	long tmp = (long) value.sival_ptr;

	printf("Received %ld\n", tmp);
}

int main(int argc, char **argv){
	printf("PID: %d\n", getpid());

	struct sigaction sigact;
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = sig_handler;
	while(1) {
		int ret = sigaction(SIGUSR1, &sigact, NULL);
	}

	return 0;
}