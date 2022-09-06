/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:02:13 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/06 12:07:09 by dbouron          ###   ########lyon.fr   */
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
	int			x;
	double		camera_x;
	double		ray_x;
	double		ray_y;
	int			map_x;
	int			map_y;
	double		side_distance_x;
	double		side_distance_y;
	double		delta_distance_x;
	double		delta_distance_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_points	pt;
	int			world_map[mapWidth][mapHeight] =
				{
					{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
					{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
					{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
				};

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
		if (ray_x == 0)
		{
			delta_distance_x = 1e30;
			delta_distance_y = 1e30;
		}
		else
		{
			delta_distance_x = fabs(1 / ray_x);
			delta_distance_y = fabs(1 / ray_y);
		}

		//what direction to step in x or y-direction (either +1 or -1)

		//was there a wall hit ?
		hit = 0;

		//calculate step and initial side_dist
		if (ray_x < 0)
		{
			step_x = -1;
			side_distance_x = (raycasting->player_x - map_x) * delta_distance_x;
		}
		else
		{
			step_x = 1;
			side_distance_x = (map_x + 1.0 - raycasting->player_x) * delta_distance_x;
		}
		if (ray_y < 0)
		{
			step_y = -1;
			side_distance_y = (raycasting->player_y - map_y) * delta_distance_y;
		}
		else
		{
			step_y = 1;
			side_distance_y = (map_y + 1.0 - raycasting->player_y) * delta_distance_y;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (side_distance_x < side_distance_y)
			{
				side_distance_x += delta_distance_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_distance_y += delta_distance_y;
				map_y += step_y;
				side = 1;
			}
			//check if ray has hit a wall
			if (world_map[map_x][map_y] > 0)
				hit = 1;
		}

		//calculate distance projected on camera direction
		if (side == 0)
			perp_wall_dist = side_distance_x - delta_distance_x;
		else
			perp_wall_dist = side_distance_y - delta_distance_y;

		//calculate height of line to draw on screen
		line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + SCREEN_HEIGHT /2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;

		//draw vertical lines
		pt.x0 = x;
		pt.x1 = x;
		pt.y0 = draw_start;
		pt.y1 = draw_end;
		if (side == 1) //give x and y sides different brightness
			bhm_line(image, &pt, WALL_COLOR / 2);
		else
			bhm_line(image, &pt, WALL_COLOR);

		x++;
	}
}
