/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehay <ehay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:37:29 by ehay              #+#    #+#             */
/*   Updated: 2024/06/11 13:38:25 by ehay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error(int num_error)
{
	if (num_error == 1)
	{
		ft_putstr_fd("\033[96mError : \033[91mnot two args\033[0m\n", 2);
		ft_putstr_fd("\033[96mTry : \033[33m./cub3d <map>.cub\033[0m\n", 2);
	}
	if (num_error == 2)
	{
		ft_putstr_fd("\033[96mError : \033[91mnot a .cub file\033[0m\n", 2);
		ft_putstr_fd("\033[96mTry : \033[33m./cub3d <map>.cub\033[0m\n", 2);
	}
	if (num_error == 3)
	{
		ft_putstr_fd("\033[96mError : \033[91mcannot open this file\033[0m\n",
			2);
		ft_putstr_fd("\033[96mTry : \033[33m./cub3d <map>.cub\033[0m\n", 2);
	}
	if (num_error == 4)
	{
		ft_putstr_fd("\033[96mError : \033[91mnot a valid map\033[0m\n", 2);
		ft_putstr_fd("\033[96mTry : \033[33m./cub3d <map>.cub\033[0m\n", 2);
	}
	if (num_error == 89)
		ft_putstr_fd("\033[96mError : \033[91mMLX Library error\033[0m\n", 2);
	exit(1);
}

void	map_example(t_param *param, char *str)
{
	ft_putstr_fd("\033[96mError : \033[91m", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0m\n\n", 2);
	ft_putstr_fd("\033[95m   ↓  Example .cub map  ↓\033[0m\n", 1);
	ft_putstr_fd("\033[33mNO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\nF 220,100,300\nC 225,30,0\n\n1111111\n1001011\n1010011\n1100N11\n1111111\033[0m\n", 1);
	free_tab(param->file);
	if (param->map)
		free_tab(param->map);
	if (param->tex_e)
		free(param->tex_e);
	if (param->tex_w)
		free(param->tex_w);
	if (param->tex_s)
		free(param->tex_s);
	if (param->tex_n)
		free(param->tex_n);
	exit(1);
}
