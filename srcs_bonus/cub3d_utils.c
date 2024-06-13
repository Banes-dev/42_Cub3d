/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:51:36 by mminet            #+#    #+#             */
/*   Updated: 2024/06/13 16:28:14 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	fusion_img(t_game_instance *game)
{
	int	x;
	int	y;
	int	ycub;

	x = 0;
	y = 0;
	ycub = 0;
	while (ycub < MINIMAP_HEIGHT)
	{
		while (x < MINIMAP_WIDTH)
		{
			my_mlx_pixel_put(&game->cub3d, x, ycub,
				my_mlx_get_color(&game->minimap, x, y));
			x++;
		}
		x = 0;
		y++;
		ycub++;
	}
}

int	my_mlx_get_color(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->data + (y * data->size_l + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->data + (y * data->size_l + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	simple_del(void *del)
{
	if (del)
		free(del);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
