INCLUDE = -Iinclude
LIB = 
CC=g++
TESTFLAGS= -ggdb -Wno-write-strings
FLAGS= -lumfpack
NAME=main


all: main testR2

main: src/main.c src/double_dim.c src/mesh_2D.c src/var_problem.c src/triangle.c
	$(CC) src/main.c src/double_dim.c src/mesh_2D.c src/var_problem.c src/triangle.c $(INCLUDE) $(LIB) $(FLAGS) -o "bin/"$(NAME)

testR2: src/test/double_dim_test.c src/double_dim.c
	$(CC) src/test/double_dim_test.c src/double_dim.c $(INCLUDE) $(LIB) $(TESTFLAGS) $(FLAGS) -o "test/R2_test" 

testmeshes: src/test/meshes_test.c src/mesh_2D.c src/var_problem.c src/triangle.c src/double_dim.c
	$(CC) src/test/meshes_test.c src/mesh_2D.c src/var_problem.c src/triangle.c src/double_dim.c $(INCLUDE) $(LIB) $(TESTFLAGS) $(FLAGS) -o "test/meshes_test"

clean:
	rm bin/main
	rm test/*
