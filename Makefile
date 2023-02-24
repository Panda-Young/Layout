# *
# Description: Simple Makefile.
# version: 0.1.0
# Author: Panda-Young
# Date: 2022-08-14 01:06:24
# Copyright (c) 2022 by Panda-Young, All Rights Reserved.
# *

SRC = $(wildcard src/*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
CPPFLAGS = "-I./inc"

all : main $(OBJ)
	mkdir -p out/build
	mv $(OBJ) out/build/
	mv *.exe out

main : $(OBJ)
	gcc $(OBJ) -o main

%.o : %.c
	gcc -c $^ -o $@  $(CPPFLAGS)

.PHONY:clean debug

clean:
	-rm $(OBJ)
	-rm -rf out
	clear

debug:
	@echo $(SRC)
	@echo $(OBJ)
