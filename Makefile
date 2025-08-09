# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/09 22:55:48 by jcummins          #+#    #+#              #
#    Updated: 2025/08/09 23:32:15 by jcummins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libasm.a

SRCS = main.c

COBJS = main.o

ASMS = 	ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s

AOBJS = $(ASMS:.c=.o)

CC = gcc
CFLAGS = -o1

NASM = nasm

$(NAME): $(AOBJS) $(COBJS)	#linking object files functions and c main
	$(CC) $(CFLAGS) -o $@ $(AOBJS) $(COBJS)

$(COBJS): $(SRCS)	#compile c files into object files
	$(CC) $(CFLAGS) -o $@ $(SRCS)

%.o: %.s
	$(NASM) $(ASMS) -o $@
