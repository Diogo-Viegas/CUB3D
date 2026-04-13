/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:09:41 by dviegas           #+#    #+#             */
/*   Updated: 2026/04/13 13:05:44 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define TILE_SIZE 32
# define MINIMAP_SCALE 8
# define MINIMAP_OFFSET_X 10
# define MINIMAP_OFFSET_Y 10
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// #define malloc(x) (NULL)

typedef struct s_line
{
	float		x;
	float		y;
	float		x_inc;
	float		y_inc;
	int			steps;
}				t_line;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_keys;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor;
	int			ceiling;
}				t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	t_player	player;
	t_map		map;
	t_keys		keys;
	t_img		screen;
	t_img		texture_no;
	t_img		texture_so;
	t_img		texture_ea;
	t_img		texture_we;
}				t_game;

typedef struct s_ray
{
	double		ray_dir_x;
	double		ray_dir_y;
	double		camera_x;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		wall_dist;

	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;

	double		wallx;
	int			tex_x;
	double		step;
	double		tex_pos;
}				t_ray;

// parse_config.c
int				is_color_line(char *line);
int				is_texture_line(char *line);
void			parse_texture_line(t_game *game, char *line, char **lines);
void			parse_color_line(t_game *game, char *line, char **lines);
void			validate_config(t_game *game, char **lines);
void			parse_config(t_game *game, char **lines, int map_start);

// parse_config_utils.c
void			error_exit(char *msg);
char			*skip_spaces(char *line);
int				is_empty_line(char *line);
int				starts_with(char *line, char *prefix);
void			set_texture(t_game *game, char **dst, char *line, char **lines);
int				count_split(char **split);
int				parse_color(char *line, char **lines, t_game *game);
// extract_map.c
int				extract_map(char **lines, int start, t_map *map);
// read_line.c
char			**read_file(char *file);
int				find_map_start(char **lines);
// validate_map.c
void			validate_map(t_game *game);
char			find_player(t_map *map, int *x, int *y);
// init_game.c
void			parse_file(t_game *game, char *filename);
void			init_player(t_game *game);
void			init_game(t_game *game);
// init_mlx.c
void			init_mlx(t_game *game);
int				close_game(t_game *game);
int				esc_close(int keycode, t_game *game);
// image_utils
void			put_pixel(t_img *img, int x, int y, int color);
void			draw_square(t_img *img, t_point pos, int size, int color);
// keys.c
int				key_press(int keycode, t_game *game);
int				mouse_move_hook(int x, int y, t_game *game);

// raycasting.c
void			init_ray(t_ray *ray, t_game *game, int x);
void			clear_img(int width, int height, t_img *img);
void			init_dda(t_ray *ray, t_player *player);
void			perform_dda(t_ray *ray, t_game *game);
void			calc_dist(t_ray *ray);
void			draw_ray(t_img *img, t_player *player, t_ray *ray);
void			cast_rays(t_game *game);
void			draw_line(t_img *img, t_point start, t_point end, int color);
// render_3d.c
void			calc_wall_height(t_game *game, t_ray *ray);
// textures.c
void			calc_wall_x(t_game *game, t_ray *ray);
void			calc_texture_x(t_ray *ray, t_img *texture);
void			draw_textured_column(t_game *game, int x, t_ray *ray,
					t_img *texture);
t_img			*get_wall_texture(t_game *game, t_ray *ray);
void			init_textures(t_game *game);
// minimap.c
void			draw_ray_minimap(t_img *img, t_player *player, t_ray *ray);
void			render_minimap_rays(t_game *game);
void			render_map(t_game *game);
void			render_player(t_game *game);
void			render_player_direction(t_game *game);
// cleanup.c
void			clean_all(t_game *game);
void			free_array_with_index(char **arr, int i);
void			free_array(char **arr);
// read_file.c
int				count_lines(char *file);
int				is_valid_number(char *s);
int				check_chars(t_map *map);
int				check_player(t_map *map);
void			rotate_right(t_game *game, double angle);
void			rotate_left(t_game *game, double angle);
void			free_map_grid(t_map *map);
int				ends_with(char *path, char *sufix);
int				get_texture_pixel(t_img *img, int x, int y);
// read_file_utils.c
int				is_cub(char *file);
void			trim_newline(char *line);
int				find_map_start(char **lines);
int				is_config_line(char *line);
// set_texture.c
void			set_texture(t_game *game, char **dst, char *line, char **lines);
void			cleanup_error(t_game *game, char **lines, char *msg);
#endif