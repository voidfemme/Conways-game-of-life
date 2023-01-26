#include <ncurses.h>
#include <string>
#include "life.h"

void SettingsMenu();
void PrintMenu(std::string*, int, int);

int main() {
    std::string menu_options[4] = {
        "Welcome to the game of life!",
        "1. Start game",
        "2. Set game settings",
        "3. Quit Game",
    };
    initscr(); // Initialize the ncurses library
    noecho(); // Don't print user input to the screen
    cbreak(); // Disable line buffering
    keypad(stdscr, true); // Enable function keys
    curs_set(0); // Hide the cursor

    int choice;
    int highlight = 0;

    while(1) {
        PrintMenu(menu_options, 4, highlight);

        choice = getch();
        switch(choice) {
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == 4)
                    highlight = 2;
                break;
            case KEY_STAB:
                highlight++;
                if(highlight == 4)
                    highlight = 2;
                break;
            case 10:
                if(highlight == 3) {
                    endwin();
                    return 0;
                } else if(highlight == 2) {
                    refresh();
                    clear();
                    refresh();
                    SettingsMenu();
                    break;
                } else if(highlight == 1) {
                    clear();
                    refresh();
                    SetBoard();
                    break;
                }
            default:
                break;
        }

        refresh();
    }
    endwin();

    return 0;
}

// What if I was to pass the string of options to this function, and then an
// array of commands?
void SettingsMenu() {
    std::string menu_options[3] = {
        "1. Set board size: ",
        "2. Set Number of generations: ",
        "3. Main Menu",
    };
    
    int choice;
    int highlight = 0;

    while(1) {
        clear();
        refresh();
        for(int i=0; i<3; i++) {
            if (i == highlight) {
                attron(A_REVERSE);
            }
            mvprintw(i + 1, 1, menu_options[i].c_str());
            attroff(A_REVERSE);
        }
        
        choice = getch();
        switch(choice) {
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 2;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == 3)
                    highlight = 0;
                break;
            case 10:
                if(highlight == 2) {
                    clear();
                    refresh();
                    return;
                }
        }
    }
    
}

void PrintMenu(std::string options[], int number_of_options, int highlight) {
    for(int i = 0; i < number_of_options; i++) { // loop through menu_options
        if(i == highlight) // starts at 0, and then gets changed by the user's direction choice
            attron(A_REVERSE);
        mvprintw(i + 1, 1, options[i].c_str()); // we have to pass a .c_str() version 
        attroff(A_REVERSE);
    }
}
