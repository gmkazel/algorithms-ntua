OBJS	= teleports.o
SOURCE	= teleports.cpp
HEADER	=
OUT	= teleports
CC	 = g++
FLAGS	 = -g3 -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

teleports.o: teleports.cpp
	$(CC) $(FLAGS) teleports.cpp


clean:
	rm -f $(OBJS) $(OUT)

# run: $(OUT) $(file)
# 	./$(OUT) << $(file)

debug: $(OUT)
	valgrind $(OUT)

valgrind: $(OUT)
	valgrind $(OUT)

valgrind_leakcheck: $(OUT)
	valgrind --leak-check=full $(OUT)

valgrind_extreme: $(OUT)
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes $(OUT)

check: $(OUT)
	python3 ~/Documents/check.py ./$(OUT) lab01/teleports/input{}.txt lab01/teleports/output{}.txt 29
