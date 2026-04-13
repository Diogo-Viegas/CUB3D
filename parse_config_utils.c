/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:49:15 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/11 22:44:37 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "cub3d.h"

char	*trim_spaces(char *s)
{
	char	*end;
	char	*start;

	start = s;
	while (*start == ' ' || *start == '\t')
		start++;
	if (*start == '\0')
		return (ft_strdup(""));
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t'))
		end--;
	return (ft_substr(start, 0, end - start + 1));
}

static void	free_rgb(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
}

static void	trim_rgb_tokens(char **rgb)
{
	char	*trimmed;
	int		i;

	i = 0;
	while (i < 3)
	{
		trimmed = trim_spaces(rgb[i]);
		free(rgb[i]);
		rgb[i] = trimmed;
		i++;
	}
}

static int	validate_rgb(char **rgb)
{
	if (!is_valid_number(rgb[0]) || !is_valid_number(rgb[1])
		|| !is_valid_number(rgb[2]))
	{
		return (0);
	}
	return (1);
}

int	parse_color(char *line, char **lines, t_game *game)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	line = skip_spaces(line);
	rgb = ft_split(line, ',');
	if (!rgb || count_split(rgb) != 3)
		error_exit("Invalid color format");
	trim_rgb_tokens(rgb);
	if (!validate_rgb(rgb))
	{
		free_array(rgb);
		cleanup_error(game, lines, "Color Must Be a Number");
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_rgb(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		cleanup_error(game, lines, "Color value out of range [0,255]");
	return (r << 16 | g << 8 | b);
}
