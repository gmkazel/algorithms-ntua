OBJS	= traintrips.o
SOURCE	= traintrips.cpp
HEADER	=
OUT	= traintrips
CC	 = g++
FLAGS	 = -g3 -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

traintrips.o: traintrips.cpp
	$(CC) $(FLAGS) traintrips.cpp


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
	python3 ~/Documents/check.py ./$(OUT) lab03/traintrips/input{}.txt lab03/traintrips/output{}.txt 21

bench: $(OUT)
	hyperfine -m 20 --parameter-scan testcase 1 20 "./$(OUT) <  lab03/traintrips/input{testcase}.txt"
