/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:14:50 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/13 10:59:40 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_game *game)
{
	clear_img(game->win_width, game->win_height, &game->screen);
	cast_rays(game);
	render_map(game);
	render_minimap_rays(game);
	render_player(game);
	render_player_direction(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img_ptr, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc < 2)
	{
		printf("Error: missing map file argument\nUsage: %s <map_file>\n",
			argv[0]);
		return (1);
	}
	init_game(&game);
	parse_file(&game,argv[1]);
	init_player(&game);
	init_mlx(&game);
	init_textures(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
