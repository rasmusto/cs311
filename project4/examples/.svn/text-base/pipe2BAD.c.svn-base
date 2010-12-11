#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
   int pfds[2];
   pid_t childpid;

   pipe(pfds);

   if ( (childpid=fork())==-1) {
      perror("fork failed");
      return -1;
   }
   if(childpid==0) {
      // child
      if ( (childpid=fork()) == -1) {
         perror("fork 2 failed");
         return -1;
	  }
	  if(childpid==0) {
         //grandchild
		 dup2(pfds[1],1);   /* change file desc. 1 */
		 close(pfds[1]);    /* we don't need these */
         close(pfds[0]);    
	     //grandchild writes to pipe not stdout
	     /*
	      This arrangement of a pipe will work when a small amount of
	      information is sent, but will not work when a large anount
	      of information is sent through the pipe. Why?
	     */
	     // Mary.txt is a small file
	         execlp("cat", "cat", "Mary.txt", NULL);
             // words_ospd.txt is a dictionary (a large file)
	     //execlp("cat", "cat", "words_ospd.txt", NULL);
	  }
	  else {
	     //child
	     dup2(pfds[0],0);   /* change file desc. 0 */
         close(pfds[0]);    /* we don't need these */
         close(pfds[1]);
         printf("waited for child %d\n", wait(NULL));
	     // child will reads from pipe not stdin
         execlp("wc", "wc", "-l", NULL);
      }
   } 
   else {
      // parent
      /* Don't leave the write end of the pipe open or the process
       * at the read end will think there are more bytes coming.
      */
      //close(pfds[1]);    /* parent doesn't need write end of pipe */
      close(pfds[0]);    /* parent doesn't need read end of pipe */
      printf("waited for child %d\n", wait(NULL));
   }
}
