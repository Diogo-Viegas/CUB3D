/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gocaetan <gocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:37:13 by gocaetan          #+#    #+#             */
/*   Updated: 2026/05/15 12:30:35 by gocaetan         ###   ########.fr       */
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

void	error_exit(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

void	cleanup_exit(t_game *game, char **lines, char *msg)
{
	if (lines)
		free_array(lines);
	if (game)
		clean_all(game);
	error_exit(msg);
}
