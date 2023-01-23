#include <ncurses.h>
#include <string>

const int FIELD_LENGTH = 20;
const int FIELD_SIZE = FIELD_LENGTH * FIELD_LENGTH;

// define a "highlight" object, with an x value and a y value inside of it, so that I can write
//  very readable code
class GridPosition
{
    public:
        int x_position = 0;
        int y_position = 0;
        int FieldPosition();
};

int GridPosition::FieldPosition() {
    return (x_position + y_position) * FIELD_LENGTH;
}

int main() {

    int choice;
    GridPosition highlight;

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
                    if(i == highlight.x_position && j == highlight.y_position) {
                        attron(A_REVERSE);
                    } 
                    if(field[FIELD_LENGTH * j + i] == true) {
                        mvaddch(j,i, '#');
                    } else {
                        mvaddch(j,i, ' ');
                    }
                    attroff(A_REVERSE);
                }
            }
        }
        mvprintw(FIELD_LENGTH + 2, 1, "x: %i", highlight.x_position);
        mvprintw(FIELD_LENGTH + 3, 1, "y: %i", highlight.y_position);
        mvprintw(FIELD_LENGTH + 4, 1, "1-d address: %i", highlight.FieldPosition());

        choice = getch();
        switch (choice) {
            case KEY_UP:
                if(highlight.y_position > 0) {
                    highlight.y_position--;
                }
                break;
            case KEY_DOWN:
                if(highlight.y_position < FIELD_LENGTH - 1) {
                    highlight.y_position++;
                }
                break;
            case KEY_LEFT:
                if(highlight.x_position > 0) {
                    highlight.x_position--;
                }
                break;
            case KEY_RIGHT:
                if(highlight.x_position < FIELD_LENGTH - 1) {
                    highlight.x_position++;
                }
                break;
/*            case 10:
                RunSimulation(field);
                break; */
            case ' ':
                field[highlight.FieldPosition()] = true;
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
