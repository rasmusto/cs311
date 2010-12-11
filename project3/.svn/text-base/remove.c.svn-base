/*
# If I type
remove  [Enter]
on the command line, your remove executable should

    * read a filename from byte 0 of .draw_config
    * open that file and draw all the images at the right positions on the screen.
    * pause to let the user position the curser on the screen and hit [Enter]
    * if the curser is at the very top of a figure, that figure is selected and removed from its linked list. It disappears from the screen and the file's length is shortened by the size of the figure data. Then the remove executable exits.
    * if the curser is not at the top of any figure, the remove executable exits.

# If I type
remove canvas2  [Enter]
on the command line, your remove executable should

    * print out an error message and exit if canvas2 is not an existing file in the current directory.
    * write canvas2 at byte 0 of .draw_config
    * open canvas2 and draw all the images at the right positions on the screen.
    * pause to let the user position the curser on the screen and hit [Enter]
    * if the curser is at the very top of a figure, that figure is selected and removed from its linked list. It disappears from the screen and the file's length is shortened by the size of the figure data. Then the remove executable exits.
    * if the curser is not at the top of any figure, the remove executable exits without removing anything. 
*/

#include "picture.h"

void remove_fig(int location);

void printFigure(FILE * file, FIGURE * fig);
void printMeta_Data(FILE * file, META_DATA * meta_data);

static META_DATA meta_data;

static int x, y;

FILE * beforeRemove;
FILE * afterRemove;;

static char filename[MAX_FILENAME];

static int orig_prev;
static int orig_next;
static int orig_last;
static int orig_last_prev;
static int orig_last_next;


int main(int argc, const char *argv[])
{
    int fd;

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
        initCurses();

        //Open canvas file
        getLock(filename);
        fd = open (filename, O_RDONLY, 0600);

        //read metadata from file
        read (fd, &meta_data, sizeof(META_DATA));

        //print out all figures
        showAll(fd, meta_data);
    }
    userMv();
    getyx(stdscr, y, x);

    if(meta_data.numH > 0 || meta_data.numP > 0 || meta_data.numT > 0)
    {
        int location;
        int exit_flag = 0;
        FIGURE current;

        location = lseek(fd, meta_data.first, SEEK_SET);

        while((location <= meta_data.last) && (exit_flag == 0))
        {
            read (fd, &current, sizeof(FIGURE));

            if (current.locX == x && current.locY == y){
                close(fd);
                removeLock(filename);
                remove_fig(location);
                exit_flag = 1;
            }
            location += sizeof(FIGURE);
        }
    }
    removeLock(filename);

    getLock(filename);
    fd = open (filename, O_RDONLY, 0600);

    //read metadata from file
    lseek(fd, 0, SEEK_SET);
    read (fd, &meta_data, sizeof(META_DATA));

    clear();
    refresh();
    showAll(fd, meta_data);

    close(fd);
    removeLock(filename);

    refresh();
    endCurses();
    return 0;
}

