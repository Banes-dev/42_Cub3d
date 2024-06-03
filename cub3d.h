/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:19:21 by ehay              #+#    #+#             */
/*   Updated: 2024/06/03 14:42:08 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "libft/libft.h"
# include "stdio.h"           // printf and other
# include "unistd.h"
# include "stdlib.h"          // malloc & free
# include "stdarg.h"          // fonction va_
# include "stddef.h"          // size_t
# include "limits.h"          // INT_MIN et INT_MAX
# include "fcntl.h" 		  // Read
# include "string.h" 		  // fonction string
# include "mlx/mlx.h"

# define WINDOW_WIDTH 960
# define WINDOW_HEIGHT 840
# define MINIMAP_WIDTH WINDOW_WIDTH / 5
# define MINIMAP_HEIGHT WINDOW_HEIGHT / 5

# define ESPACE '0'
# define WALL '1'
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

// PARSING
typedef struct s_param
{
	char	dir;
	char	*tex_n;
	char	*tex_s;
	char	*tex_e;
	char	*tex_w;
	int		color_f;
	int		color_c;
	int		posx;
	int		posy;
	char	**map;
	char	**file;
}			t_param;

// IMAGE
typedef struct s_img
{
	void		*img_ptr;
	char		*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

// GAME RESOLUTIONS 
typedef struct s_game_resolutions
{
	int		settings_map_width;
	int		settings_map_height;
	char	*settings_name_window;
	char	*settings_name_map;
}	t_game_resolutions;

// MAIN GAME CONTROLLER
// MAIN GAME CONTROLLER
typedef struct s_game_instance
{
	void				*mlx_ptr;
	void				*win_ptr;
	double				player_x;
	double				player_y;
	double				vector_x;
	double				vector_y;
	double				camera_x;
	double				camera_y;
	char				**map;
	int					mv_up;
	int					mv_down;
	int					mv_left;
	int 				mv_right;
	t_img				miniMap;
	t_game_resolutions	resolutions_init;
}	t_game_instance;

///////////
////// Functions
void	game(t_param *param);
void	refresh_minimap(t_game_instance *game);
void	ft_init_window(t_game_instance *game_init);

///// Parsing
char	*get_next_line(int fd);
int		check_file(t_param	*param, int fd);
int		is_isspace(char c);
int		get_color(char *str, t_param *param, char c);
void	check_map(t_param *param);

// Error
void	ft_error(int num_error);
void	map_example(t_param *param, char *str);
int		ft_exit_program(t_game_instance *game_init);

//Utils
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	simple_del(void *del);
void	free_tab(char **tab);

#endif
