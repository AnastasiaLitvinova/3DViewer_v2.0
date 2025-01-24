CXX := g++ -g
WFLAGS := -Wall -Wextra -Werror -std=c++17 -pedantic
GCOVFLAGS := -fprofile-arcs -ftest-coverage --coverage
SOURCES := model/parser.cpp model/transformations.cpp model/manipulation.cpp
SOURCES_TEST := tests/tests.cpp
OS := $(shell uname -s)

CFLAGS := 
CHECKFLAGS := 
NO_ERR := 

ifeq ($(OS), Linux)
  CFLAGS += -D OS_LINUX
  CHECKFLAGS += -lpthread -lcheck -pthread -lrt -lsubunit -lm
  NO_ERR += --ignore-errors mismatch
else ifeq ($(OS), Darwin)
  CFLAGS += -D OS_MAC
  CHECKFLAGS += -lcheck
  NO_ERR += --ignore-errors inconsistent
endif

all: clean install

install: uninstall
	mkdir -p 3DViewer && cd 3DViewer && qmake ../view && make -j4

uninstall: clean
	rm -rf 3DViewer

test: clean
	$(CXX) $(WFLAGS) $(CFLAGS) $(SOURCES) $(SOURCES_TEST) $(CHECKFLAGS) $(GCOVFLAGS) -o test -lgtest
	./test

gcov_report: test
	lcov -c -d . $(NO_ERR) --no-external -o test.info
	genhtml $(NO_ERR) -o report test.info
	open ./report/index.html
	rm -rf test.info *.gcda *.gcno

dvi:
	doxygen
	open ./doxygen/html/index.html

dist:
	zip -qr ../3DViewer.zip . -x ./3DViewer.zip

clang:
	@cp ../materials/linters/.clang-format .clang-format
	clang-format -n $(shell find ./model -name *.h -o -name *.cpp) \
	./view/main*.h ./view/main*.cpp ./view/Open*.h ./view/Open*.cpp \
	./controller/*.h $(SOURCES_TEST)
	@rm .clang-format

style:
	@cp ../materials/linters/.clang-format .clang-format
	clang-format -i $(shell find ./model -name *.h -o -name *.cpp) \
	./view/main*.h ./view/main*.cpp ./view/Open*.h ./view/Open*.cpp \
	./controller/*.h  $(SOURCES_TEST)
	@rm .clang-format

leaks: test
	leaks -atExit -- ./test

clean:
	@rm -rf *.o ./test ./test.dSYM ./report test.info *.gcda *.gcno

valgrind: 
	valgrind --tool=memcheck --leak-check=yes --log-file=log.txt ./test

check:
	cppcheck --enable=all --suppress=missingIncludeSystem $(shell find . -name *.cpp)
