/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:01:12 by jcummins          #+#    #+#             */
/*   Updated: 2025/09/26 15:54:19 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_H
# define LIBASM_H

# include <stdlib.h>	// abs
# include <string.h> // strlen, strcmp
# include <unistd.h> // read, write and default STDIN_FILENO
# include <stdio.h>	// printf
# include <fcntl.h>	// open
# include <errno.h>	// open

# define ANSI_COLOR_RED		"\x1b[31m"
# define ANSI_COLOR_GREEN	"\x1b[32m"
# define ANSI_COLOR_RESET	"\x1b[0m"

# define BUFSIZE 1000

enum
{
	SUCCESS,
	FAIL_STRLEN = 1u,
	FAIL_STRCPY = 1u << 1,
	FAIL_STRCMP = 1u << 2,
	FAIL_WRITE = 1u << 3,
	FAIL_READ = 1u << 4,
	FAIL_STRDUP = 1u << 5,
	FAIL_ATOI_BASE = 1u << 6,
	FAIL_LIST_PUSH_FRONT = 1u << 7,
	FAIL_LIST_SIZE = 1u << 8,
	FAIL_LIST_SORT = 1u << 9,
	FAIL_LIST_REMOVE_IF = 1u << 10
};

//	libasm declarations
int		ft_strlen(const char *str);
//	restrict guarantees unique pointer for the duration of the variable
//	allows the assembly to take fewer precautions to preserve values in case
//	of pointer aliasing
char	*ft_strcpy(char *restrict dst, char *restrict src);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_strdup(const char *s);
ssize_t	ft_write(int fd, const void *buf, size_t count);
ssize_t	ft_read(int fd, void *buf, size_t count);

//	test functions
void	set_result_color(int status);
void	reset_color(void);

int		test_strlen(const char *s);
int		test_strcpy(char *test);
int		test_strcmp(const char *s1, const char *s2);
int		test_write(const char *msg, size_t write_size);
int		test_write_autosize(const char *msg);
int		test_read_fd(int fd, char *buf,
			ssize_t (*read_fn)(int fd, void *buf, size_t count));
int		test_read_func(const char *filename, char *buf,
			ssize_t (*read_fn)(int fd, void *buf, size_t count));
int		test_read(const char *filename);
int		test_strdup(const char *s1);
void	list_failures(size_t result);
void	check_results(size_t result);

#endif
