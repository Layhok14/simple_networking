TEST = ./bin/test
DEBUG = ./bin/debug
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
HEADER = $(wildcard inc/*.h)
default: $(TARGET)
clean: 
		rm -f obj/*.o
		rm -rf bin/*
build:
	gcc -o $(TEST) -I./inc src/*.c -Wall -Wextra -ggdb -pedantic
debug:
	gcc -o $(DEBUG) -I./inc src/*.c -Wall -Wextra -ggdb -pedantic -g -O0
