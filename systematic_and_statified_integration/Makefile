# Compiler settings 
CC = g++
CXXFLAGS = -O3 -std=c++14 -Wall -Werror
DEPFLAGS = -MM -MT

# Makefile settings	
OUT = output
EXTENSION = .cpp
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc
DEP_DIR = dep

SRC = $(wildcard $(SRC_DIR)/*$(EXTENSION))
OBJ = $(SRC:$(SRC_DIR)/%$(EXTENSION)=$(OBJ_DIR)/%.o)
DEP = $(OBJ:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

# Check if Windows or Linux
ifeq ($(OS), Windows_NT)
	RM = del
	DELOUT = output.exe
	DELOBJ = $(SRC:$(SRC_DIR)/%$(EXTENSION)=$(OBJ_DIR)\\%.o)
	DELDEP = $(OBJ:$(OBJ_DIR)/%.o=$(DEP_DIR)\\%.d)
else
	RM = rm
	DELOUT = $(OUT)
	DELOBJ = $(OBJ)
	DELDEP = $(DEP)
endif

########################################################################

all: $(OUT)

# Builds the app
$(OUT): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^

# Creates the dependecy rules
$(DEP_DIR)/%.d: $(SRC_DIR)/%$(EXTENSION)
	@$(CPP) $(CXXFLAGS) $< $(DEPFLAGS) $(@:$(DEP_DIR)/%.d=$(OBJ_DIR)/%.o) >$@

# Includes all .hpp files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .hpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%$(EXTENSION)
	$(CC) $(CXXFLAGS) -c $< -o $@

# clean
.PHONY: clean
clean:
	$(RM) $(DELOUT) $(DELOBJ) $(DELDEP)

# clean obj, dep
.PHONY: cleanod
cleanod:
	$(RM) $(OBJ) $(DEP)