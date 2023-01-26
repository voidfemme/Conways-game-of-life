CC = g++
CFLAGS = -Wall -g -lncurses

OBJECTS = main.o print_grid.o run_simulation.o 

life: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o life

main.o: main.cc
	$(CC) $(CFLAGS) -c main.cc

print_grid.o: print_grid.cc
	$(CC) $(CFLAGS) -c print_grid.cc

run_simulation.o: run_simulation.cc
	$(CC) $(CFLAGS) -c run_simulation.cc

clean:
	rm -f $(OBJECTS) life
