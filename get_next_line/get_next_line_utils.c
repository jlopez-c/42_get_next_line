/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlopez-c <jlopez-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 11:41:01 by jlopez-c          #+#    #+#             */
/*   Updated: 2020/02/21 15:27:12 by jlopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	int		i;

	i = 0;
	if (s1 && s2)
	{
		str = (char*)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
		if (!str)
			return (NULL);
		while (*s1)
			str[i++] = *s1++;
		while (*s2)
			str[i++] = *s2++;
		str[i] = '\0';
		return (str);
	}
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char *ptr;

	ptr = (unsigned char*)s;
	while (n-- > 0)
		*ptr++ = 0;
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (s)
	{
		if (!(str = (char*)malloc(sizeof(char) * (int)len + 1)))
			return (NULL);
		ft_bzero(str, len);
		if (start <= ft_strlen(s))
		{
			while (i < len && s[i])
			{
				str[i] = s[i + start];
				i++;
			}
		}
		if (len < i + 1)
			str[i] = '\0';
		return (str);
	}
	return (0);
}
