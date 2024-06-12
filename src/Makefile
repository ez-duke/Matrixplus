#!/bin/bash
CC=g++ -Wall -Werror -Wextra -std=c++17 -g
SRC=*.cpp
OBJ=build/*.o
TSRC=tests/*.cpp
NAME=s21_matrix_oop
TNAME=$(NAME)_tests
LIB_NAME=$(NAME).a
UNAME=$(shell uname -s)
HEADERS=*.h tests/*.hpp

ifeq ($(UNAME),Linux)
	LIBS=-lgtest -lgcov -lm
endif

ifeq ($(UNAME),Darwin)
	LIBS=-lgtest -lgcov
endif

all: gcov_report $(LIB_NAME)

clean:
	rm -rf build/* $(LIB_NAME)

rebuild: clean all

cf:
	clang-format --style=Google -i $(SRC) $(TSRC) $(HEADERS)

check:
	clang-format --style=Google -n $(SRC) $(TSRC) $(HEADERS)

cppc:
	cppcheck --language=c++ --enable=all --suppress=missingIncludeSystem $(SRC) $(TSRC) $(HEADERS)

$(LIB_NAME): $(SRC)
	$(CC) -c $(SRC)
	mv *.o build
	ar rcs $(LIB_NAME) $(OBJ)

test: clean $(SRC) $(TSRC)
	$(CC) $(SRC) $(TSRC) -o build/$(TNAME) $(LIBS)
	build/$(TNAME)

gcov_report: clean $(SRC) $(TSRC)
	$(CC) $(SRC) $(TSRC) --coverage $(LIBS) -o build/$(TNAME)
	build/$(TNAME)
	lcov --no-external -o build/coverage.info -c -d .
	genhtml -o build/report build/coverage.info
ifeq ($(UNAME),Darwin)
	open build/report/index.html
endif

valgrind: clean $(SRC) $(TSRC)
	$(CC) $(SRC) $(TSRC) -o build/$(TNAME) $(LIBS)
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all build/$(TNAME)
