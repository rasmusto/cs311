/*
# If I type
showPeople [Enter]
on the command line, your showPeople executable should

 * read a filename from byte 0 of .draw_config
 * open that file and draw all the person images at the right positions on the screen. At this point, only persons should be on the screen. Draw the persons by following the "person linked-list". Do not simply go through the whole file and test for persons. I will test for this.
 * exit

# If I type
showPeople canvas2  [Enter]
on the command line, your showPeople executable should

 * print out an error message and exit if canvas2 is not an existing file in the current directory.
 * write canvas2 at byte 0 of .draw_config
 * open canvas2 and draw all the person images at the right positions on the screen. At this point, only persons should be on the screen. Draw the persons by following the "person linked-list". Do not simply go through the whole file and test for persons. I will test for this.
 * exit
 */

#include "picture.h"

int x, y;

int main(int argc, const char *argv[])
{
    int fd;
    char filename[MAX_FILENAME];
    static META_DATA meta;

    //File specified in command line
    if (argc == 2)
    {
        memcpy(filename, argv[1], MAX_FILENAME);
        getLock(filename);
        if (open(filename, O_RDONLY, 0600)  == -1){
            printf("ERROR: File doesn't exist\n");
            close(fd);
            removeLock(filename);
            exit(1);
        }
        close(fd);
        removeLock(filename);
    }

    if (argc == 1)
    {
        //Read filename from .draw_config
        getLock(filename);
        fd = open (".draw_config", O_RDONLY, 0600);
        read (fd, filename, MAX_FILENAME);
        close (fd);
        removeLock(filename);
    }

    if (argc == 1 || argc == 2)
    {
        initCurses();

        //Open canvas file
        fd = open (filename, O_RDONLY, 0600);

        //read metadata from file
        read (fd, &meta, sizeof(META_DATA));

        //read first FIGURE from file
        if(meta.numP > 0)
        {
            showPeople(fd, meta);
        }
    }
    close(fd);
    removeLock(filename);
    refresh();
    endCurses();
    return 0;
}
