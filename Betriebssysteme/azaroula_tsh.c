#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "makeargv.h"
#include "makeargv.c"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "azaroula_dll.h"

#define MAX 1000
#define TRUE 1
#define SET 1
#define OFF 0
 
struct proc_info{
	struct list_head head;
	int pid;
	int exitStatus;
	int exitFlag;
	char runningStatus[10];
	int jobID;	
	char name[50];
			
};    

void getProcessStatus(struct proc_info *prozess) {
	int status;	

	if (waitpid(prozess->pid, &status, WNOHANG)) {
		prozess->exitFlag = SET;
		strncpy(prozess->runningStatus, "finished", 10);
		if (WIFEXITED(status)) {	
			prozess->exitStatus = WEXITSTATUS(status); 

		} else if (WIFSIGNALED(status)) {
			prozess->exitStatus = WTERMSIG(status);	
		} else {
			prozess->exitStatus = -1;
		}	
	} else {
		strncpy(prozess->runningStatus, "running", 10);
		prozess->exitStatus = 0;
	}
}

void freeList (struct list_head *anker) {
	struct list_head *tmp, *tmp2;
	tmp = anker->next;
 	

 	while (tmp != anker) {
		tmp2 = tmp;
		tmp = tmp->next;
		free((struct proc_info*)tmp2);
		
	}
}
 
void runProcess(char ***argvp) {
	pid_t cpid;
 	int status;
 	
 	if ((cpid = fork()) > 0) {
 		if (waitpid(cpid, &status, 0) == -1) {
			 perror("waitpid()");
			 fflush(stdout);	
		} else {
			if (WIFEXITED(status)) {
				printf("[status=%d]\n", WEXITSTATUS(status)); 
				fflush(stdout);
			} else if (WIFSIGNALED(status)) {
				printf("[status=%d]\n",WTERMSIG(status));
				fflush(stdout);
			} else {
				printf("[status=%d]\n",-1);
			}	
		}
 	}
 	if (cpid == 0) {
		execvp(*argvp[0], *argvp);
		printf("[invalid command: %s]\n",*argvp[0]);
		fflush(stdout);
		exit(1);
 	}

 	if (cpid < 0) {
		perror("fork()");
		fflush(stdout);
 	}

}
void job(char ***argvp, struct proc_info *prozess, int jobNumber) {
	pid_t cpid;
 	
	if ((cpid = fork()) == 0) {
		execvp((*argvp)[1], *argvp+1);	
		exit(1);
 	}
	if (cpid > 0) {
		prozess->pid = cpid;
		prozess->jobID = jobNumber;
		strncpy(prozess->name, (*argvp)[1], 50);		
	}

	if (cpid < 0) {
		perror("fork()");
		fflush(stdout);
 	}
} 

void list(struct list_head *anker) {
	struct list_head *tmp;
	tmp = anker->next;
 	
 	while (tmp != anker) {
		
		if (!((struct proc_info*)tmp)->exitFlag) { 
			getProcessStatus(((struct proc_info*)tmp));
		}

		printf("%d (pid %d %s status = %d): %s \n",
			((struct proc_info*)tmp)->jobID,
			((struct proc_info*)tmp)->pid,
			((struct proc_info*)tmp)->runningStatus,
			((struct proc_info*)tmp)->exitStatus,
			((struct proc_info*)tmp)->name);
		tmp = tmp->next;
	}	
}

void info(struct list_head *anker, int infoNumber) {
	struct list_head *tmp;
	tmp = anker->next;
 	
	while (tmp != anker) {
		
		if (((struct proc_info*)tmp)->jobID == infoNumber) { 
			if (!((struct proc_info*)tmp)->exitFlag) { 
				getProcessStatus(((struct proc_info*)tmp));
			}
			printf("%d (pid %d %s status = %d): %s \n",
			((struct proc_info*)tmp)->jobID,
			((struct proc_info*)tmp)->pid,
			((struct proc_info*)tmp)->runningStatus,
			((struct proc_info*)tmp)->exitStatus,
			((struct proc_info*)tmp)->name);
		}
		tmp = tmp->next;
	}
} 

