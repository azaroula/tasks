#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
 
int
main(int argc, char* argv[])
{
 int i,a = atoi(argv[1]);
 pid_t cpid;
 int status;
 
 printf("Before the fork\n");

 for(i=0; i<a; i++) {
	
	cpid = fork();	

	if (cpid < 0){
		printf("ERROR fork()= %d\n",cpid);
		fflush(stdout);
		exit(0);
	}
 	if (cpid == 0) {
		printf("I’m the child (id:%d) ",getpid());
		fflush(stdout);
		printf("parent id:%d\n",getppid()); 
		fflush(stdout);		
			
	}

 	else {
		printf("I’m the parent (id:%d) (I’ve got a child with id: %d)\n",getpid(), cpid);
		fflush(stdout);
		cpid = wait(&status); 
		printf("parent Done (have wait for:%d)\n",cpid);
		exit(0);
 	}
 }
 exit(0);

}

