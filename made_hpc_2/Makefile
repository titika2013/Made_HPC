CC=g++
CFLAGS=-c
CXXFLAGS=-std=c++17

BUILD=build
SOURCE_DIR=src

SOURCES=$(wildcard $(SOURCE_DIR)/*.cpp)

all: $(BUILD)

$(BUILD): main.o matrix.o
	$(CC) $(OPT) main.o matrix.o -o $(BUILD)

main.o: main.cpp
	$(CC) $(OPT) $(CFLAGS) main.cpp

matrix.o: $(SOURCES)
	$(CC) $(OPT) $(CFLAGS) $(SOURCES)
 
run:
	./$(BUILD) $(N)

clean:
	rm -rf *.o $(BUILD)