/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehay <ehay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:49:35 by ehay              #+#    #+#             */
/*   Updated: 2024/06/05 16:38:34 by ehay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_raycasting(t_game_instance *game)
{
	// printf("player : %f %f\n", game->player_x, game->player_y);
	// printf("vector : %f %f\n", game->vector_x, game->vector_y);
	// printf("camera : %f %f\n", game->camera_x, game->camera_y);

	double theta_radians = atan2(game->vector_x, game->vector_y);
	double theta_degrees = theta_radians * (180.0 / M_PI);
	printf("angle : %f\n", theta_degrees);
	double fisrt_angle = theta_degrees + (FOV / 2);
	printf("premier angle gauche : %f\n", fisrt_angle);
	double last_angle = theta_degrees - (FOV / 2);
	printf("dernier angle droit : %f\n", last_angle);



	double angle_check = theta_degrees + (FOV / 2);
	double radians_check = angle_check * (M_PI / 180.0);
	double endX = game->player_x + 5.0 * cos(radians_check);
	double endY = game->player_y + 5.0 * sin(radians_check);
	
	printf("Point de départ : (%f, %f)\n", game->player_x, game->player_y);
	printf("Point final : (%f, %f)\n", endX, endY);


	// envoie rayon avec le premier angle
	// si le rayon touche un mur alors calcul valeur triangle rectangle
	// avec valeur du triangle utiliser theoreme de pythagore pour calculer l'hypotenuse
}
