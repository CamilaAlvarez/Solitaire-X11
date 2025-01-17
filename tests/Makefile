GTEST_INC = /usr/local/include
GTEST_LIB = gtest
SRC = ../src
CC = g++
C_FLAGS = -std=c++17 -c -Wall -I $(GTEST_INC) -I ../include
LD_FLAGS = -std=c++17 -L /usr/local/lib -l $(GTEST_LIB) -l pthread
OBJECTS = tests.o test_card.o test_deck.o deck.o
TARGET = run_tests

all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LD_FLAGS)
test_card.o: test_card.cpp
	$(CC) $(C_FLAGS) $<
tests.o : tests.cpp
	$(CC) $(C_FLAGS) $<
test_deck.o: test_deck.cpp $(SRC)/deck.cpp
	$(CC) $(C_FLAGS) $<
deck.o: $(SRC)/deck.cpp
	$(CC) $(C_FLAGS) $<
run: all
	./$(TARGET)
clean: 
	rm -f $(TARGET) $(OBJECTS)
.PHONY: all clean