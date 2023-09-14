OBJS	= threads.o shared_functions.o
SOURCE	= threads.c shared_functions.c
HEADER	= shared_functions.h
OUT	= threads.o
CC	 = gcc
FLAGS	 = -g -c -Wall -pedantic -pthread
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(SOURCE) -o $(OUT) $(LFLAGS)

threads.o: threads.c
	$(CC) $(FLAGS) threads.c 

shared_functions.o: shared_functions.c
	$(CC) $(FLAGS) shared_functions.c 


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)