CC = gcc
CFLAGS = -O2
LFLAGS = -s
DIRS = obj bin
PROGRAM = bin/csv2flat
OBJECTS = obj/main.o obj/csv.o
INCLUDES = src/csv.h

$(shell mkdir -p $(DIRS))

obj/%.o: src/%.c $(INCLUDES)
	$(CC) -c $< -o $@ $(CFLAGS)

$(PROGRAM): $(OBJECTS)
	$(CC) $^ -o $@ $(LFLAGS)

.PHONY : clean
clean:
	$(RM) $(PROGRAM) $(OBJECTS)
