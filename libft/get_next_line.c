/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:44:20 by dviegas           #+#    #+#             */
/*   Updated: 2026/03/23 11:54:29 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_cleanread(char *line, char *buffer)
{
	size_t	i;
	int		sign;

	i = 0;
	sign = ft_newline(line);
	if (sign != -1)
	{
		line[sign + 1] = '\0';
		sign = ft_newline(buffer);
		sign++;
		while (buffer[sign])
			buffer[i++] = buffer[sign++];
	}
	while (i < BUFFER_SIZE)
		buffer[i++] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	while (ft_newline(line) == -1)
	{
		if (buffer[0] == '\0')
		{
			bytes = read(fd, buffer, BUFFER_SIZE);
			if (bytes <= 0)
			{
				if (bytes == 0)
					return (line);
				free(line);
				return (NULL);
			}
			buffer[bytes] = '\0';
		}
		line = ft_strjoin(line, buffer);
		ft_cleanread(line, buffer);
	}
	return (line);
}

// #include <errno.h>
// #include <fcntl.h>
// #include <stdlib.h>
// #include <string.h>

// int	main(void)
// {
// 	int		fd;
// 	int		i;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Erro ao abrir o arquivo");
// 		return (1);
// 	}
// 	i = 1;
// 	while (i < 68)
// 	{
// 		line = get_next_line(fd);
// 		printf("output %d = %s \n", i, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// }
