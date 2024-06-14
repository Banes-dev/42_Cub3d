/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:19:21 by ehay              #+#    #+#             */
/*   Updated: 2024/06/14 14:15:08 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "fcntl.h" // Read
# include "libft/libft.h"
# include "limits.h" // INT_MIN et INT_MAX
# include "math.h"
# include "mlx/mlx.h"
# include "stdarg.h" // fonction va_
# include "stddef.h" // size_t
# include "stdio.h"  // printf and other
# include "stdlib.h" // malloc & free
# include "string.h" // fonction string
# include "unistd.h"

# define WINDOW_WIDTH 1150
# define WINDOW_HEIGHT 994
# define MINIMAP_WIDTH 254
# define MINIMAP_HEIGHT 248

# define ESPACE '0'
# define WALL '1'
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'

# define RS 0.1 // vitesse de rotation
# define MS 0.08 // vitesse de deplacement
# define ESC 65307

// # define W 122
// # define A 113
// # define S 115
// # define D 100
# define LEFT 65361
# define RIGHT 65363

# define W 119
# define A 97
# define S 115
# define D 100

// PARSING
typedef struct s_param
{
	char				dir;
	char				*tex_n;
	char				*tex_s;
	char				*tex_e;
	char				*tex_w;
	int					color_f;
	int					color_c;
	int					color_tmp;
	int					posx;
	int					posy;
	char				**map;
	char				**file;
}						t_param;

// IMAGE
typedef struct s_img
{
	void				*img_ptr;
	char				*data;
	int					size_l;
	int					bpp;
	int					endian;
}						t_img;

typedef struct s_tex
{
	t_img				img;
	int					width;
	int					height;
}						t_tex;
// GAME RESOLUTIONS
typedef struct s_game_resolutions
{
	int					settings_map_width;
	int					settings_map_height;
	char				*settings_name_window;
	char				*settings_name_map;
}						t_game_resolutions;

// MAIN GAME CONTROLLER
typedef struct s_game_instance
{
	void				*mlx_ptr;
	void				*win_ptr;
	double				player_x;
	double				player_y;
	double				vector_x;
	double				vector_y;
	double				plane_x;
	double				plane_y;
	double				camera_x;
	double				camera_y;
	double				ray_dir_x;
	double				ray_dir_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				step_x;
	double				step_y;
	double				side_dist_x;
	double				side_dist_y;
	int					sideofwall;
	char				**map;
	int					id;
	float				x_text;
	float				y_text;
	int					color_f;
	int					color_c;
	int					mv_up;
	int					mv_down;
	int					mv_left;
	int					mv_right;
	int					rt_right;
	int					rt_left;
	int					mouse_x;
	t_tex				tex[4];
	t_img				minimap;
	t_img				cub3d;
	t_game_resolutions	resolutions_init;
}						t_game_instance;

///////////
////// Functions
void					game(t_param *param);
void					refresh_minimap(t_game_instance *game);
void					ft_init_window(t_game_instance *game_init,
							t_param *param);
void					put_floor_celling(t_game_instance *game);
void					fill_line(t_game_instance *game, int x, int line_height,
							double wall_dist);
void					move(t_game_instance *game);

///// Parsing
void					get_vector(t_game_instance *game, t_param *param);
char					*get_next_line(int fd);
int						check_file(t_param *param, int fd);
int						is_isspace(char c);
int						get_color(char *str, t_param *param, char c);
void					check_map(t_param *param);

///// Raycasting
int						check_raycasting(t_game_instance *game);

// Error
void					ft_error(int num_error);
void					map_example(t_param *param, char *str);
int						ft_exit_program(t_game_instance *game_init);

// Utils
void					my_mlx_pixel_put(t_img *data, int x, int y, int color);
void					fusion_img(t_game_instance *game);
void					simple_del(void *del);
void					free_tab(char **tab);
int						my_mlx_get_color(t_img *data, int x, int y);

#endif