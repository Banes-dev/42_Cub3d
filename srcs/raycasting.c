/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:49:35 by ehay              #+#    #+#             */
/*   Updated: 2024/06/12 12:40:33 by mminet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_texx(t_game_instance *game, double wall_dist)
{
	float x_wall;
	double x_step;
	
	if (game->sideofwall == 0 && game->vector_x < 0)
		game->id = 0;
	else if (game->sideofwall == 0)
		game->id = 1;
	if (game->sideofwall == 1 && game->vector_y > 0)
		game->id = 2;
	else if (game->sideofwall == 1)
		game->id = 3;
	x_step = (float)game->tex[game->id].width / (float)WINDOW_WIDTH;
	if (game->sideofwall == 0)
		x_wall = (float)game->player_x + wall_dist * game->vector_y;
	else
		x_wall = (float)game->player_y + wall_dist * game->vector_x;
	game->x_text = (int)(x_wall * game->tex[game->id].width);
	// if (s->side == 0 && s->x_raydir > 0)
	// 	s->x_text = s->tex[id].texx - s->x_text - 1;
	// if (s->side == 1 && s->y_raydir < 0)
	// 	s->x_text = s->tex[id].texx - s->x_text - 1;
	game->x_text = abs(game->x_text);
	printf("%d\n", game->x_text);
}

void fill_line(t_game_instance *game, int x, int line_height, double wall_dist)
{
	int i;
	int y;
	float y_step;

	i = 0;
	y = 0;
	if (line_height > WINDOW_HEIGHT)
		line_height = WINDOW_HEIGHT;
	y = ((WINDOW_HEIGHT - line_height) / 2);
	// printf("%i, %i, %i\n", line_height, x, y);
	get_texx(game, wall_dist);
	game->y_text = 0;
	y_step = game->tex[game->id].height / line_height;
	while (i <= line_height)
	{
		//if (game->x_text <= game->tex[i].width - 1 && game->y_text <= game->tex[i].height && game->x_text >= 0 && game->y_text >= 0)
			my_mlx_pixel_put(&game->cub3d, x, y + i, game->id * 100);//my_mlx_get_color(&game->tex[game->id].img, game->x_text, game->y_text));
		game->y_text += y_step;
		i++;
	}
}

int	check_raycasting(t_game_instance *game)
{
	// printf("player : %f %f\n", game->player_x, game->player_y);
	// printf("vector : %f %f\n", game->vector_x, game->vector_y);
	// printf("camera : %f %f\n", game->camera_x, game->camera_y);

	// double theta_radians = atan2(game->vector_x, game->vector_y);
	// double theta_degrees = theta_radians * (180.0 / M_PI);
	// printf("angle : %f\n", theta_degrees);
	// double fisrt_angle = theta_degrees + (FOV / 2);
	// printf("premier angle gauche : %f\n", fisrt_angle);
	// double last_angle = theta_degrees - (FOV / 2);
	// printf("dernier angle droit : %f\n", last_angle);

	int x;
	// int map_x = (int)game->player_x;
	// int map_y = (int)game->player_y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		int map_x = (int)game->player_x;
		int map_y = (int)game->player_y;

		game->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		game->ray_dir_x = game->vector_x + game->plane_x * game->camera_x;
		game->ray_dir_y = game->vector_y + game->plane_y * game->camera_x;

		game->delta_dist_x = fabs(1 / game->ray_dir_x);
		game->delta_dist_y = fabs(1 / game->ray_dir_y);

		// calcul des step
		if (game->ray_dir_x < 0)
		{
			game->step_x = -1;
			game->side_dist_x = (game->player_x - map_x) * game->delta_dist_x;
		}
		else
		{
			game->step_x = 1;
			game->side_dist_x = (map_x + 1.0 - game->player_x) * game->delta_dist_x;
		}
		if (game->ray_dir_y < 0)
		{
			game->step_y = -1;
			game->side_dist_y = (game->player_y - map_y) * game->delta_dist_y;
		}
		else
		{
			game->step_y = 1;
			game->side_dist_y = (map_y + 1.0 - game->player_y) * game->delta_dist_y;
		}

		// check si wall
		while (1)
		{
			if (game->side_dist_x < game->side_dist_y)
			{
				game->side_dist_x = game->side_dist_x + game->delta_dist_x;
				map_x = map_x + game->step_x;
				game->sideofwall = 0;
			}
			else
			{
				game->side_dist_y = game->side_dist_y + game->delta_dist_y;
				map_y = map_y + game->step_y;
				game->sideofwall = 1;
			}
			// printf("map y : %i, map x : %i\n", map_y, map_x);
			if ((game->map[map_y][map_x]) == '1')
			{
				// printf("mur trouver, %c\n", game->map[map_y][map_x]);
				// printf("test %f, %f\n", game->side_dist_y, game->side_dist_x);
				break ;
			}
		}

		// calcul taille des wall
		double wall_dist = 0;
		if (game->sideofwall == 0)
			wall_dist = (map_x - game->player_x + (1 - game->step_x) / 2) / game->ray_dir_x;
		else
			wall_dist = (map_y - game->player_y + (1 - game->step_y) / 2) / game->ray_dir_y;
		int line_height = (int)(WINDOW_HEIGHT / wall_dist);
		fill_line(game, x, line_height, wall_dist);
		// printf("nb : %i, vector X : %f, vector Y : %f\n", x, game->plane_x, game->plane_y);
		// printf("nb : %i, direc X : %f, direc Y : %f\n", x, game->delta_dist_x, game->delta_dist_y);
		// printf("nb : %i, side dist X : %f, side dist Y : %f\n", x, game->side_dist_x, game->side_dist_y);
		x++;
	}



	// boucle pour chaque rayon fisrt_angle + FOV / WINDOW_WIDTH;
	// int	ray;
	// double base_radians;
	// double base_angle;
	// double first_angle;
	// double horizon_intersection;
	// double vertical_intersection;
	// double distance;

	// ray = 0;
	// base_radians = atan2(game->vector_x, game->vector_y);
	// base_angle = base_radians * (180.0 / M_PI);
	// first_angle = base_angle + (FOV / 2);
	// while (ray < WINDOW_WIDTH)
	// {
	// 	// calcul distance puis rendu des wall
	// 	// horizon_intersection = get_h_inter(game, first_angle);      // get intersection horizontale
	// 	// vertical_intersection = get_v_inter(game, first_angle);     // get intersection verticale
	// 	if (vertical_intersection <= horizon_intersection)
	// 		distance = vertical_intersection;
	// 	else
	// 		distance = horizon_intersection;
	// 	// if (base_angle - first_angle <= 2)
	// 	// 	printf("distance : %f\n", distance);
	// 	ray++;
	// 	first_angle = first_angle + (FOV / WINDOW_WIDTH);
	// }
	// printf("distance : %f\n", distance);
	// printf("rayon : %i, angle : %f\n", ray, first_angle);
	
	



	// double angle_check = theta_degrees + (FOV / 2);
	// double radians_check = angle_check * (M_PI / 180.0);
	// double endX = game->player_x + 5.0 * cos(radians_check);
	// double endY = game->player_y + 5.0 * sin(radians_check);
	
	// printf("Point de départ : (%f, %f)\n", game->player_x, game->player_y);
	// printf("Point final : (%f, %f)\n", endX, endY);


	// envoie rayon avec le premier angle
	// si le rayon touche un mur alors calcul valeur triangle rectangle
	// avec valeur du triangle utiliser theoreme de pythagore pour calculer l'hypotenuse
}
