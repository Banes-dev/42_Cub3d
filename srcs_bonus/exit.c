/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:25:16 by ehay              #+#    #+#             */
/*   Updated: 2024/06/13 03:06:11 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

// void	ft_free_img(t_game_instance *game_init)
// {
// 	mlx_destroy_image(game_init->mlx_ptr, game_init->game_objs.player_up);
// 	mlx_destroy_image(game_init->mlx_ptr, game_init->game_objs.player_left);
// 	mlx_destroy_image(game_init->mlx_ptr, game_init->game_objs.player_right);
// 	mlx_destroy_image(game_init->mlx_ptr, game_init->game_objs.player_down);
// 	mlx_destroy_image(game_init->mlx_ptr, game_init->game_objs.player_up2);
// 	mlx_destroy_image(game_init->mlx_ptr, game_init->game_objs.player_left2);
// 	mlx_destroy_image(game_init->mlx_ptr, game_init->game_objs.player_right2);
// 	mlx_destroy_image(game_init->mlx_ptr, game_init->game_objs.player_down2);
// 	mlx_destroy_image(game_init->mlx_ptr, game_init->game_objs.collectible);
// 	mlx_destroy_image(game_init->mlx_ptr, game_init->game_objs.ennemies);
// 	mlx_destroy_image(game_init->mlx_ptr, game_init->game_objs.exit_open);
// 	mlx_destroy_image(game_init->mlx_ptr, game_init->game_objs.exit_close);
// 	mlx_destroy_image(game_init->mlx_ptr, game_init->game_objs.wall);
// 	mlx_destroy_image(game_init->mlx_ptr, game_init->game_objs.floor);
// 	game_init->game_objs = (t_game_objs){0};
// }

// void	ft_cleanup(t_game_instance *game_init)
// {
// 	if (game_init->resolutions_init.settings_name_window != NULL)
// 	{
// 		free(game_init->resolutions_init.settings_name_window);
// 		game_init->resolutions_init.settings_name_window = NULL;
// 	}
// 	if (game_init->resolutions_init.settings_name_map != NULL)
// 	{
// 		free(game_init->resolutions_init.settings_name_map);
// 		game_init->resolutions_init.settings_name_map = NULL;
// 	}
// }

int	ft_exit_program(t_game_instance *game_init)
{
	ft_putstr_fd("\033[91m\n ⛔ Game stoped\033[95m by user\033[0m\n\n", 2);
	// ft_free_img(game_init);
	// ft_cleanup(game_init);
	mlx_destroy_image(game_init->mlx_ptr, game_init->tex[0].img.img_ptr);
	mlx_destroy_image(game_init->mlx_ptr, game_init->tex[1].img.img_ptr);
	mlx_destroy_image(game_init->mlx_ptr, game_init->tex[2].img.img_ptr);
	mlx_destroy_image(game_init->mlx_ptr, game_init->tex[3].img.img_ptr);
	mlx_destroy_image(game_init->mlx_ptr, game_init->miniMap.img_ptr);
	mlx_destroy_image(game_init->mlx_ptr, game_init->cub3d.img_ptr);
	mlx_destroy_window(game_init->mlx_ptr, game_init->win_ptr);
	mlx_destroy_display(game_init->mlx_ptr);
	free(game_init->mlx_ptr);
	free_tab(game_init->map);
	exit(0);
	return (0);
}
