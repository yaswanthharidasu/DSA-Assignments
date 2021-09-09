SRC_DIR := ./src
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Generates the output file
output: $(OBJ_FILES)
	$(CXX) $^ -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $< -o $@
	@echo Compiled "$<" successfully

# "make clean" command removes the .o files in the obj directory and output file
clean: 
	rm -f core output $(OBJ_FILES)