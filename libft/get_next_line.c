/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:44:20 by dviegas           #+#    #+#             */
/*   Updated: 2026/04/07 14:33:42 by dviegas          ###   ########.fr       */
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

static char	*join_and_free(char *line, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(line, buffer);
	free(line);
	return (tmp);
}

static int	fill_buffer(int fd, char *buffer, char **line)
{
	int	bytes;

	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes <= 0)
	{
		if (bytes < 0)
			free(*line);
		return (bytes);
	}
	buffer[bytes] = '\0';
	return (bytes);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	while (ft_newline(line) == -1)
	{
		if (buffer[0] == '\0' && fill_buffer(fd, buffer, &line) <= 0)
			return (line);
		line = join_and_free(line, buffer);
		if (!line)
			return (NULL);
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
