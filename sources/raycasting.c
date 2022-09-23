/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:02:13 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/23 10:38:07 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting_algo(t_image *image, t_raycasting *raycasting, t_player *player, t_minimap *minimap)
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
	int			line_height;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		//calculate ray position and direction
		camera_x = 2 * x / (double)SCREEN_WIDTH - 1;//x coords in camera space
		ray_x = player->pdx + raycasting->camera_plane_x * camera_x;
		ray_y = player->pdy + raycasting->camera_plane_y * camera_x;

		//which box of the map we're in
		map_x = (int)player->px;
		map_y = (int)player->py;

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
			side_distance_x = (player->px - map_x) * delta_distance_x;
		}
		else
		{
			step_x = 1;
			side_distance_x = (map_x + 1.0 - player->px) * delta_distance_x;
		}
		if (ray_y < 0)
		{
			step_y = -1;
			side_distance_y = (player->py - map_y) * delta_distance_y;
		}
		else
		{
			step_y = 1;
			side_distance_y = (map_y + 1.0 - player->py) * delta_distance_y;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (side_distance_x < side_distance_y)
			{
				side_distance_x += delta_distance_x;
				map_x += step_x;
				raycasting->side = 0;
			}
			else
			{
				side_distance_y += delta_distance_y;
				map_y += step_y;
				raycasting->side = 1;
			}
			//check if ray has hit a wall
			if (minimap->map[map_x][map_y] != '0')
				hit = 1;
		}

		//calculate distance projected on camera direction
		if (raycasting->side == 0)
			perp_wall_dist = side_distance_x - delta_distance_x;
		else
			perp_wall_dist = side_distance_y - delta_distance_y;

		//calculate height of line to draw on screen
		line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		raycasting->draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (raycasting->draw_start < 0)
			raycasting->draw_start = 0;
		raycasting->draw_end = line_height / 2 + SCREEN_HEIGHT /2;
		if (raycasting->draw_end >= SCREEN_HEIGHT)
			raycasting->draw_end = SCREEN_HEIGHT - 1;
		(void) image;
//		draw_vertival_lines(image, raycasting, x);

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
		bhm_line(image, &pt, WALL_COLOR / 2);
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
