/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:03:47 by dviegas           #+#    #+#             */
/*   Updated: 2026/04/10 12:09:45 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_config_line(char *line)
{
	line = skip_spaces(line);
	return (starts_with(line, "NO ") || starts_with(line, "SO ")
		|| starts_with(line, "WE ") || starts_with(line, "EA ")
		|| starts_with(line, "F ") || starts_with(line, "C "));
}

int	find_map_start(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		i++;
	i--;
	while (i >= 0 && is_empty_line(lines[i]))
		i--;
	while (i >= 0 && !is_config_line(lines[i]) && !is_empty_line(lines[i]))
		i--;
	return (i + 1);
}

void	trim_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

int	is_cub(char *file)
{
	return (ft_strnstr(file, ".cub", ft_strlen(file)) != NULL);
}
