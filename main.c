/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:27:57 by jcummins          #+#    #+#             */
/*   Updated: 2025/09/19 12:03:34 by jcummins         ###   ########.fr       */
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

int test_write(void) {
	printf("Implement write() test here\n");
	return (1);
}

int test_read(void) {
	printf("Implement read() test here\n");
	return (1);
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
	return(result ? 1 : 0);
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
	result += test_strlen("Hello There");
	result += test_strcpy("Hello There") << 1;
	result += test_strcmp("", "ABC") << 2;
	result += test_write() << 3;
	result += test_read() << 4;
	result += test_strdup("Hello there") << 5;
	final_result(result);
	return 0;
}
