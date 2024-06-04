/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:19:51 by ehay              #+#    #+#             */
/*   Updated: 2024/06/04 17:29:40 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_check_esc(int key, t_game_instance *game)
{
	if (key == ESC)
	{
		printf("\nGame ended, you are a noob.\n");
		ft_exit_program(game);
	}
	if (key == RIGHT)
		game->rt_right = 1;
	if (key == LEFT)
		game->rt_left = 1;
	if (key == W)
		game->mv_up = 1;
	if (key == S)
		game->mv_down = 1;
	if (key == A)
		game->mv_left = 1;
	if (key == D)
		game->mv_right = 1;
	return (0);
}

int	key_release(int key, t_game_instance *game)
{
	if (key == RIGHT)
		game->rt_right = 0;
	if (key == LEFT)
		game->rt_left = 0;
	if (key == W)
		game->mv_up = 0;
	if (key == S)
		game->mv_down = 0;
	if (key == A)
		game->mv_left = 0;
	if (key == D)
		game->mv_right = 0;
	return (0);
}

void	ft_init_window(t_game_instance *game_init)
{
	game_init->mlx_ptr = mlx_init();
	if (game_init->mlx_ptr == NULL)
		ft_error(89);
	game_init->win_ptr = mlx_new_window(game_init->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d in the desert");
	if (game_init->win_ptr == NULL)
		ft_error(89);
	// check si X ou Echap est fait on exit
	mlx_hook(game_init->win_ptr, 17, 0, ft_exit_program, game_init);
	mlx_hook(game_init->win_ptr, 3, (1L << 1), key_release, game_init);
	mlx_hook(game_init->win_ptr, 2, (1L << 0), ft_check_esc, game_init);
}
