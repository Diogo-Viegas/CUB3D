/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:14:58 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/13 10:54:54 by dviegas          ###   ########.fr       */
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

void	parse_color_line(t_game *game,char *line,char **lines)
{
	line = skip_spaces(line);
	if (starts_with(line, "F "))
	{
		if (game->map.floor != -1)
			cleanup_error(game,lines,"Duplicate floor color");
		game->map.floor = parse_color(line +2,lines,game);
	}
	else if (starts_with(line, "C "))
	{
		if (game->map.ceiling != -1)
		{
			cleanup_error(game,lines,"Duplicate ceiling color");
		}
		game->map.ceiling = parse_color(line + 2,lines,game);
	}
}

void	validate_config(t_game *game,char **lines )
{
	if (!game->map.no || !game->map.so || !game->map.we || !game->map.ea)
		cleanup_error(game,lines,"Missing Textures");
	if (game->map.ceiling == -1 || game->map.floor == -1)
		cleanup_error(game,lines,"Missing Color");
}

void	parse_config(t_game *game, char **lines, int map_start)
{
	int	i;

	i = 0;
	while (i < map_start)
	{
		if (is_empty_line(lines[i]))
			;
		else if (is_texture_line(lines[i]))
			parse_texture_line(game, lines[i],lines);
		else if (is_color_line(lines[i]))
			parse_color_line(game,lines[i],lines);
		else
			cleanup_error(game,lines,"Invalid config line");
		i++;
	}
	validate_config(game,lines);
}
