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

//La primera parte de esta funcion nos devuelve la size de la linea hasta que encontramos un salto
//Para despues añadir en la variable line con la funcion substr, tantos caracteres como size hayamos indicado.
//ya le esstamos cambiando el valor por referencia a la variable estatica.
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

//Esta funcion tiene que controlar dependiendo de la situacion del archivo que vamos a leer un 1 si continua habiendo lineas para leer, o un 0 en caso de que haya llegado al final.
int		ft_binary(int bytes, int fd, char **all, char **line)
{
	if (bytes < 0)
		return (-1);
	//En caso de de que no hayamos llegado al final, tenemos que retornar 1.
	else if (ft_strchr(all[fd], '\n'))
		return (ft_line(fd, all, line));
	//En caso de que el numero oobtenido por read sea 0, y que la variable estatica este vacia y solo contenga el final de documento '\0'.
	//Vaciamos line, invocamos a la funcion delete y retornamos 0.
	else if (bytes == 0 && (all[fd] == NULL || all[fd][0] == '\0'))
	{
		*line = ft_strdup("");
		ft_delete(&all[fd]);
		return (0);
	}
	// La diferencia entre este else y el anterior es que este aun tiene characteres leidos en la ultima pasada, los cuales inserta en line
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
	
	//Comprobamos errores
	if (fd < 0 || BUFFER_SIZE <= 0 || !line || !buffer)
		return (-1);
	//Empezamos a introducir valores en la variable estatica
	while(bytes > 0)
	{
		//con esto nos aseguramos de que la cadena de buffer acaba en NULL
		buffer[bytes] = '\0';
		//como la primera vez la variable estatica estara vacia, la inicializamos con el valor de buffer
		if (all[fd] == NULL)
			all[fd] = ft_strdup(buffer);
		//Aqui vamos añadiendo en cada pasada de la funcion lo leido por read en la static
		else
		{
			temp = ft_strjoin(all[fd], buffer);
			free(all[fd]);
			all[fd] = temp;
		}
		//Obligamos a parar la ejecucion en caso de que encontremos un salto de linea.
		if (ft_strchr(all[fd], '\n'))
			break;
	}
	free(buffer);
	//Necesitamos controlar la salida y por tanto creamos una funcion en el return.
	return (ft_binary(bytes, fd, all, line));
}
