#sample Makefile

SRC = $(wildcard src/*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

all : main $(OBJ)
	mkdir build out
	mv $(OBJ) build
	mv *.exe out

main : $(OBJ)
	gcc $(OBJ) -o main

%.o : %.c
	gcc -c $^ -o $@

.PHONY:clean debug

clean:
	-rm -rf build out

debug:
	@echo $(SRC)
	@echo $(OBJ)