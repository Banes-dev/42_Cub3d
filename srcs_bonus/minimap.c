/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:34:01 by mminet            #+#    #+#             */
/*   Updated: 2024/06/13 03:11:51 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	put_dir(t_game_instance *game, float centrex, float centrey, int lenx)
{
	float	expo;
	float	vx;
	float	vy;
	int		x;
	int		nbr_rayon;

	vy = (cos(M_PI_2) * game->vector_y + sin(M_PI_2) * game->vector_x);
	vx = (cos(M_PI_2) * game->vector_x - sin(M_PI_2) * game->vector_y);
	centrex -= vx * (float)(lenx / 5);
	centrey -= vy * (float)(lenx / 5);
	nbr_rayon = MINIMAP_WIDTH / 40;
	x = -1;
	while (x++ < nbr_rayon)
	{
		expo = 0;
		while (expo < (float)(lenx) / 1.2)
		{
			my_mlx_pixel_put(&game->miniMap, (int)((float)centrex
					+ (game->vector_x * expo)), (int)((float)centrey
					+ (game->vector_y * expo)), 0xFFFFFF);
			expo += 0.5;
		}
		centrex += vx * (float)(lenx / (nbr_rayon * 2));
		centrey += vy * (float)(lenx / (nbr_rayon * 2));
	}
}

void	put_player(t_game_instance *game)
{
	int	x;
	int	y;
	int	leny;
	int	lenx;
	int	centrex;
	int	centrey;

	leny = MINIMAP_HEIGHT / 15;
	lenx = MINIMAP_WIDTH / 15;
	centrex = MINIMAP_WIDTH / 2;
	centrey = MINIMAP_HEIGHT / 2;
	put_dir(game, centrex, centrey, lenx);
	y = centrey - (leny / 2);
	while (y < centrey + (leny / 2))
	{
		x = centrex - (lenx / 2);
		while (x < centrex + (lenx / 2))
		{
			if (((x - centrex) * (x - centrex) + ((centrey - y) * (centrey
							- y))) < (lenx * leny) / 5)
				my_mlx_pixel_put(&game->miniMap, x, y, 0xFFFF0000);
			x++;
		}
		y++;
	}
}

void	refresh_minimap(t_game_instance *game)
{
	int		x;
	int		y;
	double	xmap;
	double	ymap;

	ymap = game->player_y - 8.0;
	y = -1;
	while (y++ < MINIMAP_HEIGHT)
	{
		x = 0;
		xmap = (game->player_x - 4.0);
		while (x < MINIMAP_WIDTH)
		{
			if ((int)xmap >= 0 && (int)ymap >= 0 && ft_tab_size(game->map)
				- 1 >= (int)ymap && (int)ft_strlen(game->map[(int)ymap])
				- 1 >= (int)xmap && game->map[(int)ymap][(int)xmap] == '1')
				my_mlx_pixel_put(&game->miniMap, x, y, 0x1b14e4);
			else
				my_mlx_pixel_put(&game->miniMap, x, y, game->color_f);
			xmap = (game->player_x - 4.0) + ((8.0 / (double)(MINIMAP_WIDTH))
					* x++);
		}
		ymap = (game->player_y - 4.0) + ((8.0 / (double)(MINIMAP_HEIGHT)) * y);
	}
	put_player(game);
}
