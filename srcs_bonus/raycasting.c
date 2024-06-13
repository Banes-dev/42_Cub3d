/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:49:35 by ehay              #+#    #+#             */
/*   Updated: 2024/06/13 03:12:18 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	get_step(t_game_instance *game, int map_x, int map_y)
{
	if (game->ray_dir_x < 0)
	{
		game->step_x = -1;
		game->side_dist_x = (game->player_x - map_x) * game->delta_dist_x;
	}
	else
	{
		game->step_x = 1;
		game->side_dist_x = (map_x + 1.0 - game->player_x) * game->delta_dist_x;
	}
	if (game->ray_dir_y < 0)
	{
		game->step_y = -1;
		game->side_dist_y = (game->player_y - map_y) * game->delta_dist_y;
	}
	else
	{
		game->step_y = 1;
		game->side_dist_y = (map_y + 1.0 - game->player_y) * game->delta_dist_y;
	}
}

void	cast_ray(t_game_instance *game, int *map_x, int *map_y)
{
	while (1)
	{
		if (game->side_dist_x < game->side_dist_y)
		{
			game->side_dist_x = game->side_dist_x + game->delta_dist_x;
			*map_x = *map_x + game->step_x;
			game->sideofwall = 0;
		}
		else
		{
			game->side_dist_y = game->side_dist_y + game->delta_dist_y;
			*map_y = *map_y + game->step_y;
			game->sideofwall = 1;
		}
		if ((game->map[*map_y][*map_x]) == '1')
			break ;
	}
}

void	get_wall_dist(t_game_instance *game, int map_x, int map_y, int x)
{
	double	wall_dist;
	int		line_height;

	wall_dist = 0;
	if (game->sideofwall == 0)
		wall_dist = (map_x - game->player_x + (1 - game->step_x) / 2)
			/ game->ray_dir_x;
	else
		wall_dist = (map_y - game->player_y + (1 - game->step_y) / 2)
			/ game->ray_dir_y;
	line_height = (int)(WINDOW_HEIGHT / wall_dist);
	fill_line(game, x, line_height, wall_dist);
}

int	check_raycasting(t_game_instance *game)
{
	int	x;
	int	map_x;
	int	map_y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		map_x = (int)game->player_x;
		map_y = (int)game->player_y;
		game->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		game->ray_dir_x = game->vector_x + game->plane_x * game->camera_x;
		game->ray_dir_y = game->vector_y + game->plane_y * game->camera_x;
		game->delta_dist_x = fabs(1 / game->ray_dir_x);
		game->delta_dist_y = fabs(1 / game->ray_dir_y);
		get_step(game, map_x, map_y);
		cast_ray(game, &map_x, &map_y);
		get_wall_dist(game, map_x, map_y, x);
		x++;
	}
	return (0);
}
