#!/usr/bin/make -f

COLOR_RED="\033[0;31m"
COLOR_GREEN="\033[0;32m"
COLOR_YELLOW="\033[0;33m"
COLOR_RESET="\033[0m"

NAME=smartcalc
HEADERS_DIR = includes
HEADERS_FILES=\
	$(NAME).h \
	dlist.h \
	renderer.h \
	microui.h

SRCS_DIR=src

SRCS_FILES_FOR_TEST=\
	shunting_yard.c \
	dlist.c \
	rpn.c \
	utils.c \
	calc_credit.c \
	calc_deposit.c
	
SRCS_NOT_TEST = main.c gui.c renderer.c microui.c
SRCS_FILES=$(SRCS_FOR_TEST) $(SRCS_NOT_TEST)


SRCS_FOR_TEST=$(addprefix $(SRCS_DIR)/, $(SRCS_FILES_FOR_TEST))
SRCS=$(SRCS_FOR_TEST) $(addprefix $(SRCS_DIR)/, $(SRCS_NOT_TEST))

HEADERS = $(addprefix $(HEADERS_DIR)/, $(HEADERS_FILES))
OBJ=$(SRCS:.c=.o)
OBJ_FOR_TEST=$(SRCS_FOR_TEST:.c=.o)
INCLUDES=-I./includes
TEST_INCLUDES_DIR=tests/includes
TEST_INCLUDES=$(TEST_INCLUDES_DIR)/tests.h

TEST_DIR=tests
TEST_NAME=test.out
TEST_FILES=test_calculation.c \
		test_main.c \
		test_deposit.c
TEST_SRCS=$(addprefix $(TEST_DIR)/$(SRCS_DIR)/, $(TEST_FILES))
TEST_OBJS=$(TEST_SRCS:%.c=%.o)

REPORT_NAME=report.html

FLAGS=-std=c11 -Wall -Wextra -Werror -pedantic `sdl2-config --libs` -lGL -lm -O3 -g
CC=gcc 
CC_GCOV=gcc -Wall -Wextra -Werror -std=c11 \
-fcf-protection=full -static-libgcc --coverage -lgcov
THREADS = 8

all:
	$(MAKE) -j$(THREADS) $(NAME)

gcov_report: CC=$(CC_GCOV)
gcov_report: fclean test
	./$(TEST_NAME)
	gcovr -r . -f src --html -o $(REPORT_NAME)

multi:
	$(MAKE) -j$(THREADS) all

test: $(TEST_NAME)

$(TEST_NAME): $(NAME) $(TEST_OBJS)
	$(CC) $(TEST_OBJS) $(OBJ_FOR_TEST) -o $@ -lcheck -lm -lpthread -lrt -lsubunit

$(TEST_DIR)/%.o:$(TEST_DIR)/%.c $(TEST_INCLUDES)
	$(CC) -I./$(TEST_DIR)/includes -I./includes -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@ $(FLAGS)
	
	@echo -n $(COLOR_GREEN)
	@echo =================================
	@echo $(NAME) HAS BEEN MADE       
	@echo =================================	
	@echo -n $(COLOR_RESET)

%.o:%.c $(HEADERS)
	@$(CC) $(INCLUDES) -c $< -o $@
	@echo $<


		
clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f $(TEST_OBJS)
	find . -name "*.gcda" -type f -delete
	find . -name "*.gcno" -type f -delete
	/bin/rm -f $(REPORT_NAME)
fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(TEST_NAME)
re: fclean all



.PHONY: lib clean fclean all re multi

INSTALLATION_DIRECTORY=/opt/smartcalc/v1.0

PHONY: all, install, uninstall, clean, distclean, mostyclean, realclean, TAGS, info, dvi, dist, test, gcov_report
#all, clean, test, s21_matrix.a, gcov_report