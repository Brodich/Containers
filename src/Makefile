CC = g++ -g
OS = $(shell uname)
WORK_DIR = ./
SRC_LIB_FILES=$(wildcard $(WORK_DIR)*.cc)
OBJS = $(SRC_LIB_FILES:.cc=.o)
OUT_FILE = goku

ifeq ($(OS), Linux)
	FLAGS = -lcheck -lm -lpthread -lrt -lsubunit
else
	FLAGS = -lcheck -lm
endif


all: list run

info:
	@echo "SRC_LIB_FILES := $(SRC_LIB_FILES)"

%.o: %.cpp
	$(CC) -c -o $@ $<

list:
	$(CC) $(SRC_LIB_FILES) -o $(OUT_FILE)

run:
	./$(OUT_FILE)