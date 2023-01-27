#include <ncurses.h>
#include <unistd.h>
#include <string>
#include <chrono>
#include <thread>

#define FIELD_LENGTH 30
#define FIELD_SIZE 900

void PrintBoard(bool*);
char PrintCell(bool);
int NumNeighbors(bool*, int);
int RunSimulation(bool*);
int SetField();
void Timer();
