/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:42:27 by mminet            #+#    #+#             */
/*   Updated: 2024/06/14 14:22:50 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	rotate(t_game_instance *game)
{
	double	tmp;
	double	tmp_plane;

	if (game->rt_right)
	{
		tmp = game->vector_x;
		game->vector_x = game->vector_x * cos(RS) - game->vector_y * sin(RS);
		game->vector_y = tmp * sin(RS) + game->vector_y * cos(RS);
		tmp_plane = game->plane_x;
		game->plane_x = game->plane_x * cos(RS) - game->plane_y * sin(RS);
		game->plane_y = tmp_plane * sin(RS) + game->plane_y * cos(RS);
	}
	if (game->rt_left)
	{
		tmp = game->vector_x;
		game->vector_x = game->vector_x * cos(-RS) - game->vector_y * sin(-RS);
		game->vector_y = tmp * sin(-RS) + game->vector_y * cos(-RS);
		tmp_plane = game->plane_x;
		game->plane_x = game->plane_x * cos(-RS) - game->plane_y * sin(-RS);
		game->plane_y = tmp_plane * sin(-RS) + game->plane_y * cos(-RS);
	}
}

void	rotate_mouse(t_game_instance *game)
{
	double	tmp;
	double	tmp_plane;
	float	rs;

	rs = (RS / 50) * (float)game->mouse_x;
	tmp = game->vector_x;
	tmp_plane = game->plane_x;
	if (game->mouse_x > 0)
	{
		game->vector_x = game->vector_x * cos(rs) - game->vector_y * sin(rs);
		game->vector_y = tmp * sin(rs) + game->vector_y * cos(rs);
		game->plane_x = game->plane_x * cos(rs) - game->plane_y * sin(rs);
		game->plane_y = tmp_plane * sin(rs) + game->plane_y * cos(rs);
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, WINDOW_WIDTH / 2,
			WINDOW_HEIGHT / 2);
	}
	else if (game->mouse_x < 0)
	{
		game->vector_x = game->vector_x * cos(rs) - game->vector_y * sin(rs);
		game->vector_y = tmp * sin(rs) + game->vector_y * cos(rs);
		game->plane_x = game->plane_x * cos(rs) - game->plane_y * sin(rs);
		game->plane_y = tmp_plane * sin(rs) + game->plane_y * cos(rs);
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, WINDOW_WIDTH / 2,
			WINDOW_HEIGHT / 2);
	}
}

void	move_side(t_game_instance *game)
{
	double	vx;
	double	vy;

	vx = (cos(M_PI_2) * game->vector_x - sin(M_PI_2) * game->vector_y);
	vy = (cos(M_PI_2) * game->vector_y + sin(M_PI_2) * game->vector_x);
	if (game->mv_right == 1)
	{
		if (game->map[(int)(game->player_y)][(int)(game->player_x + vx * MS
				* 3)] == '0')
			game->player_x += vx * MS;
		if (game->map[(int)(game->player_y + vy * MS
				* 3)][(int)(game->player_x)] == '0')
			game->player_y += vy * MS;
	}
	if (game->mv_left == 1)
	{
		if (game->map[(int)(game->player_y)][(int)(game->player_x - vx * MS
				* 3)] == '0')
			game->player_x -= vx * MS;
		if (game->map[(int)(game->player_y - vy * MS
				* 3)][(int)(game->player_x)] == '0')
			game->player_y -= vy * MS;
	}
}

void	move(t_game_instance *game)
{
	game->mouse_x -= WINDOW_WIDTH / 2;
	if (game->mouse_x == 0)
		rotate(game);
	else
		rotate_mouse(game);
	if (game->mv_up == 1)
	{
		if (game->map[(int)(game->player_y)][(int)(game->player_x
				+ game->vector_x * MS * 3)] == '0')
			game->player_x += game->vector_x * MS;
		if (game->map[(int)(game->player_y + game->vector_y * MS
				* 3)][(int)(game->player_x)] == '0')
			game->player_y += game->vector_y * MS;
	}
	if (game->mv_down == 1)
	{
		if (game->map[(int)(game->player_y)][(int)(game->player_x
				- game->vector_x * MS * 3)] == '0')
			game->player_x -= game->vector_x * MS;
		if (game->map[(int)(game->player_y - game->vector_y * MS
				* 3)][(int)(game->player_x)] == '0')
			game->player_y -= game->vector_y * MS;
	}
	move_side(game);
}
