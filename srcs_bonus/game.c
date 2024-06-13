/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:19:51 by ehay              #+#    #+#             */
/*   Updated: 2024/06/13 20:26:06 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	ft_check_esc(int key, t_game_instance *game)
{
	if (key == ESC)
		ft_exit_program(game);
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

int	open_texture(t_game_instance *game, t_param *param)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	game->tex[0].img.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			param->tex_n, &game->tex[0].width, &game->tex[0].height);
	game->tex[1].img.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			param->tex_s, &game->tex[1].width, &game->tex[1].height);
	game->tex[2].img.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			param->tex_e, &game->tex[2].width, &game->tex[2].height);
	game->tex[3].img.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			param->tex_w, &game->tex[3].width, &game->tex[3].height);
	while (i <= 3)
	{
		if (game->tex[i].img.img_ptr == NULL || game->tex[i].height < 10
			|| game->tex[i].height != game->tex[i].width)
			a = 1;
		else
			game->tex[i].img.data = mlx_get_data_addr(game->tex[i].img.img_ptr,
					&game->tex[i].img.bpp, &game->tex[i].img.size_l,
					&game->tex[i].img.endian);
		i++;
	}
	return (a);
}

void	ft_error_texture(t_game_instance *game, t_param *param)
{
	int	i;

	i = 0;
	while (i <= 3)
	{
		if (game->tex[i].img.img_ptr != NULL)
			mlx_destroy_image(game->mlx_ptr, game->tex[i].img.img_ptr);
		i++;
	}
	mlx_destroy_display(game->mlx_ptr);
	free_tab(game->map);
	free(game->mlx_ptr);
	ft_putstr_fd("\033[96mError : \033[91mnot a valid texture\033[0m\n", 2);
	ft_putstr_fd("\033[96mexample: tex.xpm (must be a square)\033[0m\n", 1);
	free(param->tex_e);
	free(param->tex_n);
	free(param->tex_s);
	free(param->tex_w);
	exit(1);
}

void	ft_init_window(t_game_instance *game_init, t_param *param)
{
	game_init->mlx_ptr = mlx_init();
	if (game_init->mlx_ptr == NULL)
		ft_error(89);
	if (open_texture(game_init, param))
		ft_error_texture(game_init, param);
	game_init->win_ptr = mlx_new_window(game_init->mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT, "Cub3d in the desert");
	if (game_init->win_ptr == NULL)
		ft_error(89);
	free(param->tex_e);
	free(param->tex_n);
	free(param->tex_s);
	free(param->tex_w);
	mlx_hook(game_init->win_ptr, 17, 0, ft_exit_program, game_init);
	mlx_hook(game_init->win_ptr, 3, (1L << 1), key_release, game_init);
	mlx_hook(game_init->win_ptr, 2, (1L << 0), ft_check_esc, game_init);
}
