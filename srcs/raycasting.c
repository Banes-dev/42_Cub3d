/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehay <ehay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:49:35 by ehay              #+#    #+#             */
/*   Updated: 2024/06/06 16:12:22 by ehay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int wall_hit(double x, double y, t_game_instance *game) // check the wall hit
{
	int  x_m;
	int  y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / TILE_SIZE); // get the x position in the map
	y_m = floor(y / TILE_SIZE); // get the y position in the map
	// if ((y_m >= mlx->dt->h_map || x_m >= mlx->dt->w_map))
	// 	return (0);
	if (game->map[y_m] && x_m <= (int)strlen(game->map[y_m]))
		if (game->map[y_m][x_m] == '1')
			return (0);
	return (1);
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



	// boucle pour chaque rayon fisrt_angle + FOV / WINDOW_WIDTH;
	int	ray;
	double base_radians;
	double base_angle;
	double first_angle;
	double horizon_intersection;
	double vertical_intersection;
	double distance;

	ray = 0;
	base_radians = atan2(game->vector_x, game->vector_y);
	base_angle = base_radians * (180.0 / M_PI);
	first_angle = base_angle + (FOV / 2);
	while (ray < WINDOW_WIDTH)
	{
		// calcul distance puis rendu des wall
		// horizon_intersection = get_h_inter(game, first_angle);      // get intersection horizontale
		// vertical_intersection = get_v_inter(game, first_angle);     // get intersection verticale
		if (vertical_intersection <= horizon_intersection)
			distance = vertical_intersection;
		else
			distance = horizon_intersection;
		// if (base_angle - first_angle <= 2)
		// 	printf("distance : %f\n", distance);
		ray++;
		first_angle = first_angle + (FOV / WINDOW_WIDTH);
	}
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