void wait_job(struct list_head *anker, int waitNumber) {
	int status;	
	struct list_head *tmp;
	tmp = anker->next;
	
	while (tmp != anker) {
		if (((struct proc_info*)tmp)->jobID == waitNumber) {
		 	if (!((struct proc_info*)tmp)->exitFlag) { 
				if ((waitpid(((struct proc_info*)tmp)->pid, &status, 0)) == -1) {
					perror("waitpid()");
					fflush(stdout);	
				} else {
					if (WIFEXITED(status)) {
						((struct proc_info*)tmp)->exitStatus = WEXITSTATUS(status); 
					} else if (WIFSIGNALED(status)) {
						((struct proc_info*)tmp)->exitStatus = WTERMSIG(status); 		
					} else {
						((struct proc_info*)tmp)->exitStatus = -1;
					}
					((struct proc_info*)tmp)->exitFlag = SET;
					strncpy(((struct proc_info*)tmp)->runningStatus, "finished", 10);	
					 
				}
			}
		}
		tmp = tmp->next;
	}
} 

void kill_job(struct list_head *anker, int killNumber) {	
	struct list_head *tmp;
	tmp = anker->next;
	
	while (tmp != anker) {
		if (((struct proc_info*)tmp)->jobID == killNumber) {
		 	if (!((struct proc_info*)tmp)->exitFlag) { 
				if (kill(((struct proc_info*)tmp)->pid, SIGKILL) < 0) {
					perror("kill()");
					fflush(stdout);
				}
			}
		}
		tmp = tmp->next;
	}
} 

int execBuildin(int argc, char ***argvp, int jobNumber, struct list_head *anker, void (*ptrFunction) (struct list_head *anker, int argNumber)) {
	int argNumber;
	if (argc != 2) {
		printf("[Wrong number of arguments]\n");
		return 1;
	}
	argNumber = atoi((*argvp)[1]);
	if (argNumber < jobNumber) {			
		(*ptrFunction) (anker, argNumber);
		return 0;
		} else {
			printf("[job not found]\n");
			return 1;
		}			
} 

int main() {
 	int jobNumber = 0;
	int argc, i;
	int FLAG;
 	char *buildin[]={"job", "list", "info", "wait", "kill", "quit"};
 	char eingabe[MAX], ***argvp;
	struct list_head *anker,*tmp;
	
	struct proc_info *prozess;
 
	anker = malloc(sizeof(struct list_head));
	list_init(anker);
	tmp = anker; 

 	argvp=malloc(sizeof (char**));
 	while (TRUE) {
 		printf("tsh>");
		FLAG = OFF;
		fgets(eingabe,MAX,stdin);
	
		eingabe[strlen(eingabe)-1]= '\0';

		argc = makeargv(eingabe," ",argvp);
	
		if (!argc) {
			continue;
		}

		for(i=0;i<6;i++){
			if (strcmp((*argvp[0]),(buildin[i]))==0) {
				FLAG = SET;
				
				switch (i) {
					case 0: //job
						if (argc == 1){
							printf("[Too few Arguments]\n");	
							break;
						}
						prozess = malloc(sizeof(struct proc_info));
						prozess->exitFlag = OFF; 
						job(argvp, prozess, jobNumber);
						list_add(&prozess->head, tmp);
						tmp = &prozess->head;
						jobNumber++;
						break; 

					case 1: //list
						list(anker); 
						break; 

					case 2: //info
						execBuildin(argc, argvp, jobNumber, anker, info);	
						break;
 
					case 3: //wait
						execBuildin(argc, argvp, jobNumber, anker, wait_job);			
						break;

					case 4: //kill
						execBuildin(argc, argvp, jobNumber, anker, kill_job);	
						break; 

					case 5: //quit																
						printf("%s\n",buildin[i]);
						freeList(anker);
					    freemakeargv(*argvp); 
						free(argvp);
						free(anker); 
						exit(0);
				}
			}
		}
		if (!FLAG) {
			runProcess(argvp);		
		}
 		freemakeargv(*argvp);
 	}
}
