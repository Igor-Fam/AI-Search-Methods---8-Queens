CC=g++
CC_FLAGS=
INC_DIR=./include
SRC_DIR=./src

CPP_SOURCE=$(wildcard $(SRC_DIR)/*.cpp)

HPP_SOURCE=$(wildcard $(INC_DIR)/*.hpp)

MAIN_SRC=main.cpp $(CPP_SOURCE)
MAIN_HPP=$(HPP_SOURCE)

build: main.exe

main.exe: $(MAIN_SRC) $(MAIN_HPP)
	$(CC) $(CC_FLAGS) -o $@ $(MAIN_SRC) -I $(INC_DIR)