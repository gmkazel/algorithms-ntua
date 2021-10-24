OBJS	= bazaar.o
SOURCE	= bazaar.cpp
HEADER	=
OUT	= bazaar
CC	 = g++
FLAGS	 = -O3 -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

bazaar.o: bazaar.cpp
	$(CC) $(FLAGS) bazaar.cpp


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
	python3 ~/Documents/check.py ./$(OUT) lab02/bazaar/input{}.txt lab02/bazaar/output{}.txt 20

bench: $(OUT)
	hyperfine -m 19 --parameter-scan testcase 0 19 "./$(OUT) <  lab02/bazaar/input{testcase}.txt"
