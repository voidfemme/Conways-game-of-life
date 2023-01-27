#include <ncurses.h>
#include <unistd.h>
#include <string>
#include <chrono>
#include <thread>

#define FIELD_LENGTH 40
#define FIELD_SIZE 1600

void PrintBoard(bool*);
char PrintCell(bool);
int NumNeighbors(bool*, int);
int RunSimulation(bool*);
int SetField();
void Timer();
