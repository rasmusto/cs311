#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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
      kill(childpid, SIGINT); // send SIGINT to the child, SIGINT is signal #2
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
      execl("/bin/ls", "ls", "-l", NULL);
      perror("execl");
      printf("This should only print if exec fails\n");
   }
                   

   return 0;
}

