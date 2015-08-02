#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

        pid_t cpid, tpid;

        int status;

        printf("Before the fork\n");

        if ((cpid = fork()) == 0) {
                printf("I’m the child (sleeping for 3 seconds)\n");
                sleep(3);
                printf("child done\n");
        } else {
                printf("I’m the parent (I’ve got a child with id %d)\n", cpid);
                tpid = wait(&status);
                if (tpid == -1) {
                       printf("wait() failed");
                        return EXIT_FAILURE;
                }
                if (WIFEXITED(status)) {
                        printf("Child done with Status: %d\n", WEXITSTATUS(status));
                }
                printf("parent: wait returned pid %d\n", tpid);
        }
        exit(0);

}

