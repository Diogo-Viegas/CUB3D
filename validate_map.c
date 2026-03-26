/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:00:08 by dviegas           #+#    #+#             */
/*   Updated: 2026/03/26 11:18:17 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


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
int validate_map(t_map *map)
{
    if(!check_chars(map))
        error_exit("Invalid characters in map");
    if(!check_player(map))
        error_exit("Invalid number of players, only one player is valid");
    //if(!check_closed(map))
        //error_exit("Map is not closed\n");
    return (1);
}