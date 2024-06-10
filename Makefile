CC = gcc
FLAGS = -Wall -Werror -Wextra
LFLAGS = -lcheck

ifeq ($(shell uname), Linux)
  LFLAGS += -pthread -lsubunit -lrt -lm
endif

all: clean test

test: s21_matrix.a
	$(CC) $(FLAGS) -c s21_matrix_test.c
	$(CC) s21_matrix_test.o $(FLAGS) $(LFLAGS) -L. s21_matrix.a -o test

s21_matrix.a:
	$(CC) $(FLAGS) -c s21_matrix.c 
	ar rc s21_matrix.a s21_matrix.o 
	ranlib s21_matrix.a

add_coverage:
	$(eval FLAGS += --coverage)

gcov_report: clean add_coverage test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

style_check:
	clang-format -n *.c *.h

style_fix:
	clang-format -i *.c *.h

clean: 
	rm -rf *.o *.a *.gcno *.gcda test test.info report

rebuild: clean all
