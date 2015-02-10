CXX=c++
CXXFLAGS=-pedantic -Wall -std=c++11 -g -O3

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
BIN=fat
else
BIN=fat.exe
endif

.PHONY:all clean

all: $(BIN)

$(BIN): fat.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
