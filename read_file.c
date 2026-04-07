/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gocaetan <gocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:53:55 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/07 18:38:43 by gocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "cub3d.h"

int	is_config_line(char *line)
{
	line = skip_spaces(line);
	return (starts_with(line, "NO ") || starts_with(line, "SO ")
		|| starts_with(line, "WE ") || starts_with(line, "EA ")
		|| starts_with(line, "F ") || starts_with(line, "C "));
}

int	find_map_start(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		i++;
	i--;
	while (i >= 0 && is_empty_line(lines[i]))
		i--;
	while (i >= 0 && !is_config_line(lines[i]) && !is_empty_line(lines[i]))
		i--;
	return (i + 1);
}

void	trim_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

int	is_cub(char *file)
{
	return (ft_strnstr(file, ".cub", ft_strlen(file)) != NULL);
}

// Parti em duas
static void	fill_lines(char **lines, int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		trim_newline(line);
		lines[i++] = line;
		line = get_next_line(fd);
	}
	lines[i] = NULL;
}

char	**read_file(char *file)
{
	int		fd;
	int		count;
	char	**lines;

	if (!is_cub(file))
		error_exit("File must have .cub extension");
	count = count_lines(file);
	if (count == 0)
		error_exit("File is empty");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open file at read file");
	lines = malloc(sizeof(char *) * (count + 1));
	if (!lines)
		error_exit("Malloc failed");
	fill_lines(lines, fd);
	close(fd);
	return (lines);
}
