// compile gcc -o sigBlockFlop -lrt sigBlock.c

#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int counter = 0;
    int childpid, n;
    sigset_t newSet, origSet;
    sigfillset( &newSet );  // newSet contains all the signals

    struct sigaction original_act, new_act;

    // assign values to structure members
    new_act.sa_handler = SIG_IGN;
    new_act.sa_flags = 0;

    sigaction(SIGINT, &new_act, &original_act);

    childpid = fork();
    if(childpid == 0) {
        //sigaction(SIGINT, &original_act, NULL);
        fprintf(stderr, "shhhh, child is sleeping for 4 seconds!\n");
        sleep(4);
        execlp("ls", "ls", "-l", NULL);
        perror("main: exec");
    }

    while (1) {
        counter++;
        if (counter == 10) {
            printf("resetting signal handler to old way (default way)\n");
            sigaction(SIGINT, &original_act, NULL);
        }
        printf("sleeping.\n");
        sleep(1);
        n = waitpid(childpid, NULL, WNOHANG);
        fprintf(stderr, "Return of waitpid was %d\n", n);
    }
}
