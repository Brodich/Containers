CC = g++ -g
OS = $(shell uname)
WORK_DIR = ./
SRC_LIB_FILES = $(wildcard $(WORK_DIR)*.cc)
OBJS = $(SRC_LIB_FILES:.cc=.o)
TARGET_LIB = s21_containers.a
TESTS = $(wildcard tests/*.cc)
TEST_NAME = test
OTHER_LIBS = -lgtest -lgcov -fno-elide-constructors  
OUT_FILE = executable

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
	$(CC) $(SRC_LIB_FILES) main.cpp -o $(OUT_FILE)

$(TARGET_LIB): $(SRC_LIB_FILES)
	$(CC) -c $(SRC_LIB_FILES)
	ar -rc $(TARGET_LIB) *.o 
	rm -rf *.o


test: $(TARGET_LIB)
	$(CC) $(TESTS) $(TARGET_LIB) $(FLAGS) $(OTHER_LIBS) -o tests/$(TEST_NAME)
	tests/$(TEST_NAME)

val: test
	valgrind --quiet -s --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=testlog.log ./executable
# valgrind --quiet -s --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=testlog.log tests/$(TEST_NAME)

run:
	./$(OUT_FILE)

clean:
	-@rm a.out executable testlog.log s21_containers.a tests/test