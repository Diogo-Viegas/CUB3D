/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:37:13 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/10 19:17:39 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_doors(t_game *game)
{
	if (game->doors)
	{
		free(game->doors);
		game->doors = NULL;
	}
	game->door_count = 0;
}
