/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:27:57 by jcummins          #+#    #+#             */
/*   Updated: 2025/09/25 11:48:59 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	Simple main to demonstrate assembly coded library functions for libasm
//	Not required by subject or required to follow norminette

#include "libasm.h"

//	Pass an expression that should equal 0 on success
void set_result_color(int failed) {
	if (failed)
		printf(ANSI_COLOR_RED);
	else
		printf(ANSI_COLOR_GREEN);
}

void reset_color(void) {
	printf(ANSI_COLOR_RESET);
}

int test_strlen(const char *test) {
	int std_result = strlen(test);
	int ft_result = ft_strlen(test);

	printf("Testing ft_strlen against strlen from string.h...\n");
	set_result_color(std_result - ft_result);
	printf("\tLength of string \"%s\" with std strlen:\t%d\n", test, std_result);
	printf("\tLength of string \"%s\" with ft_strlen:\t%d\n", test, ft_result);
	reset_color();
	return (std_result == ft_result ? SUCCESS : FAIL_STRLEN);
}

int test_strcpy(char *test) {
	char std_buf[1024];
	char ft_buf[1024];

	printf("Testing ft_strcpy against strcpy from string.h...\n");
	strcpy(std_buf, test);
	ft_strcpy(ft_buf, test);
	set_result_color(strcmp(std_buf, ft_buf));
	printf("\tString copied by std strcpy:\t%s\n", std_buf);
	printf("\tString copied by ft_strcpy:\t%s\n", ft_buf);
	reset_color();
	return (strcmp(ft_buf, std_buf) ? FAIL_STRCPY : SUCCESS);
}

int test_strcmp(const char *s1, const char *s2) {
	int std_result = strcmp(s1,s2);
	int ft_result = ft_strcmp(s1,s2);

	printf("Testing ft_strlen against strcmp from string.h using strings '%s' and '%s'\n", s1, s2);
	printf("Note that valgrind causes std strcmp to behave differently\n");
	set_result_color(std_result - ft_result);
	printf("\tResult of std strcmp = %d\n", std_result);
	printf("\tResult of ft_strcmp = %d\n", ft_result);
	reset_color();
	return (std_result != ft_result ? FAIL_STRCMP : SUCCESS);
}

int test_write(const char *msg, size_t write_size) {
	int std_result = 0;
	int ft_result = 0;
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
	return (std_result - ft_result ? FAIL_WRITE : SUCCESS);
}

int test_write_autosize(const char *msg) {
	return (test_write(msg, strlen(msg)));
}

int test_read_fd(int fd, char *buf, ssize_t (*read_fn)(int fd, void *buf, size_t count)) {
	int bytes_read = (*read_fn)(fd, buf, BUFSIZE);
	if (bytes_read < 0) {
		set_result_color(FAIL_READ);
		printf("\tUnable to read fd %d: errno %d\n", fd, errno);
		reset_color();
		return(FAIL_READ);
	}
	buf[bytes_read] = 0;
	return(SUCCESS);
}

int test_read_func(const char *filename, char *buf, ssize_t (*read_fn)(int fd, void *buf, size_t count)) {
	int fd = open(filename, O_RDONLY, 0);

	if (fd < 0) {
		set_result_color(FAIL_READ);
		printf("\tUnable to open file '%s': errno %d\n", filename, errno);
		reset_color();
		return(FAIL_READ);
	}
	test_read_fd(fd, buf, read_fn);
	return(SUCCESS);
}

int test_read(const char *filename) {
	int result = SUCCESS;
	char std_buf[BUFSIZE + 1] = {0};
	char ft_buf[BUFSIZE + 1] = {0};

	printf("Testing ft_read against read from unistd.h with file '%s'...\n", filename);
	test_read_func(filename, ft_buf, ft_read);
	test_read_func(filename, std_buf, read);
	result |= strcmp(std_buf, ft_buf);
	set_result_color(result);
	printf("\tunistd read: %s\n", std_buf);
	printf("\tft_read: %s\n", ft_buf);
	reset_color();
	return (result ? FAIL_READ : SUCCESS);
}

int test_strdup(const char *s1) {
	char *s2 = ft_strdup(s1);
	int result = strcmp(s1,s2);

	printf("Testing ft_strdup against strdup from string.h...\n");
	set_result_color(result);
	printf("\tOriginal string at address %p = %s\n", s1, s1);
	printf("\tDuplicated string %p = %s\n", s2, s2);
	reset_color();
	free (s2);
	return(s2 == NULL || result ? FAIL_STRDUP : SUCCESS);
}

void list_failures(size_t result) {
	printf("Test failed:\n");
	if (result & FAIL_STRLEN)
		printf("\tstrlen\n");
	if (result & FAIL_STRCPY)
		printf("\tstrcpy\n");
	if (result & FAIL_STRCMP)
		printf("\tstrcmp\n");
	if (result & FAIL_WRITE)
		printf("\twrite\n");
	if (result & FAIL_READ)
		printf("\tread\n");
	if (result & FAIL_STRDUP)
		printf("\tstrdup\n");
	if (result & FAIL_ATOI_BASE)
		printf("\tatoi_base\n");
	if (result & FAIL_LIST_PUSH_FRONT)
		printf("\tlist_push_front\n");
	if (result & FAIL_LIST_SIZE)
		printf("\tlist_size\n");
	if (result & FAIL_LIST_SORT)
		printf("\tlist_sort\n");
	if (result & FAIL_LIST_REMOVE_IF)
		printf("\tlist_remove_if\n");
}

void check_results(size_t result) {
	set_result_color(result);
	if (result)
		list_failures(result);
	else
		printf("Test passed all cases\n");
	reset_color();
}

//	Change arguments in function calls under main to try out edge cases
//	Results stored in bitmask - 0 for success, 1 for failure
//	See enum to see which bits reflect which tests
int main(void) {
	size_t result = SUCCESS;

	printf("Testing assembly code for libasm project\n");
	result |= test_strlen("Hello There");
	result |= test_strcpy("Hello There");
	result |= test_strcmp("ABD", "ABC");
	result |= test_strcmp("A", "ABC");
	result |= test_strcmp("ABC", "");
	result |= test_strcmp("", "");
	result |= test_strcmp("", "A");
	result |= test_strcmp("A", "");
	result |= test_write_autosize("Hello World Write!");
	result |= test_write("Hello World Write!", 5);
	result |= test_write("Hello World Write!", 0);
	result |= test_read("test.txt");
	 result |= test_read("nofile.txt");
	 result |= test_read("nopermissions.txt");
	result |= test_strdup("Hello there");
	check_results(result);
	return (result);
}
