/*
If I type
createPict canvas1  [Enter]   <- canvas1 is just a filename. Any name could go here.
on the command line, your createPict executable should

    * exit with an error message if a file named canvas1 already exists in the current directory.
    * otherwise, create a file named canvas1 in the current directory. Write your metadata at the top of this file to help you to keep track of where first and last images of each type (tree, house, person) are stored and how many of each type are stored.
      Write canvas1 at byte 0 of .draw_config
      and exit.
    * If no filename is provided, i.e. user types createPict and hits [Enter], your program should print out a usage message and exit.
*/

#include "picture.h"

int main(int argc, const char *argv[])
{
    int fd;
    char filename[MAX_FILENAME];

    META_DATA meta;

    //Check for a single argument
    if (argc != 2)
    {
        printf("USAGE: createPict <filename>\n");
        exit(1);
    }

    memcpy(filename, argv[1], MAX_FILENAME);

    //If file exists, exit with error
    getLock(filename);
    if (open(filename, O_RDONLY, 0600) != -1)
    {
        printf("ERROR: File exists\n");
        removeLock(filename);
        exit(1);
    }
    //else, create a file and edit .draw_config
    else
    {
        //write metadata to file specified on command line
        removeLock(filename);
        getLock(filename);
        fd = open (filename, O_CREAT | O_RDWR, 0600);

        meta.first = FIRST_FIGURE;
        meta.firstH = -1;
        meta.firstT = -1;
        meta.firstP = -1;
        meta.lastH = -1;
        meta.lastT = -1;
        meta.lastP = -1;
        meta.last = FIRST_FIGURE;
        meta.numT = 0;
        meta.numH = 0;
        meta.numP = 0;

        //write meta data to file
        write (fd, &meta, sizeof(META_DATA));
        close (fd);
        removeLock(filename);

        //write file name to .draw_config
        getLock(".draw_config");
        fd = open (".draw_config", O_WRONLY, 0600);
        write (fd, argv[1], strlen(argv[1]));
        close (fd);
        removeLock(".draw_config");
    }
    return 0;
}
