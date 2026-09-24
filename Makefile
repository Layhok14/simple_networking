TEST = ./bin/test
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
HEADER = $(wildcard inc/*.h)

default: $(TARGET)
clean: 
		rm -f obj/*.o
		rm -rf bin/*
build:
	gcc -o $(TEST) -I./inc src/*.c -Wall
