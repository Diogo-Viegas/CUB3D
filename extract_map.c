#include "./libft/libft.h"
#include "cub3d.h"

int	get_map_height(char **lines, int start)
{
	int	i;

	i = start;
	while (lines[i])
		i++;
	return (i - start);
}

int	get_max_width(char **lines, int start)
{
	int	i;
	int	max;
	int	len;

	i = start;
	max = 0;
	while (lines[i])
	{
		len = ft_strlen(lines[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

// todas as linhas tem o mesmo tamanho atraves do padding com espacos
char	*create_padded_line(char *line, int width)
{
	char	*new;
	int		i;

	new = malloc(sizeof(char) * (width + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (line[i])
	{
		new[i] = line[i];
		i++;
	}
	while (i < width)
	{
		new[i] = ' ';
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	extract_map(char **lines, int start, t_map *map)
{
	int	i;
	int	j;

	map->height = get_map_height(lines, start);
	map->width = get_max_width(lines, start);
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (0);
	i = 0;
	j = start;
	while (i < map->height)
	{
		map->grid[i] = create_padded_line(lines[j], map->width);
		if (!map->grid[i])
		{
			free_array_with_index(map->grid, i);
			return (0);
		}
		i++;
		j++;
	}
	map->grid[i] = NULL;
	return (1);
}
