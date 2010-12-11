#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    int pfds[2], status;
    char buf[30];
    pid_t childpid;

    pipe(pfds);

    if (!fork()) {  // since fork() returns 0 to the child, !pipe() is true to only the child
       fprintf(stderr, " CHILD: writing to the pipe\n");
       write(pfds[1], "test", 5);
       fprintf(stderr, " CHILD: exiting\n");
       exit(0);
    } else {
       fprintf(stderr, "PARENT: reading from pipe\n");
       read(pfds[0], buf, 5);
       fprintf(stderr, "PARENT: read \"%s\"\n", buf);
       childpid = wait(&status);
       if(WIFEXITED(status) && !WEXITSTATUS(status))
          fprintf(stderr, "Child %ld terminated normally\n", (long)childpid);
            
    }
}
