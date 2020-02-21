/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 13:39:24 by jlopez-c          #+#    #+#             */
/*   Updated: 2020/02/21 15:27:17 by jlopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/uio.h>
#include <sys/types.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	int fd;
	int ret;
	int line;
	char *buff;
	int 	i;

	line = 0;
	if (argc > 1)
	{
		i = 0;
		while (++i < argc)
		{
			fd = open(argv[i], O_RDONLY);
			printf("%d- archivo: %s\n",i, argv[i]);
			while ((ret = get_next_line(fd, &buff)) > 0)
			{
				printf("[Return: %d] Line #%d: %s\n", ret, ++line, buff);
				free(buff);
			}
			printf("[Return: %d] Line #%d: %s\n", ret, ++line, buff);
			if (ret == -1)
				printf("-----------\nError\n");
			else if (ret == 0)
				printf("-----------\nEnd of file\n");
			free(buff);
		}
	}
	if (argc == 1)
	{
		printf("Necesito que me pases un fichero como parametro =)");
	}
	return (0);
}
