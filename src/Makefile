#
#	Если хочешь знать, как это работает, загляни в
#		https://habr.com/ru/post/155201/.
# 	Если этого мало, отведай https://stackoverflow.com/questions/2734719/
# 		how-to-compile-a-static-library-in-linux
#
#

SHELL := /bin/bash
CC=gcc
CFLAGS=-Wall -Wextra -Werror
LDFLAGS=
SOURCES=$(wildcard s21_*.c)
HEADERS=$(wildcard s21_*.h)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=

ifeq ("$(shell uname -s)", "Linux")
	CLIBS=-lm -lcheck -lsubunit -lrt -lpthread
	####...-lsubunit -lrt -lpthread -lm --- lcheck, видимо,
	####    использует эти библиотеки
	XDG=xdg-open
else
	CLIBS=-lm -lcheck
	XDG=open
endif


all: clean test gcov_report


%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@


s21_string.a: $(OBJECTS)
	ar -rcs $@ $^


gcov_report:
	##gcov ./tests/*.gcda
	####gcov --- выводит профилировачную инфу в консоль
	geninfo ./tests/*.gcda
	genhtml ./tests/*.info --output-directory ./tests/
	$(XDG) ./tests/src/index.html


test: ./tests/sce_unit_tests.c $(SOURCES)
	$(CC) $(CFLAGS) \
		-fprofile-arcs -ftest-coverage \
		$^ \
		-o ./tests/unit_tests.out \
		$(CLIBS)
		####...-fprofile-arcs -ftest-coverage --- это для gcov-теста
		####
	./tests/unit_tests.out; exit 0


clean:
	find ./ \( -iname "*.gcda" \
		-or -iname "*.gcov" \
		-or -iname "*.gcno" \
		-or -iname "*.out" \
		-or -iname "*.o" \
		-or -iname "*.a" \
		-or -iname "*.html" \
		-or -iname "*.info" \
		-or -iname "*.css" \
		-or -iname "*.png" \
		-or -iname "*.png" \
		-or -iname "*.out" \
	\) -delete

	rm -rf ./tests/src/ \
		./.DS_Store \