void remove_fig(int location)
{
    int fd;
    static FIGURE fig;
    static FIGURE prev;
    static FIGURE next;
    static FIGURE last;
    static FIGURE last_prev;
    static FIGURE last_next;
    int next_flag = 0;
    int prev_flag = 0;
    int last_next_flag = 0;
    int last_prev_flag = 0;

    beforeRemove = fopen("beforeRemove", "w");
    afterRemove = fopen("afterRemove", "w");

    getLock(filename);
    fd = open (filename, O_RDONLY, 0600);

    /****************************  READ IN FIGURES TO BE CHANGED *******************************/
    
    read(fd, &meta_data, sizeof(FIGURE));
    orig_last = meta_data.last;

    if((meta_data.numH + meta_data.numP + meta_data.numT > 0))
    {
        //read in figure to be removed
        lseek(fd, location, SEEK_SET);
        read(fd, &fig, sizeof(FIGURE));
        orig_next = fig.next;
        orig_prev = fig.prev;

        fprintf(beforeRemove, "fig:\n");
        printFigure(beforeRemove, &fig);

        fprintf(afterRemove, "fig:\n");
        printFigure(afterRemove, &fig);
    }

    if(fig.prev != -1)
    {
        //read in previous figure of same type
        lseek(fd, fig.prev, SEEK_SET);
        read (fd, &prev, sizeof(FIGURE));

        fprintf(beforeRemove, "prev as read:\n");
        printFigure(beforeRemove, &prev);
    }

    if(fig.next != -1)
    {
        //read in next figure of same type
        lseek(fd, fig.next, SEEK_SET);
        read (fd, &next, sizeof(FIGURE));

        fprintf(beforeRemove, "next as read:\n");
        printFigure(beforeRemove, &next);
    }

    if(meta_data.last != -1)
    {
        //read in last figure in the file
        lseek(fd, meta_data.last, SEEK_SET);
        read (fd, &last, sizeof(FIGURE));
        orig_last_next = last.next;
        orig_last_prev = last.prev;

        fprintf(beforeRemove, "last as read:\n");
        printFigure(beforeRemove, &last);

        if(last.prev != -1)
        {
            //read in last_prev
            lseek(fd, last.prev, SEEK_SET);
            read (fd, &last_prev, sizeof(FIGURE));

            fprintf(beforeRemove, "last_prev as read:\n");
            printFigure(beforeRemove, &last_prev);
        }

        if(last.next != -1)
        {
            //read in last_next
            lseek(fd, last.next, SEEK_SET);
            read (fd, &last_next, sizeof(FIGURE));

            fprintf(beforeRemove, "last_next as read:\n");
            printFigure(beforeRemove, &last_next);
        }
    }

    close(fd);
    removeLock(filename);

    fprintf(beforeRemove, "meta_data as read:\n");
    printMeta_Data(beforeRemove, &meta_data);

/************************* CHANGE FIGURES ****************************/
    //update fig.next.prev
    if(fig.next != -1)
    {
        if(fig.prev != meta_data.last)
        {
            next.prev = fig.prev;
            next_flag = 1;
        }
        else
        {
            next.prev = location;
            next_flag = 1;
        }
    }

    //update fig.prev.next
    if(fig.prev != -1)
    {
        if(fig.next != meta_data.last)
        {
            prev.next = fig.next;
            prev_flag = 1;
        }
        else
        {
            prev.next = location;
            prev_flag = 1;
        }
    }

    /************FIX*************/
    //update last_prev.next
    if(meta_data.last != -1 && last.prev != -1 && meta_data.last != location)
    {
        if(location != last.prev)
        {
            last_prev.next = location;
            last_prev_flag = 1;
        }
    }
    /************FIX*************/

    /************FIX*************/
    //update last_next.prev
    if(meta_data.last != -1 && last.next != -1)
    {
        if(location != last.next)
        {
            //last_next.prev = location;
            //last_next_flag = 1;
        }
    }
    /************FIX*************/

/*************************** CHANGE META_DATA  *******************************/

    //update meta_data.num<type>
    switch(fig.type)
    {
        case('H'):
            meta_data.numH--;
            break;
        case('P'):
            meta_data.numP--;
            break;
        case('T'):
            meta_data.numT--;
            break;
        default:
            break;
    }

    //update meta_data.first<type> based on fig
    if((fig.prev == -1) && (location != meta_data.last) && (fig.next != meta_data.last))
    {
        switch(fig.type)
        {
            case('H'):
                meta_data.firstH = fig.next;
                break;
            case('P'):
                meta_data.firstP = fig.next;
                break;
            case('T'):
                meta_data.firstT = fig.next;
                break;
        }
    }

    //update meta_data.first<type> based on fig
    if((fig.prev == -1) && (location != meta_data.last) && (fig.next == meta_data.last))
    {
        switch(fig.type)
        {
            case('H'):
                meta_data.firstH = location;
                break;
            case('P'):
                meta_data.firstP = location;
                break;
            case('T'):
                meta_data.firstT = location;
                break;
        }
    }

    //update meta_data.first<type> based on last
    if(last.prev == -1)
    {
        switch(last.type)
        {
            case('H'):
                if(meta_data.numH > 0){ 
                    if(location != meta_data.last) { meta_data.firstH = location; }
                    else { meta_data.firstH = last.next; }
                }
                else { meta_data.firstH = -1; }
                break;
            case('P'):
                if(meta_data.numP > 0){ 
                    if(location != meta_data.last) { meta_data.firstP = location; }
                    else { meta_data.firstP = last.next; }
                }
                else { meta_data.firstP = -1; }
                break;
            case('T'):
                if(meta_data.numT > 0){ 
                    if(location != meta_data.last) { meta_data.firstT = location; }
                    else { meta_data.firstT = last.next; }
                }
                else { meta_data.firstT = -1; }
                break;
        }
    }

    //update meta_data.last<type> based on fig
    if((fig.next == -1) && (location != meta_data.last))
    {
        switch(fig.type)
        {
            case('H'):
                meta_data.lastH = fig.prev;
                break;
            case('P'):
                meta_data.lastP = fig.prev;
                break;
            case('T'):
                meta_data.lastT = fig.prev;
                break;
        }
    }

    //update meta_data.last<type> based on last
    if(last.next == -1)
    {
        switch(last.type)
        {
            case('H'):
                if(meta_data.numH > 0){ 
                    if(location != meta_data.last) { meta_data.lastH = location; }
                    else { meta_data.lastH = last.prev; }
                }
                break;
            case('P'):
                if(meta_data.numP > 0){ 
                    if(location != meta_data.last) { meta_data.lastP = location; }
                    else { meta_data.lastP = last.prev; }
                }
                break;
            case('T'):
                if(meta_data.numT > 0){ 
                    if(location != meta_data.last) { meta_data.lastT = location; }
                    else { meta_data.lastT = last.prev; }
                }
                else { meta_data.lastT = -1; }
                break;
        }
    }

    //update meta_data
    meta_data.last -= sizeof(FIGURE);

/********************** WRITE TO FILE ***********************/
    getLock(filename);
    fd = open(filename, O_WRONLY, 0600);

    //write meta_data
    write(fd, &meta_data, sizeof(META_DATA));

    close(fd);
    removeLock(filename);

    if(prev_flag == 1)
    {
        getLock(filename);
        fd = open(filename, O_WRONLY, 0600);

        fprintf(afterRemove, "prev as written:\n");
        printFigure(afterRemove, &prev);

        //write fig.prev
        lseek(fd, orig_prev, SEEK_SET);
        write(fd, &prev, sizeof(FIGURE));

        close(fd);
        removeLock(filename);
    }

    if(next_flag == 1)
    {
        getLock(filename);
        fd = open(filename, O_WRONLY, 0600);

        fprintf(afterRemove, "next as written:\n");
        printFigure(afterRemove, &next);

        //write fig.next
        lseek(fd, orig_next, SEEK_SET);
        write(fd, &next, sizeof(FIGURE));

        close(fd);
        removeLock(filename);
    }

    if(meta_data.last != -1)
    {
        getLock(filename);
        fd = open(filename, O_WRONLY, 0600);

        fprintf(afterRemove, "last as written:\n");
        printFigure(afterRemove, &last);

        //write last
        lseek(fd, location, SEEK_SET);
        write(fd, &last, sizeof(FIGURE));

        close(fd);
        removeLock(filename);
            
        if(last_prev_flag == 1)
        {
            getLock(filename);
            fd = open(filename, O_WRONLY, 0600);

            fprintf(afterRemove, "last_prev as written:\n");
            printFigure(afterRemove, &last_prev);

            //write last_prev
            lseek(fd, orig_last_prev, SEEK_SET);
            write(fd, &last_prev, sizeof(FIGURE));

            close(fd);
            removeLock(filename);
        }

        if(last_next_flag == 1)
        {
            getLock(filename);
            fd = open(filename, O_WRONLY, 0600);

            fprintf(afterRemove, "last_next as written:\n");
            printFigure(afterRemove, &last_next);

            //write last_next
            lseek(fd, orig_last_next, SEEK_SET);
            write(fd, &last_next, sizeof(FIGURE));

            close(fd);
            removeLock(filename);
        }

    }

    getLock(filename);
    fd = open(filename, O_WRONLY, 0600);

    //truncate file
    if((meta_data.numH + meta_data.numP + meta_data.numT) > 0)
    {
        ftruncate(fd, meta_data.last + sizeof(FIGURE));
    }
    else
    {
        ftruncate(fd, sizeof(META_DATA));
    }

    fprintf(afterRemove, "meta_data as written:\n");
    printMeta_Data(afterRemove, &meta_data);

    close(fd);
    removeLock(filename);
    system("check2.sh all");

    fclose(beforeRemove);
    fclose(afterRemove);
}

