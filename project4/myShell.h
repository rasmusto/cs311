#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>


void *get_my_args(char *buff[]);
pid_t do_command(char **args);
void check_command(char **args);

struct sigaction original_act, new_act;

pid_t pid_array[100];

int pipe_loc;
int out_redir_loc;
int in_redir_loc;
int background_loc;

int num_args;
int num_children;
