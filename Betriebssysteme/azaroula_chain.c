#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char* argv[]) {
	if (argc == 1) {
		printf("Keine Anzahl von Prozessen angegeben!!\n");
		return EXIT_FAILURE;
    }

 	int i,a = atoi(argv[1]);
 	pid_t cpid;
 
 	printf("Before the fork\n");

 	for (i=0; i<a; i++) {
	
		cpid = fork();	

		if (cpid == -1) {
			printf("fork failed\n");
			fflush(stdout);
			return EXIT_FAILURE;
		}
 		if (cpid == 0) {
			printf("I’m the child (id:%d), (I’ve got a parent with id:%d)\n",getpid(), getppid());
			fflush(stdout);
		} else {
			printf("I’m the parent (id:%d) (I’ve got a child with id: %d)\n",getpid(), cpid);
			fflush(stdout);
			exit(0);
 		}
 	}
 	exit(0);
}

