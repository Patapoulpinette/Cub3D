/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:02:13 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/05 12:16:01 by dbouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	degree_to_radian(int degree)
{
	return (degree * M_PI / 180);
}

double	pythagoras(int a, int b)
{
	return (sqrt(pow(a, 2) + pow(b, 2)));
}

void	raycasting_algo(t_image *image, t_raycasting *raycasting)
{
	int		x;
	double	camera_x;
	double	ray_x;
	double	ray_y;
	int		map_x;
	int		map_y;
	double	side_distance_x;
	double	side_distance_y;
	double	delta_distance_x;
	double	delta_distance_y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		//calculate ray position and direction
		camera_x = 2 * x / (double)SCREEN_WIDTH - 1;//x coords in camera space
		ray_x = raycasting->direction_x + raycasting->camera_plane_x * camera_x;
		ray_y = raycasting->direction_y + raycasting->camera_plane_y * camera_x;

		//which box of the map we're in
		map_x = (int)raycasting->player_x;
		map_y = (int)raycasting->player_y;

		//length of ray from current position to next x or y-side
		//length of ray from x or y-side to next x or y-side
		delta_distance_x = ;
		delta_distance_y = ;

		x++;
	}
}
