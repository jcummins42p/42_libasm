/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:42:17 by jcummins          #+#    #+#             */
/*   Updated: 2025/09/26 16:32:13 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

int	test_strlen(const char *test)
{
	int	std_result;
	int	ft_result;

	std_result = strlen(test);
	ft_result = ft_strlen(test);
	printf("Testing ft_strlen against strlen from string.h...\n");
	set_result_color(std_result - ft_result);
	printf("\tLength of string \"%s\" with std strlen:\t%d\n", test,
		std_result);
	printf("\tLength of string \"%s\" with ft_strlen:\t%d\n", test, ft_result);
	reset_color();
	return (std_result == ft_result ? SUCCESS : FAIL_STRLEN);
}
