/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehay <ehay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:34:01 by mminet            #+#    #+#             */
/*   Updated: 2024/06/05 16:14:33 by ehay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_player(t_game_instance *game)
{
	int x;
	int y;
	float x0;
	float y0;

	x = (MINIMAP_WIDTH / 2)- 2;
	y = (MINIMAP_HEIGHT / 2) - 2;
	x0 = MINIMAP_WIDTH / 2;
	y0 = MINIMAP_HEIGHT / 2;
	while (y < (MINIMAP_HEIGHT / 2) + 2)
	{
		x = (MINIMAP_WIDTH / 2)- 2;
		while (x < (MINIMAP_WIDTH / 2) + 2)
		{
			my_mlx_pixel_put(&game->miniMap, x, y, 0xFFFF0000);
			x++;
		}
		y++;
	}

	x = (MINIMAP_WIDTH / 2)- 5;
	y = (MINIMAP_HEIGHT / 2) - 5;
	float expo = 0;
	while (expo < 7)
	{
		my_mlx_pixel_put(&game->miniMap, (int)((float)x0 + (game->vector_x * expo)), (int)((float)y0 + (game->vector_y * expo)), 0xFFFF0000);
		expo += 0.5;
	}
}

void	refresh_minimap(t_game_instance *game)
{
	int x;
	int y;
	double xmap;
	double ymap;
	double width = MINIMAP_WIDTH;
	double height = MINIMAP_HEIGHT;

	ymap = game->player_y - 16.0;
	y = 0;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0; 
		xmap = (game->player_x - 8.0);
		while (x < MINIMAP_WIDTH)
		{
			if ((int)xmap >= 0 && (int)ymap >= 0 && ft_tab_size(game->map) - 1 >= (int)ymap && ft_strlen(game->map[(int)ymap]) - 1 >= (int)xmap && game->map[(int)ymap][(int)xmap] == '1')
				my_mlx_pixel_put(&game->miniMap, x, y, 0x1b14e4);
			else
				my_mlx_pixel_put(&game->miniMap, x, y, 0x82cce8);
			x++;
			xmap = (game->player_x - 8.0) + ((16.0 / width) * x);
		}
		y++;
		ymap = (game->player_y - 8.0) + ((16.0 / height) * y);
	}
	put_player(game);
}
