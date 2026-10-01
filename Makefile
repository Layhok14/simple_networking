TEST_DIR = ./bin/test
DEBUG_DIR = .bin/debug
BUILD_DIR = .bin/build

ALGO_TEST_DIR = $(TEST_DIR)/algo
ALGO_DEBUG_DIR = $(DEBUG_DIR)/algo
NETWORK_TEST_DIR = $(TEST_DIR)/network
NETWORK_DEBUG_DIR = $(DEBUG_DIR)/network

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
HEADER = $(wildcard inc/*.h)

BUILD_FLAGS = -Wall -Wextra -pedantic
DEBUG_FLAGS = $(BUILD_FLAGS) -ggdb -O0

# main directories checking
$(TEST_DIR) $(DEBUG_DIR) $(BUILD_DIR):
	mkdir -p $@

default: gcc -o $(BUILD_DIR) -I./inc
clean: 
		rm -f obj/*.o
		rm -rf bin/**

test_algo:
	mkdir -p $(ALGO_TEST_DIR)
	gcc -o $(ALGO_TEST_DIR) -I./inc $(SRC) $(BUILD_FLAGS)

debug_algo:
	mkdir -p $(ALGO_DEBUG_DIR)
	gcc -o $(ALGO_DEBUG_DIR) -I./inc $(SRC) $(DEBUG_FLAGS)

test_connection:
	mkdir -p $(NETWORK_TEST_DIR)
	gcc -o $(NETWORK_TEST_DIR)/client src/client.c -I./inc $(BUILD_FLAGS)
	gcc -o $(NETWORK_TEST_DIR)/server src/server.c -I./inc $(BUILD_FLAGS)

debug_connection:
	mkdir -p $(NETWORK_DEBUG_DIR)
	gcc -o $(NETWORK_TEST_DIR)/client src/client.c  -I./inc $(DEBUG_FLAGS)
	gcc -o $(NETWORK_DEBUG_DIR)/server src/server.c  -I./inc $(DEBUG_FLAGS)
