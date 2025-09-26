/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:18:44 by jcummins          #+#    #+#             */
/*   Updated: 2025/09/26 16:31:35 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

int	test_read_fd(int fd, char *buf, ssize_t (*read_fn)(int fd, void *buf,
			size_t count))
{
	int	bytes_read;

	bytes_read = (*read_fn)(fd, buf, BUFSIZE);
	if (bytes_read < 0)
	{
		set_result_color(FAIL_READ);
		printf("\tUnable to read fd %d: errno %d\n", fd, errno);
		reset_color();
		return (FAIL_READ);
	}
	buf[bytes_read] = 0;
	return (SUCCESS);
}

int	test_read_func(const char *filename, char *buf, ssize_t (*read_fn)(int fd,
			void *buf, size_t count))
{
	int	fd;

	fd = open(filename, O_RDONLY, 0);
	if (fd < 0)
	{
		set_result_color(FAIL_READ);
		printf("\tUnable to open file '%s': errno %d\n", filename, errno);
		reset_color();
		return (FAIL_READ);
	}
	test_read_fd(fd, buf, read_fn);
	return (SUCCESS);
}

int	test_read(const char *filename)
{
	int		result;
	char	std_buf[BUFSIZE + 1] = {0};
	char	ft_buf[BUFSIZE + 1] = {0};

	result = SUCCESS;
	printf("Testing ft_read against read from unistd.h with file '%s'...\n",
		filename);
	test_read_func(filename, ft_buf, ft_read);
	test_read_func(filename, std_buf, read);
	result = strcmp(std_buf, ft_buf);
	set_result_color(result);
	printf("\tunistd read: %s\n", std_buf);
	printf("\tft_read: %s\n", ft_buf);
	reset_color();
	return (result ? FAIL_READ : SUCCESS);
}
