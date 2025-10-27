/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:16:17 by jcummins          #+#    #+#             */
/*   Updated: 2025/10/27 14:18:14 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

int	test_strcpy(char *test)
{
	char	std_buf[4097] = {0};
	char	ft_buf[4097] = {0};

	printf("Testing ft_strcpy against strcpy from string.h...\n");
	strcpy(std_buf, test);
	ft_strcpy(ft_buf, test);
	set_result_color(strcmp(std_buf, ft_buf));
	printf("\tString copied by std strcpy:\t%s\n", std_buf);
	printf("\tString copied by ft_strcpy:\t%s\n", ft_buf);
	reset_color();
	return (strcmp(ft_buf, std_buf) ? FAIL_STRCPY : SUCCESS);
}
