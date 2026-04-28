#include "cub3d.h"

void	free_doors(t_game *game)
{
	if (game->doors)
	{
		free(game->doors);
		game->doors = NULL;
	}
	game->door_count = 0;
}