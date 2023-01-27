#include "life.h"

void printField(bool*);
char PrintCell(bool);
int NumNeighbors(bool*, int);

int RunSimulation(bool* field) {

    printField(field);
    // Try to keep every action that happens to the field in the main function.
    // Everything hinges around this structure.
    int simulation_steps = 20;
    int generation = 1;

    for(int i=0; i<simulation_steps; i++) {
        clear();
        printField(field);
        refresh();
        mvprintw(FIELD_LENGTH + 2, 1, "Generation: %i", generation);
        generation++;

        // Analyse and save the new state of the board
        bool next_board_state[FIELD_SIZE];
        for(int i=0; i<FIELD_SIZE; i++) {
            next_board_state[i] = 0;
        }

        for(int i=0; i<FIELD_SIZE; i++) {

            // apply rules
            int num_neighbors = NumNeighbors(field, i);
            
            if(field[i])
            {
                if(num_neighbors < 2)
                    next_board_state[i] = false;
                else if(num_neighbors > 3)
                    next_board_state[i] = false;
                else if(num_neighbors == 2 || num_neighbors == 3)
                    next_board_state[i] = true;
            }
            if(!field[i])
            {
                if(num_neighbors == 3)
                    next_board_state[i] = true;
                else if(num_neighbors < 3)
                    next_board_state[i] = false;
                else if(num_neighbors > 3)
                    next_board_state[i] = false;

            }
        }
        // update the current state to the next generation
        for(int i=0; i<FIELD_SIZE; i++)
        {
            field[i] = next_board_state[i];
        }
    }
    return 0;
}

void printField(bool field[])
{
    for(int i=0; i<FIELD_LENGTH; i++)
    {
        for(int j=0; j<FIELD_LENGTH; j++){
            if(i >=0 && i < FIELD_LENGTH && j >= 0 && j < FIELD_LENGTH) {
                // Print the grid.
                if(field[i * FIELD_LENGTH + j]) {
                    mvaddch(j,i,'#');
                } else {
                    mvaddch(j,i,' ');
                }
            }
        }
    }
    Timer();
    refresh();
}


int NumNeighbors(bool field[], int cell_index)
{
    int num_neighbors = 0;
    // create an array with possible values.
    for(int i=-1; i<=1; i++)
    {
        for(int j=-1; j<=1; j++)
        {
            // skip the cell itself since it cannot be its own
            if(i == 0 && j == 0)
            {
                continue;
            }
            if(field[(cell_index + i * FIELD_LENGTH + j + FIELD_SIZE) % FIELD_SIZE])
            {
                num_neighbors++;
            }
        }
    }

    return num_neighbors;
}

void Timer() {
    std::chrono::milliseconds quarter_second = std::chrono::milliseconds(250);
    std::this_thread::sleep_for(quarter_second);
}
