# TEST_FLAGS=-lpthread -lcheck -pthread -lrt -lm -lsubunit
TEST_FLAGS=-I -L -lcheck `pkg-config --cflags --libs check`
CPP_FLAGS=-Wall -Wextra -Werror
DEBUG_FLAG=-g
GCOV_FLAG=--coverage
OBJECTS=s21_string.o s21_test.o
FUNCS=s21_string.c
#TEST_C=s21_test.c s21_string.a
TEST_C=s21_test.c s21_string.c 
HEADER=s21_string.h
EXECUTABLE=s21_test.out
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


all: clean check s21_string.a test

check:
	$(CPPCH) $(CHECK_FILES)
	$(COPY) $(LINTCFG_WAY) $(LINTCFG)
	$(PY) $(LINT_WAY) $(EXTENSION) $(CHECK_FILES)

clean:
	$(DELETE) $(TO_DELETE) $(EXECUTABLE) $(LINTCFG)

test:
	$(CC) $(DEBUG_FLAG) $(GCOV_FLAG) $(TEST_C) -o $(EXECUTABLE) $(TEST_FLAGS)
# $(CC) $(DEBUG_FLAG) $(GCOV_FLAG) $(TEST_C) -o $(EXECUTABLE) $(TEST_FLAGS)
	./s21_test.out

gcov_report: test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info


s21_string.a:
	$(CC) -c $(FUNCS)
	ar rc s21_string.a s21_string.o
	ar rc libs21_string.a s21_string.o
	ranlib s21_string.a
	ranlib libs21_string.a

valgrind_check:
	CK_FORK=no valgrind --tool=memcheck ./$(EXECUTABLE)
