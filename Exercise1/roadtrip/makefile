OBJS	= roadtrip.o
SOURCE	= roadtrip.cpp
HEADER	=
OUT	= roadtrip
CC	 = g++
FLAGS	 = -g3 -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

roadtrip.o: roadtrip.cpp
	$(CC) $(FLAGS) roadtrip.cpp


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
