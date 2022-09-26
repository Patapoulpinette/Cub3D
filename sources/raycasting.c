/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:02:13 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/26 17:47:47 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting_algo(t_raycasting *raycasting, t_minimap *minimap)
{
	double		perp_wall_dist;
	int			line_height;

	//perform DDA
	while (raycasting->hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (raycasting->side_distance_x < raycasting->side_distance_y)
		{
			raycasting->side_distance_x += raycasting->delta_distance_x;
			raycasting->map_x += raycasting->step_x;
			raycasting->side = 0;
		}
		else
		{
			raycasting->side_distance_y += raycasting->delta_distance_y;
			raycasting->map_y += raycasting->step_y;
			raycasting->side = 1;
		}
		//check if ray has hit a wall
		//dprintf(2, "map_x = %d | map_y = %d\n", raycasting->map_x / minimap->zoom, raycasting->map_y / minimap->zoom);
		if (minimap->map[raycasting->map_x / minimap->zoom][raycasting->map_y / minimap->zoom] != '0')
			raycasting->hit = 1;
	}
	//calculate distance projected on camera direction
	if (raycasting->side == 0)
		perp_wall_dist = raycasting->side_distance_x - raycasting->delta_distance_x;
	else
		perp_wall_dist = raycasting->side_distance_y - raycasting->delta_distance_y;
	//calculate height of line to draw on screen
	line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
	dprintf(2, "perp_wall_dist = %f | line_height = %d\n", perp_wall_dist, line_height);
	//calculate lowest and highest pixel to fill in current stripe
	raycasting->draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (raycasting->draw_start < 0)
		raycasting->draw_start = 0;
	raycasting->draw_end = line_height / 2 + SCREEN_HEIGHT /2;
	if (raycasting->draw_end >= SCREEN_HEIGHT)
		raycasting->draw_end = SCREEN_HEIGHT - 1;
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
