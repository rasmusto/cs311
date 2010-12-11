#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>

    int main()
    {
	char test[] = "This wrote correctly to the pipe.";
        int pfds[2];
	char buf[sizeof(test)];
	int pid;
	int status;
	int testp;

        if((testp = pipe(pfds)) == -1)
	{
	    perror("Could not pipe");
	}
	fprintf(stderr,"testp: %d\n",testp);
	
	if((pid = fork()) == -1)
	{
	    perror("Could not fork");
	}

        if(pid == 0) {	//child executes this
	    fprintf(stderr,"Child executing.\n");
            if(dup2(pfds[1],1) == -1)   /* make stdout same as pfds[1] */
	    {
		perror("Failed to dup.\n");
	    }
            if(close(pfds[0]) == -1)    /* we don't need these */
	    {
                fprintf(stderr,"pfds[0]=%d\n",pfds[0]);
		perror("Could not close pfds0 - first one\n");
	    }
            if(close(pfds[1]) == -1)
	    {
		perror("Could not close pfds1 - first one\n");
	    }
	    if(write(1, &test, sizeof(test)) == -1)
	    {
		perror("Failed to write.\n");
	    }
        }
	if(pid > 0)
	{	//parent executes this
	    fprintf(stderr,"Parent waiting on child: %d\n",pid);
            if(dup2(pfds[0],0) == -1)   /* make stdin same as pfds[0] */
	    {
		perror("Faild to dup.\n");
	    }
           // if(close(pfds[1]) == -1)    /* we don't need these */
	   // {
	   //     perror("Failed to close pfds1. - second one\n");
	   // }  
            if(close(pfds[0]) == -1)
	    {
		perror("Failed to close pfds0. - second one\n");
	    }
            if((pid = wait(&status)) == -1)
	    {
		perror("Failed to wait for child.");
	    }
	    fprintf(stderr,"status: %d\n",status);
	    if(WIFEXITED(status))
	    {
		fprintf(stderr,"Child %d exited normally with return status %d.\n",pid,WEXITSTATUS(status));
	    }
	    if(read(0, buf, sizeof(test)) == -1)
	    {
		perror("Failed to read.\n");
	    }
	    fprintf(stderr,"Parent read: %s\n",buf);
//            execlp("wc", "wc", "-l", NULL);
        }
    }
