#include <iostream> 
#include <iomanip>

const int GRID_WIDTH = 40;
const int GRID_HEIGHT = 40;
const int GRID_SIZE = GRID_WIDTH * GRID_HEIGHT;

void PrintField(bool*);
char PrintCell(bool);
int NumNeighbors(bool*, int);

int main() {
    bool field[GRID_SIZE];
    int cell_x, cell_y = 0;
    int simulation_steps = 0;

    for(int i=0; i<GRID_SIZE; i++) {
        field[i] = false;
    }

    // User Input.
    while (cell_x != -1) {
        std::cout << "x y: ";
        std::cin >> cell_x;
        if (cell_x == -1) { continue; }
        std::cin >> cell_y;
        if(cell_x * GRID_WIDTH + cell_x >= 0 && cell_y * GRID_WIDTH + cell_x <= GRID_SIZE) {
            field[cell_x * GRID_WIDTH + cell_y] = true;
            PrintField(field);
        } else {
            std::cout << "Out of bounds.\n";
        }
    }   

    std::cout << "How many generations: ";
    std::cin >> simulation_steps;
    
    // Start the game loop, iterating over every cell.
    for(int i=0; i<GRID_SIZE; i++) {
        bool next_field_state[GRID_SIZE];

        for(int i=0; i<GRID_SIZE; i++) {
            next_field_state[i] = 0;
        }

        for(int i=0; i<GRID_SIZE; i++) {
            int num_neighbors = NumNeighbors(field, i);

            // apply rules according to the number of neighbors.
            if(field[i]) {
                if(num_neighbors < 2) {
                    next_field_state[i] = false;
                } else if (num_neighbors > 3) {
                    next_field_state[i] = false;
                } else if(num_neighbors == 2 || num_neighbors == 3) {
                    next_field_state[i] == true;
                }
            }

            if(!field[i]) {
                if(num_neighbors == 3)
                    next_field_state[i] = true;
                else if(num_neighbors < 3)
                   next_field_state[i] = false;
                else if(num_neighbors > 3)
                    next_field_state[i] = false;
            }
        }

        // update the current state of the field to the next generation.
        for(int i=0; i<GRID_SIZE; i++) {
            field[i] = next_field_state[i];
        }
        PrintField(field);
    }

    std::cout << std::endl;
    return 0;
}

void PrintField(bool field[]) {
    std::cout << std::setw(GRID_WIDTH) << std::setfill('-') << " " << std::endl;

    for(int i=0; i<GRID_WIDTH; i++) {
        for(int j=0; j<GRID_HEIGHT; j++) {
            std::cout << PrintCell(field[j * GRID_WIDTH + i]) << " ";
        }
        std::cout << "|\n";
    }
    std::cout << std::setw(GRID_WIDTH) << std::setfill('-') << " " << std::endl;
}

char PrintCell(bool cell) {
    if(cell) {
        return '#';
    } else {
        return ' ';
    }
}

int NumNeighbors(bool field[], int cell_index) {
    int num_neighbors = 0;

    // check the cells around the cell_index
    for(int i=-1; i<=1; i++) {
        for(int j=-1; j<=1; j++) {
            // skip the cell itself since it is not its own neighbor 
            if(i == 0 && j == 0) {
                continue;
            }
            if(field[(cell_index + i * GRID_WIDTH + j + GRID_SIZE) % GRID_SIZE]) {
                num_neighbors++;
            }
        }
    }
    return num_neighbors;
}
