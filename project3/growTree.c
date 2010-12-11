/*
   If I type
   growTree  [Enter]
   on the command line, your growTree executable should

 * read a filename from byte 0 of .draw_config
 * open that file and draw all the images at the right positions on the screen.
 * pause to let the user position the cursor on the screen and hit [Enter]
 * draw a tree at that position. (Top of tree will appear where the cursor was positioned.)
 * exit

 If I type
 growTree canvas2  [Enter]
 on the command line, your growTree executable should

 * print out an error message and exit if canvas2 is not an existing file in the current directory.
 * write canvas2 at byte 0 of .draw_config
 * open canvas2 and draw all the images at the right positions on the screen.
 * pause to let the user position the cursor on the screen and hit [Enter]
 * draw a tree at that position. (Top of tree will appear where the cursor was positioned.)
 * exit
 */

#include "picture.h"
#include <stdio.h>


static FIGURE lastTree;
static FIGURE newTree;

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

        //Draw a Tree where the user puts the cursor
        userMv();
        getyx(stdscr, y, x);
        drawTree(x, y);

        //set FIGURE values
        newTree.type = 'T';
        newTree.a = 0;
        newTree.b = 0;
        newTree.c = 0;
        newTree.locX = x;
        newTree.locY = y;
        newTree.spacer1 = 0;
        newTree.spacer2 = 0;
        newTree.spacer3 = 0;

        //increment number of trees
        meta.numT += 1;

        //update offset of last element
        meta.last = (((meta.numH + meta.numP + meta.numT - 1) * sizeof(FIGURE)) + FIRST_FIGURE);

        //if there were no Tree images in the file
        if(meta.numT == 1)
        {
            //save absolute byte locations of next and prev figure
            newTree.next = -1;
            newTree.prev = -1;
            meta.firstT = (((meta.numH + meta.numP) * sizeof(FIGURE)) + FIRST_FIGURE);
        }

        if(meta.numT > 1)
        {
            //save absolute byte locations of next and prev figure
            newTree.next = -1;
            newTree.prev = meta.lastT; 
        }

        //change pointers of Tree before newTree
        //check if there is at least one Tree
        if(meta.numT > 1)
        {
            //open file to write lastTree.next
            //getLock(filename);
            //fd = open (filename, O_RDWR, 0600);
            //seek to location of lastTree
            lseek(fd, meta.lastT, SEEK_SET);
            read(fd, &lastTree, sizeof(FIGURE));

            //set lastTree.next to the location of newTree
            lastTree.next = meta.last;

            //write lastTree to location of meta.lastT
            lseek(fd, meta.lastT, SEEK_SET);
            write(fd, &lastTree, sizeof(FIGURE));

            //close(fd);
            //removeLock(filename);
        }

        //update position of last tree
        meta.lastT = meta.last;

        //open file for writing
        //getLock(filename);
        //fd = open (filename, O_WRONLY, 0600);

        //write META_DATA to file
        lseek(fd, 0, SEEK_SET);
        write(fd, &meta, sizeof(META_DATA));

        //seek to the empty tree figure location
        lseek(fd, meta.last, SEEK_SET);

        //write FIGURE to file
        write(fd, &newTree, sizeof(FIGURE));

        close(fd);
        removeLock(filename);

        endCurses();
    }
    return 0;
}
