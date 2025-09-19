# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/09 22:55:48 by jcummins          #+#    #+#              #
#    Updated: 2025/09/19 12:46:56 by jcummins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libasm.a

TEST = main.c

SRCS = 	ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s

OBJS = $(SRCS:.s=.o)

CC = gcc
CFLAGS = -O1 -g -Werror -Wextra -Wall

# GNU ar archive program
AR = ar
AFLAGS = -rcs	# r = replace files in archive, c = create archive, s = ranlib

NASM = nasm	#netwide assembler, uses Intel syntax
NFLAGS = -f elf64 -w+all

all: $(NAME)

# to compile the test .c main with the assembly library
# -L specifies a full library path to link library. -l looks in library folders
test: all
	$(CC) $(CFLAGS) $(TEST) -L. -l:$(NAME) -o test.out
	./test.out

nopie: all
	$(CC) $(CFLAGS) -no-pie $(TEST) -L. -l:$(NAME) -o nopie.out
	./nopie.out

# to create the library from .o object files
$(NAME): $(OBJS)
	$(AR) $(AFLAGS) $@ $?

%.o: %.s
	$(NASM) $(NFLAGS) $< -o $@

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME) a.out
	rm -f ./test.out

re: fclean all

.PHONY: re fclean clean all
