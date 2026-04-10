/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:53:55 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/10 12:03:38 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "cub3d.h"

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
