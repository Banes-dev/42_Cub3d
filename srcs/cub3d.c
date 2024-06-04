/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:14:53 by ehay              #+#    #+#             */
/*   Updated: 2024/06/04 14:06:37 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int game_loop(void *ptr)
{
	t_game_instance *game;

	game = (t_game_instance*)ptr;
	if (game->mv_up && game->map[(int)(game->player_y - 0.3)][(int)game->player_x] != '1')
		game->player_y -= 0.01;
	if (game->mv_down && game->map[(int)(game->player_y + 0.3)][(int)game->player_x] != '1')
		game->player_y += 0.01;
	if (game->mv_left && game->map[(int)game->player_y][(int)(game->player_x - 0.3)] != '1')
		game->player_x -= 0.01;
	if (game->mv_right && game->map[(int)game->player_y][(int)(game->player_x + 0.3)] != '1')
		game->player_x += 0.01;
	refresh_minimap(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->miniMap.img_ptr, 0, WINDOW_HEIGHT - MINIMAP_HEIGHT);
}

void	game(t_param *param)
{
	t_game_instance	game;

	game.map = param->map;
	ft_init_window(&game);
	game.mv_down = 0;
	game.mv_up = 0;
	game.mv_left = 0;
	game.mv_right = 0;
	game.player_x = (double)param->posx + 0.5;
	game.player_y = (double)param->posy + 0.5;
	get_vector(&game, param);
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
