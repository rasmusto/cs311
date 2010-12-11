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
            removeLock(filename);
            exit(1);
        }
        removeLock(filename);
    }

    if (argc == 1)
    {
        //Read filename from .draw_config
        getLock(".draw_config");
        fd = open (".draw_config", O_RDONLY, 0600);
        read (fd, filename, MAX_FILENAME); 
        close (fd);
        removeLock(".draw_config");
    }

    if (argc == 1 || argc == 2)
    {
        initCurses();

        //Open canvas file
        getLock(filename);
        fd = open (filename, O_RDONLY, 0600);

        //read metadata from file
        read (fd, &meta, sizeof(META_DATA));

        //print out all figures
        showAll(fd, meta);

        close(fd);
        removeLock(filename);
    }
    refresh();
    endCurses();

    return 0;
}
