/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gocaetan <gocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:48:03 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/07 18:14:13 by gocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i] != NULL)
		i++;
	return (i);
}

int	is_valid_number(char *s)
{
	s = skip_spaces(s);
	if (!*s)
		return (0);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

void	error_exit(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

void	set_texture(char **dst, char *line)
{
	char	*path;
	int		i;

	if (*dst != NULL)
	{
		error_exit("duplicate texture");
	}
	line = skip_spaces(line);
	if (*line == '\0')
		error_exit("Missing texture path");
	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	path = ft_substr(line, 0, i);
	if (!path)
		printf("Malloc Failed\n");
	line += i;
	line = skip_spaces(line);
	if (*line != '\0')
		error_exit("Invalid Texture format");
	if (!ends_with(path, ".xpm"))
		error_exit("Texture must be .xpm");
	*dst = path;
}

int	count_lines(char *file)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open file at count liness");
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}
