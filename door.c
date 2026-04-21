/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gocaetan <gocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 12:43:45 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/21 12:56:00 by gocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_door_open(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (game->doors[i].is_open);
		i++;
	}
	return (0);
}

void	open_door(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
		{
			game->doors[i].is_open = !game->doors[i].is_open;
			return ;
		}
		i++;
	}
}

void	count_doors(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == 'D')
				game->door_count++;
			x++;
		}
		y++;
	}
}

void	init_doors(t_game *game)
{
	int	y;
	int	x;
	int	i;

	count_doors(game);
	game->doors = malloc(sizeof(t_door) * game->door_count);
	if (!game->doors)
		error_exit("Malloc error doors");
	i = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == 'D')
			{
				game->doors[i].x = x;
				game->doors[i].y = y;
				game->doors[i++].is_open = 0;
			}
			x++;
		}
		y++;
	}
}

int	is_blocked(t_game *game, int x, int y)
{
	char	tile;

	tile = game->map.grid[y][x];
	if (tile == '1')
		return (1);
	if (tile == 'D')
	{
		if (!is_door_open(game, x, y))
			return (1);
	}
	return (0);
}
