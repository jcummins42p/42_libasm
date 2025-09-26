/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strcmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:17:11 by jcummins          #+#    #+#             */
/*   Updated: 2025/09/26 16:33:33 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

int	test_strcmp(const char *s1, const char *s2)
{
	int	std_result;
	int	ft_result;

	std_result = strcmp(s1, s2);
	ft_result = ft_strcmp(s1, s2);
	printf("Testing ft_strlen against strcmp using strings '%s' and '%s'\n",
		s1, s2);
	set_result_color(std_result - ft_result);
	printf("\tResult of std strcmp = %d\n", std_result);
	printf("\tResult of ft_strcmp = %d\n", ft_result);
	reset_color();
	return (std_result == ft_result ? SUCCESS : FAIL_STRCMP);
}
