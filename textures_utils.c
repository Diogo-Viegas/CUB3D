/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:53:28 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/13 10:48:03 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(t_game *game, t_img *tex, char *path)
{
	tex->img_ptr = mlx_xpm_file_to_image(game->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img_ptr)
	{
		clean_all(game);
		error_exit("Texture not Found");
	}
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
	{
		clean_all(game);
		error_exit("Error getting texture addr");
	}
}

void	init_textures(t_game *game)
{
	load_texture(game, &game->texture_no, game->map.no);
	load_texture(game, &game->texture_so, game->map.so);
	load_texture(game, &game->texture_ea, game->map.ea);
	load_texture(game, &game->texture_we, game->map.we);
}

void	parse_texture_line(t_game *game, char *line, char **lines)
{
	line = skip_spaces(line);
	if (starts_with(line, "NO "))
		set_texture(game, &game->map.no, line + 2, lines);
	else if (starts_with(line, "SO "))
		set_texture(game, &game->map.so, line + 2, lines);
	else if (starts_with(line, "WE "))
		set_texture(game, &game->map.we, line + 2, lines);
	else if (starts_with(line, "EA "))
		set_texture(game, &game->map.ea, line + 2, lines);
	else
		error_exit("Invalid texture identifier");
}

int	get_texture_pixel(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}
