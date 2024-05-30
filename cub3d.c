/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehay <ehay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:14:53 by ehay              #+#    #+#             */
/*   Updated: 2024/05/30 13:31:37 by ehay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game(t_param param)
{
	t_game_instance	game_init;

	(void)param;
	ft_init_window(&game_init);
	mlx_loop(game_init.mlx_ptr);
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
	if (check_file(param, fd_cub))
		ft_error(4);
	game(param);
}
