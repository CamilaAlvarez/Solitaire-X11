GTEST_INC = /usr/local/include
GTEST_LIB = gtest
SRC = ../src
CC = g++
C_FLAGS = -std=c++17 -c -Wall -I $(GTEST_INC) -I ../include
LD_FLAGS = -std=c++17 -L /usr/local/lib -l $(GTEST_LIB) -l pthread
OBJECTS = face_up_card_location.o deck.o wastepile.o stockpile.o foundation.o
TEST_OBJECTS = tests.o test_card.o test_deck.o test_face_up_card_location.o test_wastepile.o test_stockpile.o test_foundation.o
TARGET = run_tests

all: $(TARGET)
$(TARGET): $(OBJECTS) $(TEST_OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(TEST_OBJECTS) $(LD_FLAGS)
test_card.o: test_card.cpp
	$(CC) $(C_FLAGS) $<
tests.o : tests.cpp
	$(CC) $(C_FLAGS) $<
test_deck.o: test_deck.cpp $(SRC)/deck.cpp
	$(CC) $(C_FLAGS) $<
test_face_up_card_location.o: test_face_up_card_location.cpp $(SRC)/face_up_card_location.cpp
	$(CC) $(C_FLAGS) $<
test_wastepile.o: test_wastepile.cpp $(SRC)/wastepile.cpp
	$(CC) $(C_FLAGS) $<
test_stockpile.o: test_stockpile.cpp $(SRC)/stockpile.cpp
	$(CC) $(C_FLAGS) $<
test_foundation.o: test_foundation.cpp $(SRC)/foundation.cpp
	$(CC) $(C_FLAGS) $<
deck.o: $(SRC)/deck.cpp
	$(CC) $(C_FLAGS) $<
face_up_card_location.o: $(SRC)/face_up_card_location.cpp
	$(CC) $(C_FLAGS) $<
wastepile.o: $(SRC)/wastepile.cpp
	$(CC) $(C_FLAGS) $<
stockpile.o: $(SRC)/stockpile.cpp
	$(CC) $(C_FLAGS) $<
foundation.o: $(SRC)/foundation.cpp
	$(CC) $(C_FLAGS) $<
run: all
	./$(TARGET)
clean: 
	rm -f $(TARGET) $(OBJECTS) $(TEST_OBJECTS)
.PHONY: all clean