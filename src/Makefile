CC=gcc
CPP=g++
CC_FLAGS= -g -Wall -Werror -Wextra
CPP_FLAGS = -g -Wall -Wextra -Werror -std=c++17
GCOV_FLAGS=--coverage
TEST_FLAGS_G = -lgtest -lgtest_main -lstdc++ -pthread
LDFLAGS = -lgtest -lgtest_main -pthread --coverage
# Цели
TARGET_TETRIS_CLI=tetris_cli
TARGET_SNAKE_CLI=snake_cli
DESKTOP_SNAKE_TETRIS = desktop_snake_tetris
BACK_LIB_TETRIS = s21_tetris.a
CLI_LIB = s21_cli.a
BACK_LIB_SNAKE = s21_snake.a
# Директории
SRC_DIR=src
BIN_DIR=build
LIB_DIR=lib
TESTS_DIR=tests
DIST_DIR=dist
GCOV_REPORT_DIR=report
#файлы
INFO= coverage.info
TEST_T=tetris_test
TEST_S=snake_test
# Исходные коды
SOURCES= gui/cli/*.c brick_game/tetris/*.c main/main_tetris.c
TEST_SOURCES_T= tests/Ttest.c
TEST_SOURCES_S= tests/Stest.cc
LIBS_DIRS     = -I./brick_game/tetris/ -I ./gui/cli/
LIBS 		  = $(LIBS_DIRS)


EXE=test.out
BUILD_PATH=./

SYSTEM := $(shell uname -s)

ifeq ($(SYSTEM), Darwin)
	OPEN_CMD = open
	TEST_FLAGS = -lcheck -lm -lncurses
	TEST_FLAGS_G = -lgtest -lgtest_main -lstdc++ -pthread
	BREW := ${HOME}/homebrew
else
	OPEN_CMD = xdg-open
	TEST_FLAGS = -lcheck -lsubunit -lm -lncurses
	TEST_FLAGS_G = -lgtest -lgtest_main -lrt -lstdc++ -pthread
endif
.PHONY: clean build
all: clean install

########################################## Compiles
$(BACK_LIB_SNAKE): folder_lib
	$(CPP) $(CPP_FLAGS) -c brick_game/snake/*.cc
	mv *.o $(LIB_DIR)/
	ar rc $(LIB_DIR)/$(BACK_LIB_SNAKE) $(LIB_DIR)/*.o
	ranlib $(LIB_DIR)/$(BACK_LIB_SNAKE)
	rm -rf $(LIB_DIR)/*.o
$(BACK_LIB_TETRIS): folder_lib
	$(CC) $(CC_FLAGS) -c brick_game/tetris/*.c -o $(LIB_DIR)/s21_tetris.o
	ar rc $(LIB_DIR)/$(BACK_LIB_TETRIS) $(LIB_DIR)/*.o
	ranlib $(LIB_DIR)/$(BACK_LIB_TETRIS)
	rm -rf $(LIB_DIR)/*.o
$(CLI_LIB): folder_lib
	$(CC) $(CC_FLAGS) -c gui/cli/front.c -o $(LIB_DIR)/s21_tetris_cli.o
	ar rc $(LIB_DIR)/$(CLI_LIB) $(LIB_DIR)/*.o
	ranlib $(LIB_DIR)/$(CLI_LIB)
	rm -rf $(LIB_DIR)/*.o

$(TARGET_SNAKE_CLI): $(BACK_LIB_SNAKE) $(CLI_LIB) folder_build
	$(CPP) $(CPP_FLAGS) -D SNAKE_CLI gui/cli/snake_cli.cc $(LIB_DIR)/$(BACK_LIB_SNAKE) $(LIB_DIR)/$(CLI_LIB) -lncurses -o $(BIN_DIR)/$(TARGET_SNAKE_CLI) 	
$(TARGET_TETRIS_CLI): $(BACK_LIB_TETRIS) $(CLI_LIB) folder_build
	$(CPP) $(CC_FLAGS) -D TETRIS_CLI gui/cli/tetris_cli.cc $(LIB_DIR)/$(BACK_LIB_TETRIS) $(LIB_DIR)/$(CLI_LIB) -lncurses -o $(BIN_DIR)/$(TARGET_TETRIS_CLI)

$(DESKTOP_SNAKE_TETRIS): folder_build
	rm -rf temp
	mkdir temp
	cd temp && qmake6 ../gui/desktop/snake
	cd temp && make
	mv temp/snake.app build
	rm -rf temp
########################################## Compiles
########################################## Gcov
gcov_report: clean
	$(CPP) $(CPP_FLAGS) brick_game/snake/model.cc tests/*.cc --coverage -o test -lgtest
	./test
	rm -rf max_score.txt
	lcov --no-external --ignore-errors mismatch,format,unsupported -c -d . --output-file coverage.info
	genhtml coverage.info --output-directory report/
	open report/index.html
	rm -rf max_score.txt *gcda *gcno *.info test
gcov_report_t: clean folder_lib $(GCOV_REPORT_DIR)
	$(CC) $(CC_FLAGS) $(GCOV_FLAGS) -c brick_game/tetris/*.c -o $(LIB_DIR)/s21_tetris.o
	ar rc $(LIB_DIR)/$(BACK_LIB_TETRIS) $(LIB_DIR)/*.o
	ranlib $(LIB_DIR)/$(BACK_LIB_TETRIS)
	rm -rf $(LIB_DIR)/*.o
	$(CC) $(CC_FLAGS) $(GCOV_FLAGS) ${TEST_SOURCES_T} $(LIB_DIR)/$(BACK_LIB_TETRIS) -o $(TESTS_DIR)/$(TEST_T) $(TEST_FLAGS)
	./$(TESTS_DIR)/$(TEST_T)
	lcov -t "$(FILENAME)" -o $(GCOV_REPORT_DIR)/$(FILENAME).info -c -d . --no-external
	genhtml -o report $(GCOV_REPORT_DIR)/$(FILENAME).info
	rm -rf $(TESTS_DIR)/*.dSYM $(TESTS_DIR)/*.gcda $(TESTS_DIR)/*.gcno $(TESTS_DIR)/*.o
	open report/index.html
########################################## Gcov
########################################## tetst
test_t: $(BACK_LIB_TETRIS)
	$(CC) $(CC_FLAGS) $(LIBS) $(TEST_SOURCES_T) $(LIB_DIR)/$(BACK_LIB_TETRIS) -o $(TESTS_DIR)/$(TEST_T) $(TEST_FLAGS) -lncurses
	./$(TESTS_DIR)/$(TEST_T)
test_s: $(BACK_LIB_SNAKE)
	$(CPP) $(CPP_FLAGS) ${TEST_SOURCES_S} $(LIB_DIR)/$(BACK_LIB_SNAKE) -o $(TESTS_DIR)/$(TEST_S) $(TEST_FLAGS_G)
	./$(TESTS_DIR)/$(TEST_S)
	rm -rf max_score.txt

test: clean test_t test_s
########################################## tests
########################################## DVI
dvi: docs
	doxygen Doxyfile
	# cd docs/latex && latex refman.tex
	# cd docs/latex && cp refman.dvi ../
	# cd docs/ && mv refman.dvi About_program.dvi
	open docs/html/index.html
########################################## DVI
########################################## dist
dist: clean dist_dir
		cp -rf brick_game/ $(DIST_DIR)/
		cp -rf gui/ $(DIST_DIR)/
		cp -rf $(TESTS_DIR)/ $(DIST_DIR)/
		cp -rf Makefile $(DIST_DIR)/
		tar -czf brickgame2.tar.gz ${DIST_DIR}/
		rm -rf $(DIST_DIR)/*
		mv brickgame2.tar.gz $(DIST_DIR)/
########################################## dist
########################################## main
install: clean $(TARGET_SNAKE_CLI) $(TARGET_TETRIS_CLI) $(DESKTOP_SNAKE_TETRIS)
uninstall: 
	rm -rf $(BIN_DIR)/*

clean:
	rm -rf $(BIN_DIR) $(LIB_DIR) $(DIST_DIR) $(GCOV_REPORT_DIR) docs/* $(TEST_T) tests/tetris_test $(DIST_DIR) *.gcda *.gcno *.info tests/snake_test* docs max_score* test gui/desktop/snake/build
########################################## main
$(GCOV_REPORT_DIR):
	mkdir $(GCOV_REPORT_DIR)
folder_build: 
	mkdir $(BIN_DIR)
folder_lib:
	mkdir $(LIB_DIR)
docs:
	mkdir docs
dist_dir :
	mkdir $(DIST_DIR)	