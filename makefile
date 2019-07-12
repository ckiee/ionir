BASE_DIR := ./Ion.IR
INCLUDE_DIR := $(BASE_DIR)/include
SRC_DIR := $(BASE_DIR)/src
OBJ_DIR := $(BASE_DIR)/obj
SRC_FILES := $(shell find $(SRC_DIR) -type f -name '*.hh')
OBJ_FILES := $(patsubst $(SRC_DIR)/%.hh,$(OBJ_DIR)/%.o,$(SRC_FILES))
ARGS := -Wall

build: $(OBJ_FILES)
	clang++ $(ARGS) -o $@ $^

clean:
	@rm -rf $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)

setup:
	@mkdir -p $(OBJ_DIR)
	@git submodule init
	@git submodule update

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	clang++ $(ARGS) -I$(INCLUDE_DIR) -c -o $@ $<
