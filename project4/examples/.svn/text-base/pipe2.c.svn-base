#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

    int main()
    {
        int pfds[2];

        pipe(pfds);

        if (!fork()) {
            dup2(pfds[1],1);   /* make stdout same as pfds[1] */
            close(pfds[0]);    /* we don't need these */
            close(pfds[1]);
            execlp("ls", "ls", NULL);
        } else {
            dup2(pfds[0],0);   /* make stdin same as pfds[0] */
            close(pfds[1]);    /* we don't need these */
            close(pfds[0]);
            wait(NULL);
            execlp("wc", "wc", "-l", NULL);
        }
    }
