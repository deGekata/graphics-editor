# Applicaton options
APPLICATION = $(notdir $(CURDIR))# Application name is name of root holder
GXX_STANDARD = 17 # 11, 14, 17, 20
OUT_FILE_NAME = $(APPLICATION).exe


# Get project directory
CWD := $(subst /,\, $(abspath $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))))

# test:
# 	$(info    DIR is $(CWD))

# Сompiler options
CC = g++
INCLUDE_PATHS = -I $(CWD)\\SDL2\\include -I $(CWD)\\SDL2\\include\\SDL2 -I $(CWD)\\src\\CoreLib\\
LIBS_PATHS = -L $(CWD)\\SDL2\\lib
CXXFLAGS = -Wall -Wextra -std=c++$(GXX_STANDARD) -fopenmp  -lpthread
CXXFLAGS += -g -lmingw64 -lSDL2main -lSDL2  $(INCLUDE_PATHS) $(LIBS_PATHS)
LXXFLAGS = -fopenmp -lpthread

# Debug or Release
# BUILD = Debug
BUILD = Release

# Folder name setting
SRC_DIR = src
BIN_DIR = bin

# Setting build parameters
ifeq ($(BUILD), Debug)
	CXXFLAGS += -O0 -g -fdiagnostics-color=always
	BUILD_PATH = build-debug
else
# CXXFLAGS += -O1 -g -fdiagnostics-color=always
	CXXFLAGS += -O3 -s -g -DNDEBUG 
	BUILD_PATH = build-debug
endif

# Search for source files
SRC_FULL_PATH = $(shell where /r .\ *.cpp)
EXLUDED = # Excluded files
SRC = $(filter-out $(EXLUDED),$(notdir $(SRC_FULL_PATH)))
OBJ = $(addprefix $(BIN_DIR)/, $(SRC:.cpp=.o))

# Include library
LIB_PATH = $(CWD)\\SDL2\\
LIB_DEPEND = mingw32 SDL2main SDL2 
CXXFLAGS += $(patsubst %,-I%/include,$(LIB_PATH))
LXXFLAGS += $(patsubst %,-L%\\lib,$(LIB_PATH)) $(addprefix -l, $(LIB_DEPEND))

# Сonfiguring file search paths
VPATH = echo $(subst \,/,$(dir $(SRC_FULL_PATH)))

# Build project
$(BUILD_PATH)/$(OUT_FILE_NAME): $(OBJ) Makefile
	@ $(CC) $(OBJ) -o $(BUILD_PATH)/$(OUT_FILE_NAME) $(LXXFLAGS)
	$(BUILD_PATH)/$(OUT_FILE_NAME)

# Dependency checking
include $(addprefix $(BIN_DIR)/, $(SRC:.cpp=.d))

# Compilation source
$(BIN_DIR)/%.o: %.cpp Makefile
	@ $(CC) $< -c -o $@ $(CXXFLAGS)

# Updating dependencies
$(BIN_DIR)/%.d: %.cpp Makefile
	@ $(CC) $<  $(CXXFLAGS) -MM -MT '$(BIN_DIR)/$*.o $(BIN_DIR)/$*.d' -MF $@ 

.PHONY: init clean
init:
	if not exist $(BIN_DIR) md $(BIN_DIR)
	if not exist $(BUILD_PATH) md $(BUILD_PATH)

clean:
	if exist $(CWD)\\$(BIN_DIR) rmdir /S /Q $(BIN_DIR)