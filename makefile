TARGET_EXEC := final
INC_DIRS := include
BUILD_DIR := build
OBJS_DIR := build/objs
SRC_DIR := src

CC=gcc
CFLAGS := -g

INC_FLAGS := -I$(INC_DIRS)

SRCS := $(shell find $(SRC_DIR) -name '*.c' -or -name '*.s')
# OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

build:# Won't delete the files, only makes
	@$(CC) $(CFLAGS) $(SRCS) -o $(TARGET_EXEC)
	@chmod +x $(TARGET_EXEC)
	@echo Compiled... Please check ./final

execute:
	./final

clean:
	rm -f *.o
	rm -f final
