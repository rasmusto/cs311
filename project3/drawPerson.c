#include "picture.h"
int drawPerson(int x, int y) {

   move(y, x);
   addstr ("_");
   move(y+1, x-1);
   addstr ("(O)");
   move(y+2, x-1);
   addstr ("/|\\");
   move(y+3, x-1);
   addstr ("\\|/");
   move(y+4, x-1);
   addstr ("/ \\");
   move(y+5, x-2);
   addstr ("/   \\"); // 3 spaces here
   move(0, 0);
   refresh();

   return 0;
}
