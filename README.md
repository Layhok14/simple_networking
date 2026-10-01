# Networking in C

## 1. Introduction
A simple project for learning how networking works. The C implementation is to brush up memory handling and to improve the style of declarative programming style.

## 2. Description
The project is divided into 2 phases:
- Phase 1: Implementation of a kv_table or a hash table.
- Phase 2: A simple networking implementation of HTTP server.

### Phase 1: Hash Table implementation.
For simplicity, the project will only implement a hash table using the open addressing approach with linear probing. Refer to [document file](./documents.md) for further details. It is just a simple CRUD operation of hash table.
 
### Phase 2: HTTP Server implementation.
This phase is not implemented nor planned yet. Further details will be provided in the future.

## 3. Quick Start
### Prerequisites: 
- [Make](https://shellrag.com/tutorials/makefile/installation): Pre-installed on Linux and Mac.
- [C](https://installc.org/)
- [GNU Debugger](https://sourceware.org/gdb/download/)

### Prepare compile folder.
Create a <code>bin/</code> directory at the root of the project for all compilation result to stay in there. The Makefile is built around that.

<code>mkdir -p bin</code>

As programs are built in C, you need to perform 2 steps to run the programs: compile and run the executable file(ELF file in Linux).

### Compiling Program
Refer to [Makefile](./Makefile) for options in compiling different parts of the project.

There are 2 build/compile modes: debug mode and testing mode. 
The debug mode is customized to be used with GDB.

Result of all compilation will be store inside <code>bin/</code> directory.

#### Examples
Run commands at the root of the project.

1. Compiling for testing: 
- Testing build for algorithm part(Hash Table): <code>make test_algo</code>
- Testing build for networking part: <code>make test_connection</code>

2. Compiling for debugging: 
- Debug build for algorithm part(Hash Table): <code>make debug_algo</code>
- Debug build for networking part: <code>make debug_connection</code>


#### Executing program.
At the root of the project, run:

1. Executable files for testing:
- Algorithm(Hash Table): <code>./bin/test/algo</code>
- Networking: <code>./bin/test/network/</code>

2. Executable files for debugging:
- Algorithm(Hash Table): <code>./bin/debug/algo</code>
- Networking: <code>./bin/debug/algo</code>
#### Cleanup
To cleanup all executable files, run: 
<code>make clean</code>

## 4. Limitations:
- Lack of documentation for some functions.
- Maybe there are some bad practices for memory management somewhere.

## 5. Helping out
Feel free to help out and thank you for doing so. This can be done in different formats such as: 
- Overcome the limitations listed above.
- Criticize or roast my code with feedback on improved code.
- Suggest new features.

## 6. Declaration of Using AI.
No AI was used to write code in this project. It was used for researching concept of C and related topic to implement this project.

Author: Layhok Leng.
