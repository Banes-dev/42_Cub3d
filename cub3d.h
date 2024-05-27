#ifndef CUB3D_H
#define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#include <fcntl.h>
#include <stdio.h>
#include "libft/libft.h"

typedef struct s_param
{
	char	*tex_N;
	char	*tex_S;
	char	*tex_E;
	char	*tex_O;
	int 	color_F;
	int		color_C;
	char	**map;
}			t_param;



char	*get_next_line(int fd);
int		check_file(int fd);



#endif
