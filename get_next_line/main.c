/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 13:15:18 by jlopez-c          #+#    #+#             */
/*   Updated: 2020/01/31 15:50:08 by jlopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/uio.h>
#include <sys/types.h>

int main ()
{
	char *x = (char *)malloc(sizeof(char) * 4096);
	char **p = &x;
	int fd = open("test_texts/texto.txt", O_RDONLY);
	int n;

	while ((n = get_next_line(fd, p)) > 0)
	{
		printf("Linea: %s\n", *p);
		free(*p);
	}
	if (n == 0)
		printf("Última linea: %s\n", *p);
	
	close(fd);
	return 0;
}
