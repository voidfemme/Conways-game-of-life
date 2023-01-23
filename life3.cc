#include <iostream>
#include <iomanip>
#include <unistd.h>

const int FIELD_LENGTH = 20;
const int FIELD_SIZE = FIELD_LENGTH * FIELD_LENGTH;

void FormatFunction();
void PrintBoard(bool*);
char PrintCell(bool);
int NumNeighbors(bool*, int);

int main()
{
    // Try to keep every action that happens to the board in the main function.
    // Everything hinges around this structure.
    bool life_board[FIELD_SIZE];
    int cell_x, cell_y = 0;
    int simulation_steps = 0;

    // initialize all the values to false.
    for(int i=0; i<FIELD_SIZE; i++)
    {
        life_board[i] = false;
    }
    FormatFunction(); 

    // Get initial state of the board from the user
    while(cell_x != -1)
    {
        std::cout << "x, y: ";
        std::cin >> cell_x;
        if(cell_x == -1) { continue; }
        std::cin >> cell_y;
        if(cell_x * FIELD_LENGTH + cell_y >= 0 && cell_x * FIELD_LENGTH + cell_y <= FIELD_SIZE)
        {
            life_board[cell_y * FIELD_LENGTH + cell_x] = true;
            FormatFunction();
            PrintBoard(life_board);
            FormatFunction();
        }
        else {
            {
                std::cout << "Out of bounds!\n";
            }
        }
    }

    std::cout << "How many generations to simulate: ";
    std::cin >> simulation_steps;

    for(int i=0; i<simulation_steps; i++)
    {
        // Analyse and save the new state of the board
        bool next_board_state[FIELD_SIZE];
        for(int i=0; i<FIELD_SIZE; i++)
        {
            next_board_state[i] = 0;
        }

        for(int i=0; i<FIELD_SIZE; i++)
        {

            // apply rules
            int num_neighbors = NumNeighbors(life_board, i);
            
            if(life_board[i])
            {
                if(num_neighbors < 2)
                    next_board_state[i] = false;
                else if(num_neighbors > 3)
                    next_board_state[i] = false;
                else if(num_neighbors == 2 || num_neighbors == 3)
                    next_board_state[i] = true;
            }
            if(!life_board[i])
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
            life_board[i] = next_board_state[i];
        }
        PrintBoard(life_board);
        
    }

    std::cout << std::endl;

    return 0;
}

void FormatFunction()
{
    std::cout << std::setw(32) << std::setfill('-') << " " << std::endl;
}

void PrintBoard(bool life_board[])
{
    FormatFunction();
    for(int i=0; i<FIELD_LENGTH; i++)
    {
        for(int j=0; j<FIELD_LENGTH; j++){
            std::cout << PrintCell(life_board[i * FIELD_LENGTH + j]) << " ";
        }
        std::cout << "|\n";
    }
    FormatFunction();
    std::cout.flush();
    sleep(1);
}

char PrintCell(bool cell)
{
    if(cell) { 
        return 'X';
    }
    else
    {
        return '.';
    }
}

int NumNeighbors(bool life_board[], int cell_index)
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
            if(life_board[(cell_index + i * FIELD_LENGTH + j + FIELD_SIZE) % FIELD_SIZE])
            {
                num_neighbors++;
            }
        }
    }

    return num_neighbors;
}
