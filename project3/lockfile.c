#define _GNU_SOURCE
#include <stdio.h>
#include <sys/unistd.h>
#include <errno.h>

#include "picture.h"

void getLock(char filename[MAX_FILENAME])
{
    char * lockname = NULL;
    asprintf(&lockname, "%s%s", filename, ".LCK");
    //fprintf(stderr, "lockname = %s\n", lockname);
    while( open(lockname, O_CREAT | O_EXCL | O_RDWR, 0600) == -1 ) 
    {
        if( errno==EEXIST || errno == EINTR ) 
        {
            // error was due to file already in existence or signal interrupt, try again later
            fprintf(stderr, "trying to get the lock, but couldn't\n");
            sleep(1);
        }
        else 
        {
            // error was not due to file already in existence or a signal, quit
            perror("opening lockfile");
            return;
        }
    }
}

void removeLock(char filename[MAX_FILENAME])
{
    char * lockname = NULL;
    asprintf(&lockname, "%s%s", filename, ".LCK");
    remove(lockname);
    return;
}
