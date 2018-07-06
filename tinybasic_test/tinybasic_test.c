#include <stdio.h>
#include <ncurses.h>

#include "tinybasic03.c"

#define ESC 27

int main(int argc, char **args) {
    initscr();
    kbhit();
    
    /* cbreak(); */
    /* noecho(); */
    scrollok(stdscr, TRUE);

    init();
    setup();
    /* for (int i = 0; i < 10000000; i++) { */
    while (loop()) {
        if (kbhit()) {
            getln_addch(getch());
        }
        
        fflush(stdout);
    }

    endwin();
    
    return 0;
}

int kbhit(void)
{
    nodelay(stdscr, TRUE);
    int ch = getch();
    nodelay(stdscr, FALSE);

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

unsigned char breakcheck(void) {
    if (kbhit())
        return getch() == ESC;
    else
        return 0;
}
void outchar(unsigned char c) {
    putchar(c);
}


bool getln_started = false;
bool getln_ready = false;
bool getln_isstarted(void) {
    return getln_started;
}
bool getln_isready(void) {
    return getln_ready;
}

void getln_start(char prompt) {
    outchar(prompt);
    txtpos = program_end+sizeof(LINENUM);
    getln_started = true;
    getln_ready = false;
}
void getln_consume(void) {
    getln_started = false;
}
void getln_addch(int c) {
    switch(c) {
    case NL:
        line_terminator();
        // Terminate all strings with a NL
        txtpos[0] = NL;

        getln_ready = true;
        return;
    case CTRLH:
        if(txtpos == program_end)
            break;
        txtpos--;
        printmsg(backspacemsg);
        break;
    default:
        // We need to leave at least one space to allow us to shuffle the line into order
        if(txtpos == variables_begin-2)
            outchar(BELL);
        else
        {
            txtpos[0] = c;
            txtpos++;
        }
    }
}
// todo handle BYE

