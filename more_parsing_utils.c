/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gocaetan <gocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:48:03 by gocaetan          #+#    #+#             */
/*   Updated: 2026/05/15 12:30:09 by gocaetan         ###   ########.fr       */
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

void	check_commas(t_game *game, char **lines, char *line)
{
	int		commas;
	char	*p;

	commas = 0;
	p = line;
	while (*p)
	{
		if (*p == ',')
			commas++;
		p++;
	}
	if (commas != 2)
		cleanup_error(game, lines, "Invalid color format");
	else
		return ;
}
