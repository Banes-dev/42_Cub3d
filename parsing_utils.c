/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehay <ehay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:55:44 by mminet            #+#    #+#             */
/*   Updated: 2024/05/30 12:59:44 by ehay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

void	check_color(char *str, t_param *param)
{
	int	i;

	i = 0;
	if (!ft_isdigit(str[i]) || ft_atoi(str + i) > 255)
		map_example(param, "syntax1");
	while (ft_isdigit(str[i]))
		i++;
	if (!str[i] || str[i++] != ',')
		map_example(param, "syntax2");
	if (!ft_isdigit(str[i]) || ft_atoi(str + i) > 255)
		map_example(param, "syntax3");
	while (ft_isdigit(str[i]))
		i++;
	if (!str[i] || str[i++] != ',')
		map_example(param, "syntax4");
	if (!ft_isdigit(str[i]) || ft_atoi(str + i) > 255)
		map_example(param, "not r,g,b color");
	while (ft_isdigit(str[i]))
		i++;
	if (str[i])
		map_example(param, "syntax4");
}

int	get_color(char *str, t_param *param, char c)
{
	int	i;
	int	color;
	int	r;

	if ((c == 'C' && param->color_c != -1) || (c == 'F' && param->color_f != -1))
		map_example(param, "double color");
	i = 0;
	if (!is_isspace(str[i]))
		map_example(param, "syntax0");
	while (is_isspace(str[i]))
		i++;
	check_color(str + i, param);
	r = ft_atoi(str + i);
	color = (r & 0xff) << 16;
	while (ft_isdigit(str[i]))
		i++;
	i++;
	r = ft_atoi(str + i);
	color += (r & 0xff) << 8;
	while (ft_isdigit(str[i]))
		i++;
	i++;
	r = ft_atoi(str + i);
	color += (r & 0xff);
	return (color);
}
