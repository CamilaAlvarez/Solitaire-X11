CC := g++
C_FLAGS := -std=c++17 -Wall -I include $(C_FLAGS) 
LD_FLAGS := -std=c++17 -L /usr/local/lib -l X11 $(LD_FLAGS)
SRC := src
BUILD := build
TARGET := run_game
SRC_FILES := $(shell find $(SRC) -type f -name \*.cpp -exec basename {} \;)
OBJECTS  := $(addprefix $(BUILD)/,$(SRC_FILES:.cpp=.o))

all:$(TARGET)

$(BUILD)/%.o:$(SRC)/%.cpp
	mkdir -p $(BUILD)	
	$(CC) $(C_FLAGS) -c $^ -o $@

$(TARGET):$(OBJECTS)
	$(CC) $^ -o $@ $(C_FLAGS) $(LD_FLAGS)
clean:
	rm -rf $(BUILD)
.PHONY: all clean 
