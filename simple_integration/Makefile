# Compiler settings 
CC = g++
CXXFLAGS = -O3 -std=c++14 -Wall -Werror
DEPFLAGS = -MM -MT

# Makefile settings	
OUT = output
EXTENSION = .cpp

SRC = $(wildcard *$(EXTENSION))
OBJ = $(SRC:%$(EXTENSION)=%.o)
DEP = $(OBJ:%.o=%.d)

# Check if Windows or Linux
ifeq ($(OS), Windows_NT)
	RM = del
	DELOUT = output.exe
else
	RM = rm
	DELOUT = $(OUT)
endif


########################################################################

all: $(OUT)

# Builds the app
$(OUT): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^

# Creates the dependecy rules
%.d: %$(EXTENSION)
	@$(CPP) $(CXXFLAGS) $< $(DEPFLAGS) $(@:%.d=%.o) >$@

# Includes all .hpp files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .hpp
%.o: %$(EXTENSION)
	$(CC) $(CXXFLAGS) -c $< -o $@

# clean
.PHONY: clean
clean:
	$(RM) $(DELOUT) $(OBJ) $(DEP)

# clean obj, dep
.PHONY: cleanod
cleanod:
	$(RM) $(OBJ) $(DEP)