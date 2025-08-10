/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:27:57 by jcummins          #+#    #+#             */
/*   Updated: 2025/08/10 17:03:43 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	Simple main to demonstrate assembly coded library functions for libasm

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int ft_strlen(const char *str);

int main(void) {
	char *message = "Testing assembly code for libasm project\n";
	write(1, message, strlen(message));
	printf("Length of message with strlen is %d\n", (int)strlen(message));
	printf("Length of message with ft_strlen is %d\n", (int)ft_strlen(message));
}
