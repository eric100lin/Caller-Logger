CC = gcc
CXX = g++
AR = ar
LD = g++
CFLAGS = -g
CXXFLAGS = -g -std=gnu++0x

PROGRAM_NAME = ./CallerLogger
SOURCE_PATH = ./
INCLUDE_PATH = -I./
OBJ_DIR = .objs
Csources = $(wildcard $(SOURCE_PATH:=*.c))
CXXsources = $(wildcard $(SOURCE_PATH:=*.cpp))
PROGRAM_OBJS := ${Csources:.c=.o} ${CXXsources:.cpp=.o}
PROGRAM_OBJS := $(addprefix $(OBJ_DIR)/,$(PROGRAM_OBJS))

all: before_compile COMPILING after_compile

before_compile: 
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)

after_compile:

COMPILING: $(PROGRAM_OBJS)
	$(LD) -o $(PROGRAM_NAME) $(addprefix $(OBJ_DIR)/, $(notdir $(PROGRAM_OBJS))) $(LD_LIBS)

$(OBJ_DIR)/%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -c $< -o $(OBJ_DIR)/$(@F)

$(OBJ_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c $< -o $(OBJ_DIR)/$(@F)

clean:
	rm -fr $(OBJ_DIR)/
	rm $(PROGRAM_NAME)

.PHONY: before_compile after_compile
