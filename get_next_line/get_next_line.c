/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-c <jlopez-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 11:40:50 by jlopez-c          #+#    #+#             */
/*   Updated: 2020/02/19 18:46:14 by jlopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int 	i;
	char	*str;
	i = 0;
	if (!s)
		return (NULL);
	str = (char *)s;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	if (str[i] == (unsigned char)c)
			return (&str[i]);
	return (NULL);
}

void	ft_delete(char **all)
{
	if (all != NULL && *all != NULL)
	{
		free(*all);
		*all = NULL;
	}
}

int		ft_line(int fd, char **all, char **line)
{
	int		size;
	char	*temp;
	
	size = 0;
	while (all[fd][size] != '\n')
		size++;
	*line = ft_substr(all[fd], 0, size);
	temp = ft_strdup(&all[fd][size + 1]);
	free(all[fd]);
	all[fd] = temp;
	return (1);
}

int		ft_binary(int bytes, int fd, char **all, char **line)
{
	if (bytes < 0)
		return (-1);
	else if (ft_strchr(all[fd], '\n'))
		return (ft_line(fd, all, line));
	else if (bytes == 0 && (all[fd] == NULL || all[fd][0] == '\0'))
	{
		*line = ft_strdup("");
		ft_delete(&all[fd]);
		return (0);
	}
	else
	{
		*line = ft_strdup(all[fd]);
		ft_delete(&all[fd]);
		return (0);
	}
}

int		get_next_line(int fd, char **line)
{
	static char		*all[4096];
	char			*buffer;
	char			*temp;
	int				bytes;
	
	buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1);
	bytes = read(fd, buffer, BUFFER_SIZE);
	
	if (fd < 0 || BUFFER_SIZE <= 0 || !line || !buffer)
		return (-1);
	while(bytes > 0)
	{
		buffer[bytes] = '\0';
		if (all[fd] == NULL)
			all[fd] = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(all[fd], buffer);
			free(all[fd]);
			all[fd] = temp;
		}
		if (ft_strchr(all[fd], '\n'))
			break;
	}
	free(buffer);
	return (ft_binary(bytes, fd, all, line));
}
