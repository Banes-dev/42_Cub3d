/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:22:01 by mminet            #+#    #+#             */
/*   Updated: 2024/05/28 03:27:00 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	map_example(t_param *param, char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\nExample .cub file :\n", 1);
	ft_putstr_fd("NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\nF 220,100,300\nC 225,30,0\n\n1111111\n1001011\n1010011\n1100N11\n1111111\n",
		1);
	free_tab(param->file);
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

void	simple_del(void *del)
{
	if (del)
		free(del);
}

int	is_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
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
		map_example(param, "error: syntax5\n");
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

void	get_texture(char *str, char **img, t_param *param)
{
	int i;

	i = 0;
	if (*img)
		map_example(param, "error: double texture\n");
	if (!is_isspace(str[i]))
		map_example(param, "error: syntax\n");
	while (is_isspace(str[i]))
		i++;
	if (!str[i])
		map_example(param, "error: syntax\n");
	*img = ft_strdup(str + 1);
}

void	get_param(char *str, t_param *param)
{
	if (ft_strncmp(str, "NO", 2) == 0)
		get_texture(str + 2, &param->tex_N, param);
	else if (ft_strncmp(str, "SO", 2) == 0)
		get_texture(str + 2, &param->tex_S, param);
	else if (ft_strncmp(str, "WE", 2) == 0)
		get_texture(str + 2, &param->tex_W, param);
	else if (ft_strncmp(str, "EA", 2) == 0)
		get_texture(str + 2, &param->tex_E, param);
	else if (str[0] == 'C')
		param->color_C = get_color(str + 1, param, str[0]);
	else if (str[0] == 'F')
		param->color_F = get_color(str + 1, param, str[0]);
	else if (str[0])
		map_example(param, "error: wrong param");
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
	if (!param->tex_E || !param->tex_N || !param->tex_S || !param->tex_W || param->color_C == -1 || param->color_F == -1)
		map_example(param, "error: miss param");
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

int	check_file(int fd)
{
	t_param	param;

	param.map = NULL;
	param.color_C = -1;
	param.color_F = -1;
	param.tex_E = NULL;
	param.tex_N = NULL;
	param.tex_W = NULL;
	param.tex_S = NULL;
	param.file = get_file(fd);
	check_param(&param);
	free_tab(param.file);
	free(param.tex_E);
	free(param.tex_N);
	free(param.tex_S);
	free(param.tex_W);
	return (0);
}
