/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehay <ehay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:14:53 by ehay              #+#    #+#             */
/*   Updated: 2024/06/10 16:36:23 by ehay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_floor_celling(t_game_instance *game)
{
	int y;
	int x;
	
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while(y < WINDOW_HEIGHT)
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

void	fusion_img(t_game_instance *game)
{
	int x = 0;
	int y = 0;
	int ycub = WINDOW_HEIGHT - MINIMAP_HEIGHT;

	while (ycub < WINDOW_HEIGHT)
	{
		while (x < MINIMAP_WIDTH)
		{
			my_mlx_pixel_put(&game->cub3d, x, ycub, my_mlx_get_color(&game->miniMap, x, y));
			x++;
		}
		x = 0;
		y++;
		ycub++;
	}
}

int game_loop(void *ptr)
{
	t_game_instance *game;

	game = ptr;	
	move(game);
	put_floor_celling(game);
	check_raycasting(game);
	refresh_minimap(game);
	fusion_img(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->cub3d.img_ptr, 0, 0);
	usleep(2);
}

void	game(t_param *param)
{
	t_game_instance	game;

	game.map = param->map;
	ft_init_window(&game);
	game.color_c = param->color_c;
	game.color_f = param->color_f;
	game.mv_down = 0;
	game.mv_up = 0;
	game.mv_left = 0;
	game.mv_right = 0;
	game.rt_left = 0;
	game.rt_right = 0;
	game.player_x = (double)param->posx + 0.5;
	game.player_y = (double)param->posy + 0.5;
	get_vector(&game, param);
	game.cub3d.img_ptr = mlx_new_image(game.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	game.cub3d.data = mlx_get_data_addr(game.cub3d.img_ptr, &game.cub3d.bpp, &game.cub3d.size_l, &game.cub3d.endian);
	game.miniMap.img_ptr = mlx_new_image(game.mlx_ptr, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	game.miniMap.data = mlx_get_data_addr(game.miniMap.img_ptr, &game.miniMap.bpp, &game.miniMap.size_l, &game.miniMap.endian);
	mlx_loop_hook(game.mlx_ptr, game_loop, &game);
	mlx_loop(game.mlx_ptr);
}

int	is_cub(char *str)
{
	int	i;

	if (ft_strlen(str) < 4)
		return (0);
	i = 0;
	while (str[i])
		i++;
	i = i - 4;
	if (ft_strncmp(str + i, ".cub", 4))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_param	param;
	int	fd_cub;

	if (ac != 2)
		ft_error(1);
	if (!is_cub(av[1]))
		ft_error(2);
	fd_cub = open(av[1], O_RDONLY);
	if (fd_cub == -1)
		ft_error(3);
	if (check_file(&param, fd_cub))
		ft_error(4);
	game(&param);
}
