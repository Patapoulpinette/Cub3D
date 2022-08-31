/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:02:13 by dbouron           #+#    #+#             */
/*   Updated: 2022/06/02 11:22:57 by dbouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	degree_to_radian(int degree)
{
	return (degree * M_PI / 180);
}

int pythagoras(t_raycasting *raycasting)
{
	return ((int) lround(sqrt(pow(raycasting->player_X - raycasting->ray_X, 2) + \
		pow(raycasting->player_Y - raycasting->ray_Y, 2))));
	//distance² = (player x - ray x)² +(player y - ray y)²
}

void	rayCasting(t_image *image, t_raycasting *raycasting)
{
	int		ray_angle;
	int		ray_count;
	double	ray_cos;
	double	ray_sin;
	int		wall;
	int		distance;
	int		wall_height;
	t_points	pt;

	ray_angle = raycasting->player_angle - raycasting->player_half_FOV;
	ray_count = 0;
	while (ray_count < SCREEN_WIDTH)
	{
		// Ray data
				raycasting->ray_X = raycasting->player_X;
				raycasting->ray_Y = raycasting->player_Y;

		// Ray path incrementers
		ray_cos = cos(degree_to_radian(ray_angle)) / raycasting->rayCasting_precision;
		ray_sin = sin(degree_to_radian(ray_angle)) / raycasting->rayCasting_precision;

		// Wall checking
		wall = 0;
		while (wall == 0)
		{
			raycasting->ray_X += (int) lround(ray_cos);
			raycasting->ray_Y += (int) lround(ray_sin);
			wall = raycasting->map[raycasting->ray_Y][raycasting->ray_X];
		}

		//Pythagoras theorem
		distance = pythagoras(raycasting);

		// Wall height
		wall_height = (int) lround(SCREEN_HALF_HEIGHT / distance);

		// Draw
		pt.x0 = ray_count;
		pt.y0 = 0;
		pt.x1 = ray_count;
		pt.y1 = SCREEN_HALF_HEIGHT - wall_height;
		bhm_line(image, &pt, SKY_COLOR);
		pt.y0 = SCREEN_HALF_HEIGHT - wall_height;
		pt.y1 = SCREEN_HALF_HEIGHT + wall_height;
		bhm_line(image, &pt, WALL_COLOR);
		pt.y0 = SCREEN_HALF_HEIGHT + wall_height;
		pt.y1 = SCREEN_HEIGHT;
		bhm_line(image, &pt, FLOOR_COLOR);

		//drawLine(rayCount, 0, rayCount, data.screen.halfHeight - wallHeight, "cyan");
		//drawLine(rayCount, data.screen.halfHeight - wallHeight, rayCount, data.screen.halfHeight + wallHeight, "red");
		//drawLine(rayCount, data.screen.halfHeight + wallHeight, rayCount, data.screen.height, "green");
		//x1, y1, x2, y2

		// Increment
		ray_angle += raycasting->increment_angle;
		ray_count++;
	}
}
