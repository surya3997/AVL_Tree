CC = g++

OUTPUT = AVL_TREE

all:
	$(CC) main.cpp functions.cpp -o $(OUTPUT)
	./$(OUTPUT)
