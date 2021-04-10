#Work title
TARGET=gardenofmists

#Directories
OBJ_DIR=obj
SRC_DIR=src
INC_DIRS=includes
LIB_DIRS=

#Compilation related indications
CC=clang
CFLAGS= -g -Wall -Wextra -Werror `pkg-config --cflags gtk+-3.0`
LIBS=git2

#From there we use the info to compile everything.
SRC_FILE_NAMES = main.c common.c git.c load_css.c notifications.c load_glade.c events.c welcome_screen.c
SOURCES=$(addprefix $(SRC_DIR)/, $(SRC_FILE_NAMES))
OBJS:=$(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
INC_FLAGS=$(addprefix -I,$(INC_DIRS))
LIBIDR_FLAGS=$(addprefix -L,$(LIB_DIRS))
CFLAGS+=$(INC_FLAGS)
LIBS_FLAGS=$(addprefix -l,$(LIBS))
VPATH=$(SRC_DIR)

.phony: $(TARGET) clean re

all: $(TARGET)

$(TARGET): $(OBJS)	
	@$(CC) $(CFLAGS) -MMD $(OBJS) -o $(TARGET) $(LIBIDR_FLAGS) $(LIBS_FLAGS) `pkg-config --libs gtk+-3.0`
	@echo "Compilation succeeded."

$(OBJS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIRS)/* |$(OBJ_DIR) 
	@$(COMPILE.c) $(OUTPUT_OPTIONS) -o $@ $<
	@echo "Compiled 1 file."

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJS) $(TARGET)

re: clean $(TARGET)

debian-deps:
	echo "No dependencies"

test: all
	@$(CC) $(CFLAGS) $(OBJ_DIR)/common.o $(OBJ_DIR)/git.o $(OBJ_DIR)/notifications.o tests/test.c $(LIBIDR_FLAGS) $(LIBS_FLAGS) `pkg-config --libs gtk+-3.0` -o gardenoftests
	clear && ./gardenoftests
