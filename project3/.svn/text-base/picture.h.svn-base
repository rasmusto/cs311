#include <curses.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct{
   int firstH; // byte offset where first house figure is stored in the file
   int firstT; // byte offset where first tree figure is stored in the file
   int firstP; // byte offset where first person figure is stored in the file
   int lastH; // byte offset where last house figure is stored in the file
   int lastT; // byte offset where last tree figure is stored in the file
   int lastP; // byte offset where last person figure is stored in the file
   int last; // byte offset where the last figure is stored in the file
   int numT; // how many tree figures are currently in the file
   int numH; // how many house figures are currently in the file
   int numP; // how many person figures are currently in the file
   int first; // byte offset where the first figure is stored in the file
}META_DATA;

typedef struct{
   char type; // a 'T' or a 'H' or a 'P'
   char a,b,c; // filler so that int locX appears in a certain place
   int locX; // x location on the screen where the top of the figure is drawn
   int locY; // y location on the screen where the top of the figure is drawn
   int next; // byte offset in the file of the next figure OF THIS TYPE
   int prev; // byte offset in the file of the previous figure OF THIS TYPE
   int spacer1, spacer2, spacer3; // fillers so that this struct takes 32 bytes.
}FIGURE;

#define META_LOC 0
#define MAX_FILENAME 128
#define FIRST_FIGURE 128
#define NA (-1) 

//your function declarations here 

int drawHouse(int x, int y);
int drawPerson(int x, int y);
int drawTree(int x, int y);
void userMv();
void showTrees(int fd, META_DATA meta);
void showPeople(int fd, META_DATA meta);
void showHouses(int fd, META_DATA meta);
void showAll(int fd, META_DATA meta);
void initCurses();
void endCurses();
void getLock(char filename[MAX_FILENAME]);
void removeLock(char filename[MAX_FILENAME]);
