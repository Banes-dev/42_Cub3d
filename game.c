/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehay <ehay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:19:51 by ehay              #+#    #+#             */
/*   Updated: 2024/05/27 16:34:37 by ehay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_esc(int key, t_game_instance *game_init)
{
	if (key == ESC)
	{
		printf("\nGame ended, you are a noob.\n");
		ft_exit_program(game_init);
	}
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
	mlx_hook(game_init->win_ptr, 2, (1L << 0), ft_check_esc, game_init);
}
