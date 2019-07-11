BASE_DIR := ./Ion.IR
INCLUDE_DIR := $(BASE_DIR)/include
SRC_DIR := $(BASE_DIR)/src
OBJ_DIR := $(BASE_DIR)/obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

build: $(OBJ_FILES)
	clang -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	clang -I$(INCLUDE_DIR) -c -o $@ $<
