#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "diskLib.h"

int main (void) {
   pid_t childpid = 0, termChildpid = 0;
   int i;

   childpid = fork();
   if(childpid==-1){
      perror("Could not create child process in main");
      return -1;
   }

   if (childpid > 0){
      // parent process enters if block
      printf("I am %d, the parent of %d and am waiting for my kid.\n", getpid(),childpid);
      //kill(childpid, 15); // send SIGINT to the child
      termChildpid = wait(&i);
	  if( WIFEXITED(i) )
	     printf("Child %d terminated normally with an exit status of %d.\n",
			                          termChildpid, WEXITSTATUS(i));
      else if( WIFSIGNALED(i) )
         printf("Child %d terminated due to uncaught signal %d\n",termChildpid, WTERMSIG(i));
   }
   else {
      // child process enters else block
      printf("I am %d the child process.\n", getpid());
      char *arg[4];
      arg[0] = "ls";
      arg[1] = "-a";
	  arg[2] = "-l";
      arg[3] = NULL;
	  /*
        This code also demonstrates output file redirection.
		I create a file and get its file descriptor.
		Then I tell this process to change where file descriptor 1 (stdout)
		normally points. Now it points to the file.
	  */
	  int fd = open("myfile", O_CREAT|O_RDWR, 0600);
	  dup2(fd, 1);
	  close(fd); // don't need this anymore, stdout points to myfile
      execvp(arg[0], arg);
      perror("execvp");
      printf("This should only print if exec fails\n");
   }
                   

   return 0;
}

