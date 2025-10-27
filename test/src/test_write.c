/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:18:01 by jcummins          #+#    #+#             */
/*   Updated: 2025/10/27 14:10:45 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

int	test_write_fd(int fd, const char *msg, size_t write_size)
{
	int	std_result;
	int	ft_result;

	std_result = 0;
	ft_result = 0;
	printf("Testing write to fd %d with length %ld and string '%s'\n", fd, write_size, msg);
	printf("\tUnistd write:\t");
	fflush(NULL);
	std_result = write(fd, msg, write_size);
	printf("\n\tft_write:\t");
	fflush(NULL);
	ft_result = ft_write(fd, msg, write_size);
	set_result_color(std_result - ft_result);
	printf("\n\tWrite test success\n");
	reset_color();
	return (std_result == ft_result ? SUCCESS : FAIL_WRITE);
}

int	test_write(const char *msg, size_t write_size)
{
	int	std_result;
	int	ft_result;

	std_result = 0;
	ft_result = 0;
	printf("Testing write with length %ld and string '%s'\n", write_size, msg);
	printf("\tUnistd write:\t");
	fflush(NULL);
	std_result = write(STDOUT_FILENO, msg, write_size);
	printf("\n\tft_write:\t");
	fflush(NULL);
	ft_result = ft_write(STDOUT_FILENO, msg, write_size);
	set_result_color(std_result - ft_result);
	printf("\n\tWrite test success\n");
	reset_color();
	return (std_result == ft_result ? SUCCESS : FAIL_WRITE);
}

int	test_write_autosize(const char *msg)
{
	return (test_write(msg, strlen(msg)));
}
