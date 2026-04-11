/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:14:58 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/11 23:04:19 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "cub3d.h"

int	is_color_line(char *line)
{
	return (starts_with(line, "F ") || starts_with(line, "C "));
}

int	is_texture_line(char *line)
{
	return (starts_with(line, "NO ") || starts_with(line, "SO ")
		|| starts_with(line, "WE ") || starts_with(line, "EA "));
}

void	parse_color_line(char *line,char **lines, t_map *map,t_game *game)
{
	line = skip_spaces(line);
	if (starts_with(line, "F "))
	{
		if (map->floor != -1)
			cleanup_error(game,lines,"Duplicate floor color");
		map->floor = parse_color(line +2,lines,game);
	}
	else if (starts_with(line, "C "))
	{
		if (map->ceiling != -1)
		{
			cleanup_error(game,lines,"Duplicate ceiling color");
		}
		map->ceiling = parse_color(line + 2,lines,game);
	}
}

void	validate_config(t_map *map,t_game *game,char **lines )
{
	if (!map->no || !map->so || !map->we || !map->ea)
		cleanup_error(game,lines,"Missing Textures");
	if (map->ceiling == -1 || map->floor == -1)
		cleanup_error(game,lines,"Missing Color");
}

void	parse_config(t_game *game, char **lines, int map_start, t_map *map)
{
	int	i;

	i = 0;
	while (i < map_start)
	{
		if (is_empty_line(lines[i]))
			;
		else if (is_texture_line(lines[i]))
			parse_texture_line(game, lines[i], map, lines);
		else if (is_color_line(lines[i]))
			parse_color_line(lines[i],lines, map,game);
		else
			cleanup_error(game,lines,"Invalid config line");
		i++;
	}
	validate_config(map,game,lines);
}
