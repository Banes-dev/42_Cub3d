/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:22:01 by mminet            #+#    #+#             */
/*   Updated: 2024/05/27 15:52:26 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	simple_del(void *del)
{
	t_list *to_del = del;
	if (del)
		free(to_del->content);
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
	int 	i;

	len = ft_lstsize(*lst);
	if (len == 0)
		return;
	tmp = *lst;
	param->map = malloc(sizeof(char *) * len + 1);
	param->map[len] = NULL;
	i = 0;
	while (tmp)
	{
		param->map[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	//ft_lstclear(lst, simple_del);
}

int	check_file(int fd)
{
	char	*line;
	int		i;
	t_list	*map;
	t_param param;

	map = NULL;
	line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (is_isspace(line[i]))
			i++;
		if (line[i] && ft_isdigit(line[i]))
			ft_lstadd_back(&map, ft_lstnew(ft_strdup(line)));
		//check_line(line);
		free(line);
		line = get_next_line(fd);
	}
	fill_map(&param, &map);
	return (0);
}
