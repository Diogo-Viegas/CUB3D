/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:45:16 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/12 13:17:09 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_file(t_game *game, t_map *map, char *filename)
{
	char	**lines;
	int		map_start;

	lines = read_file(filename);
	if (!lines)
		error_exit("Failed to read file\n");
	map_start = find_map_start(lines);
	parse_config(game, lines, map_start, map);
	printf("-----CONFIG------\n[NO] -> %s\n[SO] -> %s\n"
		"[WE] -> %s\n[EA] -> %s\n[FLOOR] -> %d\n[CEILING] -> %d\n",
		map->no,
		map->so,
		map->we,
		map->ea,
		map->floor,
		map->ceiling);
	if (!extract_map(lines, map_start, map))
	{
		free_array(lines);
		clean_all(game);
		error_exit("Allocation failed");
	}
	free_array(lines);
	validate_map(map,game);
	print_map(map);
}

char	*skip_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	starts_with(char *line, char *prefix)
{
	int	i;

	i = 0;
	line = skip_spaces(line);
	while (prefix[i])
	{
		if (line[i] != prefix[i])
			return (0);
		i++;
	}
	return (1);
}

int	ends_with(char *path, char *sufix)
{
	int	extension;
	int	i;

	extension = ft_strlen(path) - 4;
	i = 0;
	while (path[extension] != '\0' && sufix[i] == path[extension])
	{
		extension++;
		i++;
	}
	if ((int)ft_strlen(path) == extension)
		return (1);
	else
		return (0);
}
