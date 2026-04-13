/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:00:08 by dviegas           #+#    #+#             */
/*   Updated: 2026/04/13 10:58:59 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_copy(char **copy, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}

char	**copy_map(t_map *map)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		copy[i] = ft_strdup(map->grid[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	flood_fill(char **map, int x, int y, t_map *data)
{
	if (x < 0 || y < 0 || x >= data->width || y >= data->height)
		return (0);
	if (map[y][x] == ' ')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (1);
	map[y][x] = 'V';
	if (!flood_fill(map, x + 1, y, data))
		return (0);
	if (!flood_fill(map, x - 1, y, data))
		return (0);
	if (!flood_fill(map, x, y + 1, data))
		return (0);
	if (!flood_fill(map, x, y - 1, data))
		return (0);
	return (1);
}

int	check_closed(t_game *game)
{
	int		x;
	int		y;
	char	**copy;
	int		valid;

	find_player(&game->map, &x, &y);
	copy = copy_map(&game->map);
	if (!copy)
	{
		clean_all(game);
		error_exit("Memory allocation failed in check_closed");
	}
	valid = flood_fill(copy, x, y, &game->map);
	free_copy(copy, game->map.height);
	return (valid);
}

void	validate_map(t_game *game)
{
	if (!check_chars(&game->map))
	{
		clean_all(game);
		error_exit("Invalid characters in map");
	}
	if (!check_player(&game->map))
	{
		clean_all(game);
		error_exit("Invalid number of players, only one player is valid");
	}
	if (!check_closed(game))
	{
		clean_all(game);
		error_exit("Map is not closed\n");
	}
}