void printFigure(FILE * file, FIGURE * fig)
{
    fprintf(file, "\ttype = %c\n", fig->type);
    fprintf(file, "\tlocX = %d\n", fig->locX);
    fprintf(file, "\tlocY = %d\n", fig->locY);
    fprintf(file, "\tnext = %d\n", fig->next);
    fprintf(file, "\tprev = %d\n", fig->prev);
}

void printMeta_Data(FILE * file, META_DATA * meta_data) 
{
    fprintf(file, "\tfirstH = %d\n", meta_data->firstH);
    fprintf(file, "\tfirstT = %d\n", meta_data->firstT);
    fprintf(file, "\tfirstP = %d\n", meta_data->firstP);
    fprintf(file, "\tlastH = %d\n", meta_data->lastH);
    fprintf(file, "\tlastT = %d\n", meta_data->lastT);
    fprintf(file, "\tlastP = %d\n", meta_data->lastP);
    fprintf(file, "\tlast = %d\n", meta_data->last);
    fprintf(file, "\tnumT = %d\n", meta_data->numT);
    fprintf(file, "\tnumH = %d\n", meta_data->numH);
    fprintf(file, "\tnumP = %d\n", meta_data->numP);
    fprintf(file, "\tfirst = %d\n", meta_data->first);
}
