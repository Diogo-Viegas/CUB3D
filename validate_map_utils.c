/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gocaetan <gocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:00:00 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/17 14:55:40 by gocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'W' || c == 'N' || c == 'S' || c == 'E'
		|| c == ' ' || c == 'D');
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

int	check_chars(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (!is_valid_char(map->grid[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_player(t_map *map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (is_player(map->grid[i][j]))
				count++;
			j++;
		}
		i++;
	}
	return (count == 1);
}

char	find_player(t_map *map, int *x, int *y)
{
	int	row;
	int	col;

	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			if (is_player(map->grid[row][col]))
			{
				*x = col;
				*y = row;
				return (map->grid[*y][*x]);
			}
			col++;
		}
		row++;
	}
	return ('0');
}
