#include "myShell.h"

int do_command(char **args) 
{
    int pfd[2];

    int status;  
    pid_t child_id;

    // Fork the child process
    child_id = fork();
    
    struct sigaction ignore_act;
    ignore_act.sa_handler = SIG_IGN;
    ignore_act.sa_flags = 0;

    // Check for errors in fork()
    if(child_id == -1)
    {
        switch(errno) {
            case EAGAIN:
                perror("Error EAGAIN: ");
                return -1;
            case ENOMEM:
                perror("Error ENOMEM: ");
                return -1;
        }
    }

    if(child_id == 0 && background_loc == -1)
    {
        sigaction(SIGINT, &original_act, NULL);

        //check for input redirection
        if(in_redir_loc != -1)
        {
            int fd = open(args[in_redir_loc + 1], O_RDONLY, 0600);
            //change stdin to fd
            dup2(fd, 0);
            close(fd);
            args[in_redir_loc] = NULL;
        }

        //check for output redirection
        if(out_redir_loc != -1)
        {
            int fd = open(args[out_redir_loc + 1], O_CREAT|O_WRONLY, 0600);
            //change stdout to fd
            dup2(fd, 1);
            close(fd);
            args[out_redir_loc] = NULL;
        }

        //check for background command
        if(background_loc != -1)
        {
            args[background_loc] = NULL;
        }

        //check for pipes
        if(pipe_loc != -1)
        {
            pid_t pipe_child_id;

            pipe(pfd);

            pipe_child_id = fork();

            if(pipe_child_id > 0)
            {
                //change stdout of 1st child to input of pipe
                dup2(pfd[1], 1);
                close(pfd[1]);
                close(pfd[0]);
                args[pipe_loc] = NULL;
            }
            if(pipe_child_id == 0)
            {
                //change stdin of 2nd child to output of pipe
                dup2(pfd[0], 0);
                close(pfd[0]);
                close(pfd[1]);
                execvp(args[pipe_loc + 1], &args[pipe_loc + 1]);
                perror("second child in pipe failed");
            }
        }

        // Execute the command
        execvp(args[0], args);
        perror("child failed");

        exit(-1);
    }

    if(child_id == 0 && background_loc != -1)
    {
        sigaction(SIGINT, &new_act, NULL);

        //check for input redirection
        if(in_redir_loc != -1)
        {
            int fd = open(args[in_redir_loc + 1], O_RDONLY, 0600);
            //change stdin to fd
            dup2(fd, 0);
            close(fd);
            args[in_redir_loc] = NULL;
        }

        //check for output redirection
        if(out_redir_loc != -1)
        {
            int fd = open(args[out_redir_loc + 1], O_CREAT|O_WRONLY, 0600);
            //change stdout to fd
            dup2(fd, 1);
            close(fd);
            args[out_redir_loc] = NULL;
        }

        //check for background command
        if(background_loc != -1)
        {
            args[background_loc] = NULL;
        }

        //check for pipes
        if(pipe_loc != -1)
        {
            pid_t pipe_child_id;

            pipe(pfd);

            pipe_child_id = fork();

            if(pipe_child_id > 0)
            {
                //change stdout of 1st child to input of pipe
                dup2(pfd[1], 1);
                close(pfd[1]);
                close(pfd[0]);
                args[pipe_loc] = NULL;
            }
            if(pipe_child_id == 0)
            {
                //change stdin of 2nd child to output of pipe
                dup2(pfd[0], 0);
                close(pfd[0]);
                close(pfd[1]);
                execvp(args[pipe_loc + 1], &args[pipe_loc + 1]);
                perror("second child in pipe failed");
            }
        }

        // Execute the command
        execvp(args[0], args);
        perror("child failed");

        exit(-1);
    }

    /*
    //print debug information
    fprintf(stdout, "executing %s\n", args[0]);
    if(pipe_loc != -1)
    fprintf(stdout, "found a pipe at args[%d]\n", pipe_loc);
    if(in_redir_loc != -1)
    fprintf(stdout, "found an input redir at args[%d]\n", in_redir_loc);
    if(out_redir_loc != -1)
        fprintf(stdout, "found an output redir at args[%d]\n", out_redir_loc);
    if(background_loc != -1)
        fprintf(stdout, "found an ampersand at args[%d]\n", background_loc);
    */
    
    if(background_loc == -1)
    {
        // Wait for the child process to complete, if necessary
        waitpid(child_id, &status, 0);
        if ( WIFSIGNALED(status) )
            printf("Child %ld terminated due to signal %d\n", (long)child_id, WTERMSIG(status) );
    }
    else
    {
        sigaction(SIGINT, &new_act, NULL);
        //int status = waitpid(child_id, &status, WNOHANG);
        printf(":Backround process %ld started\n", (long)child_id);
        return child_id;
    }
    
    return 0;
}
