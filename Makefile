CC = g++
CFLAGS = -Wall -g -lncurses

OBJECTS = main.o set_field.o run_simulation.o 

life: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o life.out

main.o: main.cc
	$(CC) $(CFLAGS) -c main.cc

print_grid.o: set_field.cc
	$(CC) $(CFLAGS) -c set_field.cc

run_simulation.o: run_simulation.cc
	$(CC) $(CFLAGS) -c run_simulation.cc

clean:
	rm -f *.o $(OBJECTS)
