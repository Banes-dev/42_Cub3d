/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:09:08 by mminet            #+#    #+#             */
/*   Updated: 2024/06/04 18:02:41 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_input(t_param *param, int i, int j, char **map)
{
	if (map[i][j] == '0' || ft_strchr("NSEW", map[i][j]))
	{
		if (ft_strchr("NSEW", map[i][j]))
		{
			if (param->dir != -1)
				map_example(param, "double player");
			param->dir = map[i][j];
			map[i][j] = '0';
			param->posx = j;
			param->posy = i;
		}
		if (i == 0 || j == 0 || !map[i][j + 1] || !map[i + 1] || j > (int)ft_strlen(map[i + 1]) - 1 || j > (int)ft_strlen(map[i - 1]) - 1)
			map_example(param, "map ouverte");
		if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ' || map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
			map_example(param, "map ouverte");
	}
}

void	parse_map(t_param *param)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (param->map[i])
	{
		j = 0;
		while (param->map[i][j] && ft_strchr("SENW01 ", param->map[i][j]))
		{
			check_input(param, i, j, param->map);
			j++;
		}
		if (ft_strlen(param->map[i]) && param->map[i][j] != '\0')
			map_example(param, "wrong map");
		i++;
	}
	if (param->dir == -1)
		map_example(param, "no player");
}

void	fill_map(t_param *param, t_list **lst)
{
	int		len;
	t_list	*tmp;
	int		i;

	len = ft_lstsize(*lst);
	if (len == 0)
		return ;
	tmp = *lst;
	param->map = malloc(sizeof(char *) * (len + 1));
	param->map[len] = NULL;
	i = 0;
	while (tmp)
	{
		param->map[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	ft_lstclear(lst, simple_del);
}

void	check_map(t_param *param)
{
	t_list	*map;
	int		i;

	i = 0;
	map = NULL;
	while (param->file[i] && !ft_isdigit(param->file[i][0]) && !is_isspace(param->file[i][0]))
		i++;
	if (param->file[i] == NULL)
		map_example(param, "no map");
	while (param->file[i] && (ft_isdigit(param->file[i][0]) || is_isspace(param->file[i][0])))
	{
		ft_lstadd_back(&map, ft_lstnew(ft_strdup(param->file[i])));
		i++;
	}
	while (param->file[i] && param->file[i][0] == '\0')
		i++;
	if (param->file[i])
	{
		ft_lstclear(&map, simple_del);
		map_example(param, "wrong map");
	}
	else
		fill_map(param, &map);
	parse_map(param);
}
