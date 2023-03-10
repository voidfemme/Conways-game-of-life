#include <ncurses.h>
#include <string>
#include "life.h"

// define a "highlight_position" object, with an x value and a y value inside of it, so that I can write
//  very readable code
class GridPosition
{
    public:
        int x_position = 0;
        int y_position = 0;
        int FieldPosition();
};

int GridPosition::FieldPosition() {
    return x_position + y_position * FIELD_LENGTH;
}

int SetField() {

    int choice;
    int generation = 1;
    GridPosition highlight_position;

//  1. a list structure of menu items
    bool field[FIELD_SIZE];
    // Use this later in order to hand off to the main simulation to proceed to process it.
    for(int i=0; i<FIELD_SIZE; i++) {
        field[i] = false;
    }

/*  2. int choice to store the character entered by the user.
 *  (in this case, up, down, left, or right) */
    while(1) { 
 
//  3. A loop to display the grid.
        for(int i=0; i<FIELD_LENGTH; i++) {
            for(int j=0; j<FIELD_LENGTH; j++) {
                if(i >= 0 && i < FIELD_LENGTH && j >= 0 && j < FIELD_LENGTH) {
                    // Print the grid. 
                    if(i == highlight_position.x_position && j == highlight_position.y_position) {
                        attron(A_REVERSE);
                    } 
                    if(field[FIELD_LENGTH * j + i]) {
                        mvaddch(j,i * 2, '#');
                    } else {
                        mvaddch(j,i * 2, ' ');
                    }
                    attroff(A_REVERSE);
                }
            }
        }
        mvprintw(FIELD_LENGTH + 1, 1, "Generation: %i", generation);
        mvprintw(FIELD_LENGTH + 2, 1, "x: %i", highlight_position.x_position);
        mvprintw(FIELD_LENGTH + 3, 1, "y: %i", highlight_position.y_position);
        mvprintw(FIELD_LENGTH + 4, 1, "1-d address: %i", highlight_position.FieldPosition());
        mvprintw(FIELD_LENGTH + 5, 1, "arrow keys to move, <enter> to start the sim, \"q\" to return to the main menu.");

        choice = getch();
        switch (choice) {
            case KEY_UP:
                highlight_position.y_position--;
                highlight_position.y_position = (highlight_position.y_position + FIELD_LENGTH) % FIELD_LENGTH;
                break;
            case KEY_DOWN:
                highlight_position.y_position++;
                highlight_position.y_position = (highlight_position.y_position + FIELD_LENGTH) % FIELD_LENGTH;
                break;
            case KEY_LEFT:
                highlight_position.x_position--;
                highlight_position.x_position = (highlight_position.x_position + FIELD_LENGTH) % FIELD_LENGTH;
                break;
            case KEY_RIGHT:
                highlight_position.x_position++;
                highlight_position.x_position = (highlight_position.x_position + FIELD_LENGTH) % FIELD_LENGTH;
                break;
            case 10:
                clear();
                refresh();
                RunSimulation(field, generation);
                generation--;
                clear();
                refresh();
                break;
            case ' ':
                if(field[highlight_position.FieldPosition()]) {
                    field[highlight_position.FieldPosition()] = false;
                } else {
                    field[highlight_position.FieldPosition()] = true;
                }
                break;
            case 'q':
                clear();
                refresh();
                return 0;
            default:
                break;
        }
    }

    getch();
    endwin();

    return 0;
}
