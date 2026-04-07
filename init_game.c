/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gocaetan <gocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:40:00 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/07 18:14:40 by gocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(t_map *map)
{
	int	i;

	printf("--------------MAP--------------\n");
	printf("Height -> %d\n", map->height);
	printf("Width -> %d\n", map->width);
	i = 0;
	while (i < map->height)
	{
		printf("%s\n", map->grid[i]);
		i++;
	}
	printf("----------------------------------------\n");
}

void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->map.ceiling = -1;
	game->map.floor = -1;
}

void	set_player_dir(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
}

void	set_player_fov(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (dir == 'S')
	{
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (dir == 'W')
	{
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	else if (dir == 'E')
	{
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
}

void	init_player(t_game *game)
{
	int		y;
	int		x;
	char	dir;

	dir = find_player(&game->map, &x, &y);
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	set_player_dir(&game->player, dir);
	game->map.grid[y][x] = '0';
	set_player_fov(&game->player, dir);
	printf("[Player] -> [%0.2f] [%0.2f]\n", game->player.y, game->player.x);
	printf("[Player Dir x] -> %f\n", game->player.dir_x);
	printf("[Player Dir y] -> %f\n", game->player.dir_y);
	printf("[Player Fov x] -> %f\n", game->player.plane_x);
	printf("[Player Fov y] -> %f\n", game->player.plane_y);
}
