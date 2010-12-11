#include "myShell.h"

void check_command(char **args)
{
    pipe_loc = -1;
    out_redir_loc = -1;
    in_redir_loc = -1;
    background_loc = -1;

    int i = 0;
    while(args[i] != NULL)
    {
        if(strcmp(args[i], "|") == 0)
        { pipe_loc = i; }

        if(strcmp(args[i], ">") == 0)
        { out_redir_loc = i; }

        if(strcmp(args[i], "<") == 0)
        { in_redir_loc = i; }

        if(strcmp(args[i], "&") == 0)
        { background_loc = i; }

        i++;
    }
    num_args = i;
}

/*
ls -l -a > newfile
grep "test" < dump

ls -la | grep "test"
*/
