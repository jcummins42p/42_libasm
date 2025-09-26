/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:27:57 by jcummins          #+#    #+#             */
/*   Updated: 2025/09/26 16:15:34 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	Simple main to demonstrate assembly coded library functions for libasm
//	Not required by subject or required to follow norminette

#include "libasm.h"

//	Pass an expression that should equal 0 on success
void	set_result_color(int status)
{
	if (status == SUCCESS)
		printf(ANSI_COLOR_GREEN);
	else
		printf(ANSI_COLOR_RED);
}

void	reset_color(void)
{
	printf(ANSI_COLOR_RESET);
}

void	list_failures(size_t result)
{
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

void	check_results(size_t result)
{
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
int	main(void)
{
	size_t	result = SUCCESS;

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
