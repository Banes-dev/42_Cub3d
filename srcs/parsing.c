/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:22:01 by mminet            #+#    #+#             */
/*   Updated: 2024/05/27 18:25:12 by mminet           ###   ########.fr       */
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

int	is_param(char *str)
{
	if (ft_strncmp(str, "NO", 2) == 0)
		return (1);
	if (ft_strncmp(str, "SO", 2) == 0)
		return (1);
	if (ft_strncmp(str, "WE", 2) == 0)
		return (1);
	if (ft_strncmp(str, "EA", 2) == 0)
		return (1);
	if (str[0] == 'S' || str[0] == 'F')
		return (1);
	return (0);
}
/*
int	check_param(int fd, t_param *param)
{
	
}*/

char **get_file(int fd)
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
		//free(line);
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
	param.tex_O = NULL;
	param.tex_S = NULL;
	param.file = get_file(fd);
	int i = 0;
	while (param.file && param.file[i])
	{
		ft_putstr_fd(param.file[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	//check_param(fd, &param);
	return (0);
}
