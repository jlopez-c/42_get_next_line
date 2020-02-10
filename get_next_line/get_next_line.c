/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-c <jlopez-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 11:40:50 by jlopez-c          #+#    #+#             */
/*   Updated: 2020/01/31 15:49:57 by jlopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static char		*all[4096];
	char			*buffer;
	char			*temp;
	int				bytes;
	
	buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1)
	bytes = read(fd, buffer, BUFFER_SIZE);
	
	//Comprobamos errores
	if (fd < 0 || BUFFER_SIZE <= 0 || !line || !buffer)
		return (-1)
	//Empezamos a introducir valores en la variable estatica
	while(bytes > 0)
	{
		//con esto nos aseguramos de que la cadena de buffer acaba en NULL
		buffer[bytes] = '\0'
		//como la primera vez la variable estatica estara vacia, la inicializamos con el valor de buffer
		if(all[fd] == NULL)
			all[fd] = ft_strdup(buffer);
		else
		{

		}

	}
	return (0)
}
