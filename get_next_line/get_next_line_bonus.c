/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:44:37 by jlopez-c          #+#    #+#             */
/*   Updated: 2020/02/21 18:44:51 by jlopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
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
	if (fd < 0 || BUFFER_SIZE <= 0 || !line || !buffer)
		return (-1);
	while ((bytes = read(fd, buffer, BUFFER_SIZE)) > 0)
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
			break ;
	}
	free(buffer);
	return (ft_binary(bytes, fd, all, line));
}
