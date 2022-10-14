/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:02:13 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/14 14:05:27 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting_algo(t_image *image, t_player *player, t_raycasting *ray)
{
	int			x;
	double		camera_x;
	double		ray_x;
	double		ray_y;
	int			map_x;
	int			map_y;
	double		side_dist_x; //length of ray from current position to next x-side
	double		side_dist_y; //length of ray from current position to next y-side
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x; //what direction to step in x-direction (either +1 or -1)
	int			step_y; //what direction to step in y-direction (either +1 or -1)
	int			hit;
	int			line_height;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		//calculate ray position and direction
		camera_x = 2 * x / (double)SCREEN_WIDTH - 1;//x coords in camera space
		ray_x = player->dir_x + ray->plane_x * camera_x;
		ray_y = player->dir_y + ray->plane_y * camera_x;

		//which box of the map we're in
		map_x = (int)player->x;
		map_y = (int)player->y;

		//length of ray from x or y-side to next x or y-side
		if (ray_x == 0)
		{
			delta_dist_x = 1e30;
			delta_dist_y = 1e30;
		}
		else
		{
			delta_dist_x = fabs(1 / ray_x);
			delta_dist_y = fabs(1 / ray_y);
		}

		//was there a wall hit ?
		hit = 0;

		//calculate step and initial side_dist
		if (ray_x < 0)
		{
			step_x = -1;
			side_dist_x = (player->x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - player->x) * delta_dist_x;
		}
		if (ray_y < 0)
		{
			step_y = -1;
			side_dist_y = (player->y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - player->y) * delta_dist_y;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				ray->side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				ray->side = 1;
			}
			//check if ray has hit a wall
			if (ray->map[map_x][map_y] != '0')
				hit = 1;
		}

		//calculate distance projected on camera direction
		if (ray->side == 0)
			perp_wall_dist = side_dist_x - delta_dist_x;
		else
			perp_wall_dist = side_dist_y - delta_dist_y;

		//calculate height of line to draw on screen
		line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		ray->draw_start = -line_height * 0.5 + SCREEN_HEIGHT * 0.5;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
		ray->draw_end = line_height * 0.5 + SCREEN_HEIGHT * 0.5;
		if (ray->draw_end >= SCREEN_HEIGHT)
			ray->draw_end = SCREEN_HEIGHT - 1;

		draw_vertival_lines(image, ray, x);

		x++;
	}
}

void	draw_vertival_lines(t_image *image, t_raycasting *raycasting, int x)
{
	t_points	pt;

	//draw walls with vertical lines
	pt.x0 = x;
	pt.x1 = x;
	pt.y0 = raycasting->draw_start;
	pt.y1 = raycasting->draw_end;
	if (raycasting->side == 1) //give x and y sides different brightness
		bhm_line(image, &pt, WALL_COLOR * 0.5);
	else
		bhm_line(image, &pt, WALL_COLOR);
	//draw ceilling with vertical lines
	pt.x0 = x;
	pt.x1 = x;
	pt.y0 = 0;
	pt.y1 = raycasting->draw_start;
	bhm_line(image, &pt, SKY_COLOR);
	//draw floor with vertical lines
	pt.x0 = x;
	pt.x1 = x;
	pt.y0 = raycasting->draw_end;
	pt.y1 = SCREEN_HEIGHT;
	bhm_line(image, &pt, FLOOR_COLOR);
}
