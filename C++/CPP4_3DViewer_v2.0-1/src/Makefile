CC = gcc -std=c++17 -g
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes
GCOV_LIBS=--coverage
RM+=-r

PATH_CONTROLLER = ./controller
PATH_MODEL = ./model
TEST_VIEW = $(PATH_TESTS)/test_view/test_view.cc
PATH_TESTS = ./tests
PATH_DATA = $(PATH_MODEL)/dao
PATH_KERNEL = $(PATH_MODEL)/kernel
PATH_OBSERVER = $(PATH_MODEL)/observer
PATH_STRATEGY = $(PATH_KERNEL)/strategy_transform

TEST = $(PATH_TESTS)/tests.cc
SRC = $(PATH_CONTROLLER)/controller.cc $(PATH_MODEL)/facade.cc $(PATH_DATA)/data_model.cc $(PATH_KERNEL)/parser.cc $(PATH_KERNEL)/optimal_scale_calculator.cc \
	  $(PATH_STRATEGY)/move.cc $(PATH_STRATEGY)/rotate.cc $(PATH_STRATEGY)/scale.cc $(PATH_STRATEGY)/transform_strategy.cc $(TEST_VIEW)

HEADERS = $(PATH_CONTROLLER)/*.h $(PATH_MODEL)/*.h $(PATH_DATA)/*.h $(PATH_KERNEL)/*.h $(PATH_OBSERVER)/*.h $(PATH_STRATEGY)/*.h
OBJ = $(SRC:.cc=.o)
LIBA = 3DViewer_v2_0.a
EXE = 3DViewer_v2_0
ARCHIVE_DIR = 3DViewer_v2_0


OS = $(shell uname)

ifeq ($(OS), Darwin)
	LIBFLAGS = -lgtest -lstdc++ -lgtest_main
else
	LIBFLAGS = -lstdc++ `pkg-config --cflags --libs gtest  --libs gtest_main`
endif

all: install

build: clean
	mkdir build
	cd ./build/ && qmake ../view && make

install: build
	cd ./build/ && make clean
	./build/3DViewer_v2.app/Contents/MacOS/3DViewer_v2

uninstall:
	rm -rf build/

dist:
	rm -rf $(ARCHIVE_DIR)
	mkdir $(ARCHIVE_DIR)
	mkdir $(ARCHIVE_DIR)/src
	cp -r ./view ./controller ./model ./tests dvi.html Makefile $(ARCHIVE_DIR)/src/
	tar cvzf $(ARCHIVE_DIR).tgz $(ARCHIVE_DIR)
	rm -rf $(ARCHIVE_DIR)

dvi:
	open dvi.html

clean:
	@rm -rf *.gcda *.o *.a *.gcno *.tgz *.txt *.info *.dSYM report build coverage $(EXE) $(ARCHIVE_DIR) $(OBJ)

%.o: %.cc
	$(CC) $(CFLAGS) $(LIBFLAGS) -c $^ -o $@

$(LIBA): $(OBJ)
	ar rcs $(LIBA) $^

tests: $(LIBA)
	$(CC) $(CFLAGS) $(TEST)  -L. $(LIBFLAGS) $(LIBA) -o $(EXE) -lm
	./$(EXE)

gcov_report: $(LIBA)
	$(CC) $(GCOV_LIBS) $(CFLAGS) $(TEST) $(SRC) -L. $(LIBFLAGS) $(LIBA) -o coverage -lm
	./coverage
	lcov -t "coverage" -c -d  ./ --no-external --output-file ./coverage.info
	genhtml ./coverage.info --output-directory ./report/
	open ./report/index.html

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config $(TEST) $(SRC) $(HEADERS)
	@clang-format -i $(TEST) $(SRC) $(HEADERS)
	clang-format -n $(TEST) $(SRC) $(HEADERS) -Werror

leaks: tests
ifeq ($(OS), Darwin)
	leaks -atExit -- ./$(EXE)
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --error-exitcode=1 --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./$(EXE)
endif

rebuild: clean uninstall all

reinstall: clean uninstall install

.PHONY:		all install uninstall dist dvi clean check tests gcov_report
