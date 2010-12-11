/*
   If I type
   buildHouse [Enter]
   on the command line, your buildHouse executable should

 * read a filename from byte 0 of .draw_config
 * open that file and draw all the images at the right positions on the screen.
 * pause to let the user position the cursor on the screen and hit [Enter]
 * draw a tree at that position. (Top of tree will appear where the curser was positioned.)
 * exit

 If I type
 buildHouse canvas2  [Enter]
 on the command line, your buildHouse executable should

 * print out an error message and exit if canvas2 is not an existing file in the current directory.
 * write canvas2 at byte 0 of .draw_config
 * open canvas2 and draw all the images at the right positions on the screen.
 * pause to let the user position the cursor on the screen and hit [Enter]
 * draw a house at that position. (Top of house will appear where the curser was positioned.)
 * exit
 */

#include "picture.h"
#include <stdio.h>


static FIGURE lastHouse;
static FIGURE newHouse;

int main(int argc, const char *argv[])
{
    int fd;
    int x, y;
    char filename[MAX_FILENAME];
    static META_DATA meta;


    //File specified in command line
    if (argc == 2)
    {
        memcpy(filename, argv[1], MAX_FILENAME);
        //getLock(filename);
        if (open(filename, O_RDONLY, 0600)  == -1){
            printf("ERROR: File doesn't exist\n");
            //removeLock(filename);
            exit(1);
        }
        //removeLock(filename);
    }

    if (argc == 1)
    {
        //Read filename from .draw_config
        getLock(".draw_config");
        fd = open (".draw_config", O_RDONLY, 0600);
        read (fd, filename, MAX_FILENAME);
        close(fd);
        removeLock(".draw_config");
    }

    if (argc == 2)
    {
        //write filename to .draw_config
        getLock(".draw_config");
        fd = open (".draw_config", O_WRONLY, 0600);
        write (fd, filename, MAX_FILENAME);
        close (fd);
        removeLock(".draw_config");
    }

    if (argc == 1 || argc == 2)
    {
        //Open canvas file
        getLock(filename);
        fd = open (filename, O_RDWR, 0600);

        initCurses();

        //read metadata from file
        read (fd, &meta, sizeof(META_DATA));

        showAll(fd, meta);

        //close(fd);
        //removeLock(filename);

        //Draw a house where the user puts the cursor
        userMv();
        getyx(stdscr, y, x);
        drawHouse(x, y);

        //set FIGURE values
        newHouse.type = 'H';
        newHouse.a = 0;
        newHouse.b = 0;
        newHouse.c = 0;
        newHouse.locX = x;
        newHouse.locY = y;
        newHouse.spacer1 = 0;
        newHouse.spacer2 = 0;
        newHouse.spacer3 = 0;

        //increment number of houses
        meta.numH += 1;

        //update offset of last element
        meta.last = (((meta.numH + meta.numP + meta.numT - 1) * sizeof(FIGURE)) + FIRST_FIGURE);

        //if there were no house images in the file
        if(meta.numH == 1)
        {
            //save absolute byte locations of next and prev figure
            newHouse.next = -1;
            newHouse.prev = -1;
            meta.firstH = (((meta.numP + meta.numT) * sizeof(FIGURE)) + FIRST_FIGURE);
        }

        if(meta.numH > 1)
        {
            //save absolute byte locations of next and prev figure
            newHouse.next = -1;
            newHouse.prev = meta.lastH; 
        }

        //change pointers of house before newHouse
        //check if there is at least one house
        if(meta.numH > 1) 
        {
            //open file to write lastHouse.next
            //getLock(filename);
            //fd = open (filename, O_RDWR, 0600);
            //seek to location of lastHouse
            lseek(fd, meta.lastH, SEEK_SET);
            read(fd, &lastHouse, sizeof(FIGURE));

            //set lastHouse.next to the location of newHouse
            lastHouse.next = meta.last;

            //write lastHouse to location of meta.lastH
            lseek(fd, meta.lastH, SEEK_SET);
            write(fd, &lastHouse, sizeof(FIGURE));

            //close(fd);
            //removeLock(filename);
        }

        //update position of last house
        meta.lastH = meta.last;

        //open file for writing
        //getLock(filename);
        //fd = open (filename, O_WRONLY, 0600);

        //write META_DATA to file
        lseek(fd, 0, SEEK_SET);
        write(fd, &meta, sizeof(META_DATA));

        //seek to the empty house figure location
        lseek(fd, meta.last, SEEK_SET);

        //write FIGURE to file
        write(fd, &newHouse, sizeof(FIGURE));

        close(fd);
        removeLock(filename);

        endCurses();
    }
    return 0;
}
