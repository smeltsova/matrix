

CC = gcc

ASAN = #-fsanitize=address
CFLAGS = -c -g -Wall -Wextra -Werror -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
TEST_FLAGS = -lcheck
ifeq ($(shell uname), Linux)
TEST_FLAGS = -lcheck -lm -lpthread -lrt -lsubunit
endif

TEST_SRC_DIR = ./tests
TEST_OBJ_DIR = ./tests/objs
TEST_SRC:=$(shell find $(TEST_SRC_DIR) -name "*.c")
TEST_OBJS:=$(addprefix $(TEST_OBJ_DIR)/, $(notdir $(TEST_SRC:.c=.o)))

LIB_SRC:=$(shell find . -maxdepth 1 -name "*.c")
LIB_OBJS:=$(LIB_SRC:.c=.o)

TARGET=s21_matrix.a 


LIB_OBJS_GCOV:=$(LIB_SRC:.c=_gcov.o)

TARGET_GCOV=s21_matrix_gcov.a 

all: $(TARGET) test

$(TARGET): $(LIB_OBJS)
	ar rcs $(TARGET) $(LIB_OBJS)
	ranlib $(TARGET)

$(LIB_OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(ASAN) $< -o $@

test: clean $(TARGET) $(TEST_OBJS)
	$(CC) $(ASAN) $(TEST_OBJS) -o test $(TEST_FLAGS) -L. $(TARGET)
	./test

$(TEST_OBJS): $(TEST_OBJ_DIR)%.o: $(TEST_SRC_DIR)%.c
	mkdir -p $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) $(ASAN) $< -o $@

gcov_report: clean coverage.html open

coverage.html: gcov_test
	gcovr -r . --html-details -o coverage.html

gcov_test: $(TEST_OBJS) $(TARGET_GCOV)
	$(CC) $(TEST_OBJS) $(TARGET_GCOV) $(TEST_FLAGS) $(GCOV_FLAGS)  -o gcov_test
	./gcov_test

$(TARGET_GCOV): $(LIB_OBJS_GCOV)
	ar rcs $(TARGET_GCOV) $(LIB_OBJS_GCOV)
	ranlib $(TARGET_GCOV)

$(LIB_OBJS_GCOV): %_gcov.o: %.c
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(ASAN) $< -o $@

open:
	open coverage.html

clean:
	rm -rf *.o $(TARGET) test_$(TARGET) test gcov_test $(TEST_OBJ_DIR)/*.o *.gcno *.gcda *.gcov *gcov.a coverage* $(TEST_OBJ_DIR)/*.gcno  $(TEST_OBJ_DIR)/*.gcda  $(TEST_OBJ_DIR)/*.gcov *.gz
 
rebuild: clean all

valgrind: clean test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

check: test
	CK_FORK=no leaks --atExit -- ./test
	cppcheck --enable=all --suppress=missingIncludeSystem *.h *.c ./tests/*.c ./tests/*.h
	cp ../materials/linters/.clang-format .
	clang-format -n *.c ./tests/*.c
