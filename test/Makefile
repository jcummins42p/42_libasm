# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/26 14:08:54 by jcummins          #+#    #+#              #
#    Updated: 2025/10/27 14:50:37 by jcummins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Makefile for tests only - not required by subject

NAME = test.out

HEADDIR = include/
LIB = libasm.a
LIBDIR = ..

SRCS = 	main.c \
		test_strlen.c \
		test_strcpy.c \
		test_strcmp.c \
		test_write.c \
		test_read.c \
		test_strdup.c
SRC_DIR = src/

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = obj/

CC = gcc
CFLAGS = -O1 -g -Werror -Wextra -Wall

all: $(NAME)
	./$(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Iinclude -L$(LIBDIR) -l:$(LIB) -o $(NAME)
	chmod 000 files/nopermissions.txt

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -Iinclude -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)
	chmod 400 files/nopermissions.txt

re: fclean all

.PHONY: re fclean clean all
