/*
   If I type
   putPerson [Enter]
   on the command line, your putPerson executable should

 * read a filename from byte 0 of .draw_config
 * open that file and draw all the images at the right positions on the screen.
 * pause to let the user position the cursor on the screen and hit [Enter]
 * draw a tree at that position. (Top of tree will appear where the curser was positioned.)
 * exit

 If I type
 putPerson canvas2  [Enter]
 on the command line, your putPerson executable should

 * print out an error message and exit if canvas2 is not an existing file in the current directory.
 * write canvas2 at byte 0 of .draw_config
 * open canvas2 and draw all the images at the right positions on the screen.
 * pause to let the user position the cursor on the screen and hit [Enter]
 * draw a person at that position. (Top of person will appear where the curser was positioned.)
 * exit
 */

#include "picture.h"
#include <stdio.h>


static FIGURE lastPerson;
static FIGURE newPerson;

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

        //Draw a Person where the user puts the cursor
        userMv();
        getyx(stdscr, y, x);
        drawPerson(x, y);

        //set FIGURE values
        newPerson.type = 'P';
        newPerson.a = 0; 
        newPerson.b = 0;
        newPerson.c = 0;
        newPerson.locX = x;
        newPerson.locY = y;
        newPerson.spacer1 = 0;
        newPerson.spacer2 = 0;
        newPerson.spacer3 = 0;

        //increment number of persons
        meta.numP += 1;

        //update offset of last element
        meta.last = (((meta.numH + meta.numP + meta.numT - 1) * sizeof(FIGURE)) + FIRST_FIGURE);

        //if there were no Person images in the file
        if(meta.numP == 1)
        {
            //save absolute byte locations of next and prev figure
            newPerson.next = -1;
            newPerson.prev = -1;
            meta.firstP = (((meta.numH + meta.numT) * sizeof(FIGURE)) + FIRST_FIGURE);
        }

        if(meta.numP > 1)
        {
            //save absolute byte locations of next and prev figure
            newPerson.next = -1;
            newPerson.prev = meta.lastP; 
        }

        //change pointers of Person before newPerson
        //check if there is at least one Person
        if(meta.numP > 1) 
        {
            //open file to write lastPerson.next
            //getLock(filename);
            //fd = open (filename, O_RDWR, 0600);
            //seek to location of lastPerson
            lseek(fd, meta.lastP, SEEK_SET);
            read(fd, &lastPerson, sizeof(FIGURE));

            //set lastPerson.next to the location of newPerson
            lastPerson.next = meta.last;

            //write lastPerson to location of meta.lastP
            lseek(fd, meta.lastP, SEEK_SET);
            write(fd, &lastPerson, sizeof(FIGURE));

            //close(fd);
            //removeLock(filename);
        }

        //update position of last person
        meta.lastP = meta.last;

        //open file for writing
        //getLock(filename);
        //fd = open (filename, O_WRONLY, 0600);

        //write META_DATA to file
        lseek(fd, 0, SEEK_SET);
        write(fd, &meta, sizeof(META_DATA));

        //seek to the empty person figure location
        lseek(fd, meta.last, SEEK_SET);

        //write FIGURE to file
        write(fd, &newPerson, sizeof(FIGURE));

        close(fd);
        removeLock(filename);

        endCurses();
    }
    return 0;
}
