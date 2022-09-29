/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:02:13 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/28 16:48:14 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	search_collisions(t_raycasting *ray, t_minimap *minimap)
{
	double	perp_wall_dist;
	int		line_height;

	//was there a wall hit ?
	ray->hit = 0;

	//perform DDA
	while (ray->hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		//check if ray has hit a wall
		if (minimap->map[ray->map_y / minimap->zoom][ray->map_x / minimap->zoom] != '0')
			ray->hit = 1;
	}
	//calculate distance projected on camera direction
	if (ray->side == 0)
		perp_wall_dist = ray->side_x - ray->delta_x;
	else
		perp_wall_dist = ray->side_y - ray->delta_y;
	//calculate height of line to draw on screen
	line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
	//calculate lowest and highest pixel to fill in current stripe
	ray->draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = line_height / 2 + SCREEN_HEIGHT /2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
}

void	draw_vertival_lines(t_image *image, t_raycasting *ray, int x)
{
	t_points	pt;

	//draw walls with vertical lines
	pt.x0 = x;
	pt.x1 = x;
	pt.y0 = ray->draw_start;
	pt.y1 = ray->draw_end;
	if (ray->side == 1) //give x and y sides different brightness
		bhm_line(image, &pt, WALL_COLOR / 2);
	else
		bhm_line(image, &pt, WALL_COLOR);
	//draw ceilling with vertical lines
	pt.x0 = x;
	pt.x1 = x;
	pt.y0 = 0;
	pt.y1 = ray->draw_start;
	bhm_line(image, &pt, SKY_COLOR);
	//draw floor with vertical lines
	pt.x0 = x;
	pt.x1 = x;
	pt.y0 = ray->draw_end;
	pt.y1 = SCREEN_HEIGHT;
	bhm_line(image, &pt, FLOOR_COLOR);
}
