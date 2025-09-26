/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:19:30 by jcummins          #+#    #+#             */
/*   Updated: 2025/09/26 16:32:03 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

int	test_strdup(const char *s1)
{
	char	*s2;
	int		result;

	s2 = ft_strdup(s1);
	result = strcmp(s1, s2);
	printf("Testing ft_strdup against strdup from string.h...\n");
	set_result_color(result);
	printf("\tOriginal string at address %p = %s\n", s1, s1);
	printf("\tDuplicated string %p = %s\n", s2, s2);
	reset_color();
	free(s2);
	return (s2 == NULL || result ? FAIL_STRDUP : SUCCESS);
}
