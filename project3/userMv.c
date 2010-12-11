#include "picture.h"

void userMv(void) {
   int c, x, y;
   keypad(stdscr, TRUE);
   getyx(stdscr, y, x);
   noecho();
   do {
      c = getch();
      if (c==KEY_LEFT || c==106) x--;
      else if(c==KEY_RIGHT || c==108) x++;
      else if(c==KEY_UP || c==105) y--;
      else if(c==KEY_DOWN || c==107) y++;
      move(y,x);
      refresh();
   }while(c!=10);
   echo();
}
