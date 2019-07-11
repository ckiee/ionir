BASE_DIR := ./Ion.IR
SRC_DIR := $(BASE_DIR)/src
OBJ_DIR := $(BASE_DIR)/obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

main: $(OBJ_FILES)
	clang -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	clang -IIon.IR/include -c -o $@ $<
