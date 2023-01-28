#include <ncurses.h>
#include <string>
#include "life.h"

void SettingsMenu();
void PrintMenu(std::string*, int, int);
int SetFieldSize();
int SetNumberOfGenerations();
int SetSimSpeed();


int main() {
    int number_of_options = 4;
    std::string menu_options[number_of_options] = {
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
    int highlight_position = 1;

    while(1) {
        PrintMenu(menu_options, number_of_options, highlight_position);

        choice = getch();
        switch(choice) {
            case KEY_UP:
                highlight_position--;
                if(highlight_position == 0)
                    highlight_position = 4;
                break;
            case KEY_DOWN:
                highlight_position++;
                if(highlight_position == 4)
                    highlight_position = 1;
                break;
            case KEY_STAB:
                highlight_position++;
                if(highlight_position == 4)
                    highlight_position = 2;
                break;
            case 10:
                if(highlight_position == 3) {
                    endwin();
                    return 0;
                } else if(highlight_position == 2) {
                    refresh();
                    clear();
                    refresh();
                    SettingsMenu();
                    break;
                } else if(highlight_position == 1) {
                    clear();
                    refresh();
                    SetField();
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
    int number_of_options = 5;
    std::string menu_options[number_of_options] = {
        "Settings Menu",
        "1. Set field size: ",
        "2. Set Number of generations: ",
        "3. Set simulation speed: ",
        "4. Main Menu",
    };
    
    int choice;
    int highlight_position = 1;
    int sim_speed = 0;
    int number_of_generations = 30;
    int field_size = 0;

    while(1) {
        clear();
        refresh();
        PrintMenu(menu_options, number_of_options, highlight_position);
        
        choice = getch();
        switch(choice) {
            case KEY_UP:
                highlight_position--;
                if(highlight_position == 0)
                    highlight_position = number_of_options - 1;
                break;
            case KEY_DOWN:
                highlight_position++;
                if(highlight_position == number_of_options)
                    highlight_position = 1;
                break;
            case 10:
                switch(highlight_position) {
                    case 1:
                        clear();
                        refresh();
                        SetFieldSize();
                        break;
                    case 2: 
                        clear();
                        refresh();
                        number_of_generations = SetNumberOfGenerations();
                        break;
                    case 3: 
                        clear();
                        refresh();
                        sim_speed = SetSimSpeed();
                        break;
                    case 4:
                        clear();
                        refresh();
                        return;
                    
                }
        }
    }
}

int SetFieldSize() {
    char str[80];
    mvprintw(1, 1, "Set field size");
    mvprintw(2, 1, "Enter the number of rows: ");
    echo();
    getstr(str);
    noecho();
    mvprintw(4, 1, "You entered %s", str);
    getch();
    return 0;
}

int SetNumberOfGenerations() {
    mvprintw(2, 1, "Enter the number of generations: ");
    getch();
    return 30;
}

int SetSimSpeed() {
    return 0;
}

void PrintMenu(std::string options[], int number_of_options, int highlight_position) {
    // loop through menu_options
    for(int i = 0; i < number_of_options; i++) { 
        if(i == highlight_position)
            attron(A_REVERSE);
        mvprintw(i + 1, 1, options[i].c_str());
        attroff(A_REVERSE);
    }
}
