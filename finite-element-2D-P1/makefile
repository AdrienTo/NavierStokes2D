INCLUDE = -Iinclude
LIB = 
CC=g++
TESTFLAGS= -ggdb -Wno-write-strings
FLAGS= -lumfpack
NAME=main


all: main testR2

main: src/main.c src/double_dim.c
	$(CC) src/main.c src/double_dim.c $(INCLUDE) $(LIB) $(FLAGS) -o "bin/"$(NAME)

testR2: src/double_dim_test.c src/double_dim.c
	$(CC) src/double_dim_test.c src/double_dim.c $(INCLUDE) $(LIB) $(TESTFLAGS) $(FLAGS) -o "test/R2_test" 

testmeshes: src/meshes_test.c src/meshes_tri.c src/double_dim.c
	$(CC) src/meshes_test.c src/meshes_tri.c src/double_dim.c $(INCLUDE) $(LIB) $(TESTFLAGS) $(FLAGS) -o "test/meshes_test"

clean:
	rm bin/main
	rm test/*
