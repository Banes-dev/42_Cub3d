/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:22:01 by mminet            #+#    #+#             */
/*   Updated: 2024/05/31 14:11:54 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_texture(char *str, char **img, t_param *param)
{
	int	i;

	i = 0;
	if (*img)
		map_example(param, "double texture");
	if (!is_isspace(str[i]))
		map_example(param, "syntax");
	while (is_isspace(str[i]))
		i++;
	if (!str[i])
		map_example(param, "syntax");
	*img = ft_strdup(str + 1);
}

void	get_param(char *str, t_param *param)
{
	if (ft_strncmp(str, "NO", 2) == 0)
		get_texture(str + 2, &param->tex_n, param);
	else if (ft_strncmp(str, "SO", 2) == 0)
		get_texture(str + 2, &param->tex_s, param);
	else if (ft_strncmp(str, "WE", 2) == 0)
		get_texture(str + 2, &param->tex_w, param);
	else if (ft_strncmp(str, "EA", 2) == 0)
		get_texture(str + 2, &param->tex_e, param);
	else if (str[0] == 'C')
		param->color_c = get_color(str + 1, param, str[0]);
	else if (str[0] == 'F')
		param->color_f = get_color(str + 1, param, str[0]);
	else if (str[0])
		map_example(param, "wrong param");
}

int	check_param(t_param *param)
{
	int	i;

	i = 0;
	while (param->file[i] && !ft_isdigit(param->file[i][0])
		&& !is_isspace(param->file[i][0]))
	{
		get_param(param->file[i], param);
		i++;
	}
	if (!param->tex_e || !param->tex_n || !param->tex_s || !param->tex_w
		|| param->color_c == -1 || param->color_f == -1)
		map_example(param, "miss param");
	check_map(param);
	return (0);
}

char	**get_file(int fd)
{
	int		i;
	t_list	*file_lst;
	t_list	*tmp;
	char	*line;
	char	**file;

	line = get_next_line(fd);
	file_lst = NULL;
	while (line)
	{
		ft_lstadd_back(&file_lst, ft_lstnew(line));
		line = get_next_line(fd);
	}
	i = 0;
	file = malloc(sizeof(char *) * (ft_lstsize(file_lst) + 1));
	file[ft_lstsize(file_lst)] = NULL;
	tmp = file_lst;
	while (tmp)
	{
		file[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	ft_lstclear(&file_lst, simple_del);
	return (file);
}

int	check_file(t_param	*param, int fd)
{
	param->map = NULL;
	param->color_c = -1;
	param->color_f = -1;
	param->tex_e = NULL;
	param->tex_n = NULL;
	param->tex_w = NULL;
	param->tex_s = NULL;
	param->posx = -1;
	param->posy = -1;
	param->dir = -1;
	param->file = get_file(fd);
	check_param(param);
	free_tab(param->file);
	free(param->tex_e);
	free(param->tex_n);
	free(param->tex_s);
	free(param->tex_w);
	return (0);
}
