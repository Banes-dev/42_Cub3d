/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehay <ehay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:37:29 by ehay              #+#    #+#             */
/*   Updated: 2024/05/27 15:59:02 by ehay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_error(int num_error)
{
	if (num_error == 1)
	{
		printf("\033[96mError : \033[91mnot two args.\033[0m\n");
		printf("\033[96mTry : \033[33m./cub3d <map>.cub\033[0m\n");
	}
	if (num_error == 89)
		printf("\033[96mError : \033[91mMLX Library error.\033[0m\n");
	exit(1);
}
