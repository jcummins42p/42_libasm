/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:27:57 by jcummins          #+#    #+#             */
/*   Updated: 2025/09/16 16:22:50 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	Simple main to demonstrate assembly coded library functions for libasm

#include <stdlib.h>	// abs
#include <string.h> // strlen, strcmp
#include <unistd.h>
#include <stdio.h>	// printf

#define ANSI_COLOR_RED		"\x1b[31m"
#define ANSI_COLOR_GREEN	"\x1b[32m"
#define ANSI_COLOR_RESET	"\x1b[0m"

enum {
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
int ft_strlen(const char *str);
//	restrict guarantees unique pointer for the duration of the variable
//	allows the assembly to take fewer precautions to preserve values in case
//	of pointer aliasing
char *ft_strcpy(char *restrict dst, char *restrict src);
int	ft_strcmp(const char *s1, const char *s2);

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

int test_strcmp(const char *s1, const char *s2) {
	int std_result = strcmp(s1,s2);
	int ft_result = ft_strcmp(s1,s2);

	printf("Testing ft_strlen against strcmp from string.h...\n");
	set_result_color(std_result - ft_result);
	printf("\tResult of std strcmp = %d\n", std_result);
	printf("\tResult of ft_strcmp = %d\n", ft_result);
	reset_color();
	return (std_result == ft_result ? 0 : 1);
}

int test_strlen(const char *test) {
	int std_result = strlen(test);
	int ft_result = ft_strlen(test);

	printf("Testing ft_strlen against strlen from string.h...\n");
	set_result_color(std_result - ft_result);
	printf("\tLength of string \"%s\" with std strlen:\t%d\n", test, std_result);
	printf("\tLength of string \"%s\" with ft_strlen:\t%d\n", test, ft_result);
	reset_color();
	return (std_result == ft_result ? 0 : 1);
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
	return (strcmp(ft_buf, std_buf) ? 1 : 0);
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

void final_result(size_t result) {
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
	size_t result = 0;

	printf("Testing assembly code for libasm project\n");
	result &= test_strlen("Hello There");
	result &= test_strcpy("Hello There");
	result &= test_strcmp("", "ABC");
	final_result(result);
	return 0;
}
