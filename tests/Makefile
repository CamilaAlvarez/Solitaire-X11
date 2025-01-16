GTEST_INC = /usr/local/include
GTEST_LIB = gtest
CC = g++
C_FLAGS = -std=c++17 -c -Wall -I $(GTEST_INC) -I ../include
LD_FLAGS = -std=c++17 -L /usr/local/lib -l $(GTEST_LIB) -l pthread
OBJECTS = tests.o test_card.o
TARGET = tests

all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LD_FLAGS)
%.o: %.cpp
	$(CC) $(C_FLAGS) $<
run: all
	./$(TARGET)
clean: 
	rm -f $(TARGET) $(OBJECTS)
.PHONY: all clean