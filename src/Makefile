CC = g++ -g -Wall -Werror -Wextra -std=c++17
OS = $(shell uname)
WORK_DIR = ./lib/
SRC_LIB_FILES = $(wildcard $(WORK_DIR)*.cc)
OBJS = $(SRC_LIB_FILES:.cc=.o)
TARGET_LIB = s21_containers.a
TESTS = $(wildcard tests/*.cc)
TEST_NAME = test
OTHER_LIBS = -lgtest -lgcov -fno-elide-constructors  
GCOVFLAGS = -L. --coverage
OUT_FILE = executable

ifeq ($(OS), Linux)
	FLAGS = -lcheck -lm -lpthread -lrt -lsubunit
else
	FLAGS = -lcheck -lm
endif

all: clang gcov

info:
	@echo "SRC_LIB_FILES := $(SRC_LIB_FILES)"

%.o: %.cpp
	$(CC) -c -o $@ $<

$(TARGET_LIB): $(SRC_LIB_FILES)
	$(CC) -c $(SRC_LIB_FILES)
	ar -rc $(TARGET_LIB) *.o 
	rm -rf *.o

.PHONY: test clang
test: clang
	$(CC) $(TESTS) $(FLAGS) $(OTHER_LIBS) -o tests/$(TEST_NAME)
	tests/$(TEST_NAME)

gcov: clang
	$(CC) $(FIX_GCOV) -w $(SRC_LIB_FILES) tests/*.cc  $(OTHER_LIBS) $(GCOVFLAGS) -o test
	./test 
ifeq ($(OS), Linux)
	lcov --no-external -t test -o rep.info -c -d .
else 
	lcov --ignore-errors mismatch --no-external -t test -o rep.info -c -d .
endif
	genhtml -o report rep.info
	open ./report/index.html
	rm -rf *.gcda *.gcno *.info

val: test
	valgrind --quiet -s --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=testlog.log tests/$(TEST_NAME)
# valgrind --quiet -s --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=testlog.log ./executable

clang:
	-@clang-format -style=google -i $(WORK_DIR)*.cc
	-@clang-format -style=google -i $(WORK_DIR)*.h

clean:
	-@rm a.out executable testlog.log s21_containers.a tests/test test *.gcno *.gcda 
	-@rm -rf report tests/test.dSYM executable.dSYM test.dSYM


