#sample Makefile

SRC = $(wildcard src/*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
CPPFLAGS = "-I./inc"

all : main $(OBJ)
	mkdir -p build/out
	mv $(OBJ) build
	mv *.exe build/out

main : $(OBJ)
	gcc $(OBJ) -o main

%.o : %.c
	gcc -c $^ -o $@  $(CPPFLAGS)

.PHONY:clean debug

clean:
	-rm -rf build
	clear

debug:
	@echo $(SRC)
	@echo $(OBJ)