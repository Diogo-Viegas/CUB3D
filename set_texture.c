/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 19:10:57 by dviegas           #+#    #+#             */
/*   Updated: 2026/04/11 22:31:45 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

 void	cleanup_error(t_game *game, char **lines, char *msg)
{
	free_array(lines);
	clean_all(game);
	error_exit(msg);
}

static char	*extract_path(char *line, t_game *game, char **lines)
{
	char	*path;
	int		i;

	line = skip_spaces(line);
	if (*line == '\0')
		cleanup_error(game, lines, "Missing texture path");
	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	path = ft_substr(line, 0, i);
	if (!path)
		cleanup_error(game, lines, "Malloc Failed");
	if (*skip_spaces(line + i) != '\0')
	{
		free(path);
		cleanup_error(game, lines, "Invalid texture format");
	}
    if(!ends_with(path, ".xpm"))
    {
        free(path);
        cleanup_error(game, lines, "File must be .xpm");
    }
	return (path);
}


void	set_texture(t_game *game, char **dst, char *line, char **lines)
{
	if (*dst != NULL)
		cleanup_error(game, lines, "duplicate texture");
	*dst = extract_path(line, game, lines);
}