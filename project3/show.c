#include "picture.h"

static FIGURE house;
static FIGURE person;
static FIGURE tree;

void showHouses(int fd, META_DATA meta)
{
    //read first House figure to house
    lseek(fd, meta.firstH, SEEK_SET);
    read (fd, &house, sizeof(FIGURE));

    drawHouse(house.locX, house.locY);

    //draw Houses to screen
    while(house.next != -1)
    {
        lseek(fd, house.next, SEEK_SET);
        read (fd, &house, sizeof(FIGURE));

        drawHouse(house.locX, house.locY);
    }
    return;
}

void showPeople(int fd, META_DATA meta)
{
    //read first Person figure to person
    lseek(fd, meta.firstP, SEEK_SET);
    read (fd, &person, sizeof(FIGURE));

    drawPerson(person.locX, person.locY);

    //draw People to screen
    while(person.next != -1)
    {
        lseek(fd, person.next, SEEK_SET);
        read (fd, &person, sizeof(FIGURE));

        drawPerson(person.locX, person.locY);
    }
    return;
}

void showTrees(int fd, META_DATA meta)
{
    //read first Tree figure to tree
    lseek(fd, meta.firstT, SEEK_SET);
    read (fd, &tree, sizeof(FIGURE));

    drawTree(tree.locX, tree.locY);

    //draw Trees to screen
    while(tree.next != -1)
    {
        lseek(fd, tree.next, SEEK_SET);
        read (fd, &tree, sizeof(FIGURE));

        drawTree(tree.locX, tree.locY);
    }
    return;
}

void showAll(int fd, META_DATA meta)
{
    if(meta.numH > 0) { showHouses(fd, meta); }
    if(meta.numP > 0) { showPeople(fd, meta); }
    if(meta.numT > 0) { showTrees(fd, meta); }

    return;
}
 
void initCurses() {
    initscr();
    noecho();
    return;
}

void endCurses() {
    endwin();
    return;
}
