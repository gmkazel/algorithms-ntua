OBJS	= chem.o
SOURCE	= chem.cpp
HEADER	=
OUT	= chem
CC	 = g++
FLAGS	 = -O3 -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

chem.o: chem.cpp
	$(CC) $(FLAGS) chem.cpp


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
	python3 ~/Documents/check.py ./$(OUT) lab02/chem/input{}.txt lab02/chem/output{}.txt 21

bench: $(OUT)
	hyperfine -m 20 --parameter-scan testcase 1 20 "./$(OUT) <  lab02/chem/input{testcase}.txt"
