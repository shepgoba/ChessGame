CXX = g++
CC = gcc

SRC_DIR := src

OBJ_DIR := obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

CXXFLAGS := -Og -Wall -Wextra -Wno-unused-variable -Wno-unused-function -Wno-unused-parameter -Werror -std=c++17
LDFLAGS := 
LIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image



build\chess.exe: $(OBJ_FILES)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<


run: build\chess.exe
	.\build\chess.exe

do: build\chess.exe run

clean:
	@rm -rf obj/*.o
	@rm -rf build/*.exe
