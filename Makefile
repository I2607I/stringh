# TEST_FLAGS=-lpthread -lcheck -pthread -lrt -lm -lsubunit
TEST_FLAGS=-I -L -lcheck `pkg-config --cflags --libs check`
CPP_FLAGS=-Wall -Wextra -Werror
DEBUG_FLAG=-g
GCOV_FLAG=--coverage
OBJECTS=string.o test.o
FUNCS=string.c
#TEST_C=test.c string.a
TEST_C=test.c string.c 
HEADER=string.h
EXECUTABLE=test.out
CC=gcc
LINT_WAY=../materials/linters/cpplint.py
LINTCFG_WAY=../materials/linters/CPPLINT.cfg
LINTCFG=CPPLINT.cfg
COPY=cp
PY=python3
EXTENSION=--extensions=c
CHECK_FILES=*.c *.h
CPPCH=cppcheck
DELETE=rm -rf
TO_DELETE=*.o *.a *.gcda *.gcno *.info
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	CC += -D OS_MAC
	TEST_FLAGS =-lcheck
endif
ifeq ($(OS), linux)
	CC += -D OS_LINUX
	TEST_FLAGS =-lpthread -lcheck -pthread -lrt -lm -lsubunit
endif


all: clean string.a test

clean:
	$(DELETE) $(TO_DELETE) $(EXECUTABLE) $(LINTCFG) report

test:
	$(CC) $(DEBUG_FLAG) $(GCOV_FLAG) $(TEST_C) -o $(EXECUTABLE) $(TEST_FLAGS)
# $(CC) $(DEBUG_FLAG) $(GCOV_FLAG) $(TEST_C) -o $(EXECUTABLE) $(TEST_FLAGS)
	./test.out

gcov_report: test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info


string.a:
	$(CC) -c $(FUNCS)
	ar rc string.a string.o
	ar rc libstring.a string.o
	ranlib string.a
	ranlib libstring.a

valgrind_check:
	CK_FORK=no valgrind --tool=memcheck ./$(EXECUTABLE)
