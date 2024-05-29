/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:55:44 by mminet            #+#    #+#             */
/*   Updated: 2024/05/29 17:18:52 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_example(t_param *param, char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\nExample .cub file :\n", 1);
	ft_putstr_fd("NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\nF 220,100,300\nC 225,30,0\n\n1111111\n1001011\n1010011\n1100N11\n1111111\n",
		1);
	free_tab(param->file);
	if (param->map)
		free_tab(param->map);
	if (param->tex_E)
		free(param->tex_E);
	if (param->tex_W)
		free(param->tex_W);
	if (param->tex_S)
		free(param->tex_S);
	if (param->tex_N)
		free(param->tex_N);
	exit(0);
}

int	is_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

void	check_color(char *str, t_param *param)
{
	int i = 0;

	if (!ft_isdigit(str[i]) || ft_atoi(str + i) > 255)
		map_example(param, "error: syntax1\n");
	while(ft_isdigit(str[i]))
		i++;
	if (!str[i] || str[i++] != ',')
		map_example(param, "error: syntax2\n");
	if (!ft_isdigit(str[i])|| ft_atoi(str + i) > 255)
		map_example(param, "error: syntax3\n");
	while(ft_isdigit(str[i]))
		i++;
	if (!str[i] || str[i++] != ',')
		map_example(param, "error: syntax4\n");
	if (!ft_isdigit(str[i])|| ft_atoi(str + i) > 255)
		map_example(param, "error: not r,g,b color\n");
	while(ft_isdigit(str[i]))
		i++;
	if (str[i])
		map_example(param, "error: syntax4\n");
}

int	get_color(char *str, t_param *param, char c)
{
	int i;
	int color;
	int r;

	if ((c == 'C' && param->color_C != -1) || (c == 'F' && param->color_F != -1))
		map_example(param, "error: double color\n");
	i = 0;
	if (!is_isspace(str[i]))
		map_example(param, "error: syntax0\n");
	while (is_isspace(str[i]))
		i++;
	check_color(str + i, param);
	r = ft_atoi(str + i);
	color = (r & 0xff) << 16;
	while(ft_isdigit(str[i]))
		i++;
	i++;
	r = ft_atoi(str + i);
	color += (r & 0xff) << 8;
	while(ft_isdigit(str[i]))
		i++;
	i++;
	r = ft_atoi(str + i);
	color += (r & 0xff);
	return (color);
}
