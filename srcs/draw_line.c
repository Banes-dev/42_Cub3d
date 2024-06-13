/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 01:54:27 by mminet            #+#    #+#             */
/*   Updated: 2024/06/13 03:19:45 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_floor_celling(t_game_instance *game)
{
	int	y;
	int	x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			if (y < WINDOW_HEIGHT / 2)
				my_mlx_pixel_put(&game->cub3d, x, y, game->color_c);
			else
				my_mlx_pixel_put(&game->cub3d, x, y, game->color_f);
			y++;
		}
		x++;
	}
}

void	get_texx(t_game_instance *game, double wall_dist)
{
	float	x_wall;

	game->id = 0;
	if (game->sideofwall == 0 && game->ray_dir_x < 0)
		game->id = 3;
	else if (game->sideofwall == 0)
		game->id = 2;
	if (game->sideofwall == 1 && game->ray_dir_y < 0)
		game->id = 0;
	else if (game->sideofwall == 1)
		game->id = 1;
	if (game->sideofwall == 0)
		x_wall = game->player_y + wall_dist * game->ray_dir_y;
	else
		x_wall = game->player_x + wall_dist * game->ray_dir_x;
	game->x_text = (int)(x_wall * (double)game->tex[game->id].width);
	if (game->x_text < 0)
		game->x_text *= -1;
}

void	fill_line(t_game_instance *game, int x, int line_height,
		double wall_dist)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	start = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (end >= WINDOW_HEIGHT)
		end = WINDOW_HEIGHT - 1;
	get_texx(game, wall_dist);
	game->y_text = 0;
	while (i + start <= end)
	{
		game->y_text = abs(((((start + i) * 256 - WINDOW_HEIGHT * 128 + line_height
							* 128) * game->tex[game->id].height) / line_height)
				/ 256);
		my_mlx_pixel_put(&game->cub3d, x, start + i,
			my_mlx_get_color(&game->tex[game->id].img, (int)game->x_text
				% game->tex[game->id].height, (int)game->y_text
				% game->tex[game->id].height));
		i++;
	}
}
