/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:00:08 by dviegas           #+#    #+#             */
/*   Updated: 2026/03/26 12:39:03 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"


int is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == 'W' || c == 'N'|| c == 'S' || c == 'E' || c == ' ');
}
int is_player(char c)
{
    return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}
int check_chars(t_map *map)
{
    int i;
    int j;

    i = 0;
    while(i < map->height)
    {
        j = 0;
        while(j < map->width)
        {
            if(!is_valid_char(map->grid[i][j]))
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}
int check_player(t_map *map)
{
    int i;
    int j;
    int count;

    count = 0;
    i = 0;
    while(i < map->height)
    {
        j = 0;
        while(j < map->width)
        {
            if(is_player(map->grid[i][j]))
                count++;
            j++;
        }
        i++;
    }
    return (count == 1);
}
void find_player(t_map *map, int *x,int *y)
{
    int i;
    int j;
    i = 0;
    while(i < map->height)
    {
        j = 0;
        while(j < map->width)
        {
            if(is_player(map->grid[i][j]))
            {
                *x = i;
                *y = j;
                return; 
            }
            j++;
        }
        i++;
    }
}
char **copy_map(t_map *map)
{
    char **copy;
    int i;

    copy = malloc(sizeof(char *) * map->height);
    i = 0;
    while(i < map->height)
    {
        copy[i] = ft_strdup(map->grid[i]);
        i++;
    }
    return (copy);
}
int flood_fill(char **map,int x, int y,t_map *data)
{
    if(x < 0 || y < 0 || x >= data->height || y >= data->width)
        return (0);
    if(map[x][y] == ' ')
        return (0);
    if(map[x][y] == '1' || map[x][y] == 'V')
        return (1);
    map[x][y] = 'V';
    if(!flood_fill(map,x + 1,y,data))
        return (0);
    if(!flood_fill(map,x - 1,y,data))
        return (0);
    if(!flood_fill(map,x,y + 1,data))
        return (0);
    if(!flood_fill(map,x,y - 1,data))
        return (0);
    return (1);

}

int check_closed(t_map *map)
{
    int x;
    int y;
    char **copy;
    int valid;
    find_player(map,&x,&y);
    copy = copy_map(map);
    printf("[Player] -> [%d] [%d]\n",x,y);
    int i = 0;
    while(i < map->height)
    {
        printf("line -> %s\n",copy[i]);
        i++;
    }
    valid = flood_fill(copy,x,y,map);
    //free_map(map);
    return (valid);
}
int validate_map(t_map *map)
{
    if(!check_chars(map))
        error_exit("Invalid characters in map");
    if(!check_player(map))
        error_exit("Invalid number of players, only one player is valid");
    if(!check_closed(map))
        error_exit("Map is not closed\n");
    return (1);
}