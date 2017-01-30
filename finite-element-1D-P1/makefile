INCLUDE = -Iinclude
LIB = 
CC=g++
TESTFLAGS= -ggdb -Wno-write-strings
FLAGS= -lumfpack
NAME=main


all: main testR1

main: src/main.c src/simple_dim.c
	$(CC) src/main.c src/simple_dim.c $(INCLUDE) $(LIB) $(FLAGS) -o "bin/"$(NAME)

testR1: src/simple_dim_test.c src/simple_dim.c
	$(CC) src/simple_dim_test.c src/simple_dim.c $(INCLUDE) $(LIB) $(TESTFLAGS) $(FLAGS) -o "test/R1_test" 

testmeshes: src/meshes_test.c src/meshes_seg.c src/simple_dim.c
	$(CC) src/meshes_test.c src/meshes_seg.c src/simple_dim.c $(INCLUDE) $(LIB) $(TESTFLAGS) $(FLAGS) -o "test/meshes_test"

clean:
	rm bin/main
	rm test/*
