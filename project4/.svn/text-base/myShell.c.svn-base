#include "myShell.h"

int main(void) 
{
    char *buff[20];
    char *inputString;

    //  *************Signal handling*************
    new_act.sa_handler = SIG_IGN;
    new_act.sa_flags = 0;

    sigaction(SIGINT, &new_act, &original_act);
    //  *****************************************

    // Loop forever
    while(1) {
        // Print out the prompt and get the input
        fprintf(stdout, ": ");

        inputString = get_my_args(buff);

        //check for finished background processes
        int i, j;
        for(i = 0; i < num_children; i ++)
        {
            int status = waitpid(pid_array[i], &status, WNOHANG);
            if (status != 0){
                fprintf(stdout, ":Background process %d finished\n", status);
                for(j = i; j < num_children; j ++){
                    pid_array[j]=pid_array[j+1];
                 }
                num_children--;
                i--;
             }   
        }
        /*
        for(i = 0; i < num_children; i ++)
        {
            printf("running_processes[%d] = %d\n", i, pid_array[i]);
        }
        */

        if((buff[0] == NULL) || (strcmp(buff[0], "#") == 0)) continue;

        check_command(buff);

        //return if exit is entered as first argument
        if((strcmp(buff[0], "exit") == 0)) return 0;
        if((strcmp(buff[0], "cd") == 0))
        {
            if(num_args == 1)
            {
                //printf("cd called, change directory to %s\n", getenv("HOME"));
                chdir(getenv("HOME"));
                continue;
            }
            else if(num_args == 2)
            {
                //printf("cd called, change directory to %s\n", buff[1]);
                chdir(buff[1]);
                continue;
            }
            else 
            {
                fprintf(stderr, "cd: too many arguments\n");
                continue;
            }
        }

        if(pipe_loc == 0 || pipe_loc + 1 == num_args)
        {
            fprintf(stderr, "myShell: syntax error near unexpected token `|'\n");
            continue;
        }

        if(out_redir_loc == 0 || out_redir_loc + 1 == num_args)
        {
            fprintf(stderr, "myShell: syntax error near unexpected token `>'\n");
            continue;
        }

        if(in_redir_loc == 0 || in_redir_loc + 1 == num_args)
        {
            fprintf(stderr, "myShell: syntax error near unexpected token `<'\n");
            continue;
        }

        if(background_loc != -1 && ((background_loc != (num_args - 1)) && num_args >= 2))
        {
            fprintf(stderr, "myShell: syntax error near unexpected token `&'\n");
            continue;
        }

        // Do the command
        pid_t child = do_command(buff);
        if(child != 0)
        {
            pid_array[num_children] = child;
            num_children++;
        }

        /*
        i = 0;
        while(buff[i] != '\0'){
            fprintf(stdout, "buff[%d] = %s\n", i, buff[i]);
            i++;
        }
        fprintf(stdout, "pipe_loc = %d\n", pipe_loc);
        fprintf(stdout, "out_redir_loc = %d\n", out_redir_loc);
        fprintf(stdout, "in_redir_loc = %d\n", in_redir_loc);
        fprintf(stdout, "num_args = %d\n", num_args);
        */

        //free up the malloced memory
        free(inputString);
    }// end of while(1)
}
