/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gocaetan <gocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:45:03 by dviegas           #+#    #+#             */
/*   Updated: 2026/04/07 15:36:59 by gocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map_grid(t_map *map)
{
	int	i;

	if (!map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		map->grid[i] = NULL;
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

void	free_array_with_index(char **arr, int i)
{
	while (--i >= 0)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
// ft_substr em set_texture()
void	free_map_textures(t_map *map)
{
	if (map->no)
	{
		free(map->no);
		map->no = NULL;
	}
	if (map->so)
	{
		free(map->so);
		map->so = NULL;
	}
	if (map->ea)
	{
		free(map->ea);
		map->ea = NULL;
	}
	if (map->we)
	{
		free(map->we);
		map->we = NULL;
	}
}
// destroi as texturas vindas da minilbx
static void	destroy_texture(t_game *game, t_img *tex)
{
	if (tex->img_ptr)
	{
		mlx_destroy_image(game->mlx, tex->img_ptr);
		tex->img_ptr = NULL;
	}
}
void	clean_all(t_game *game)
{
	if (game->mlx)
	{
		destroy_texture(game, &game->texture_no);
		destroy_texture(game, &game->texture_so);
		destroy_texture(game, &game->texture_ea);
		destroy_texture(game, &game->texture_we);
		if (game->screen.img_ptr)
		{
			mlx_destroy_image(game->mlx, game->screen.img_ptr);
			game->screen.img_ptr = NULL;
		}
		if (game->win)
		{
			mlx_destroy_window(game->mlx, game->win);
			game->win = NULL;
		}
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	free_map_grid(&game->map);
	free_map_textures(&game->map);
}
