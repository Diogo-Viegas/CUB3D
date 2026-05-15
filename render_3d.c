/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:15:46 by gocaetan          #+#    #+#             */
/*   Updated: 2026/05/15 10:34:10 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_wall_height(t_game *game, t_ray *ray)
{
	if (ray->wall_dist < 1e-6)
		ray->wall_dist = 1e-6;
	ray->line_height = (int)(game->win_height / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + game->win_height / 2;
	ray->draw_end = ray->line_height / 2 + game->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= game->win_height)
		ray->draw_end = game->win_height - 1;
}
