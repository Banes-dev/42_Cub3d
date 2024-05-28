#ifndef CUB3D_H
#define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#include <fcntl.h>
#include <stdio.h>
#include "libft/libft.h"
# include "minilibx-linux/mlx.h"

typedef struct s_parse
{
	char	**file;
}			t_parse;

typedef struct s_param
{
	char	*tex_N;
	char	*tex_S;
	char	*tex_E;
	char	*tex_W;
	int 	color_F;
	int		color_C;
	char	**map;
	char	**file;
}			t_param;

char	*get_next_line(int fd);
int		check_file(int fd);



#endif
