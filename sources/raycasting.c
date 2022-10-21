/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:02:13 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/19 12:05:58 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting_algo(t_image *image, t_player *player, t_raycasting *ray, t_minimap *minimap, t_texture *texture)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;//x coords in camera space
		ray->ray_x = player->dir_x + ray->plane_x * ray->camera_x;
		ray->ray_y = player->dir_y + ray->plane_y * ray->camera_x;
		ray->map_x = (int)player->x;
		ray->map_y = (int)player->y;
		if (ray->ray_x == 0)
		{
			ray->delta_dist_x = 1e30;
			ray->delta_dist_y = 1e30;
		}
		else
		{
			ray->delta_dist_x = fabs(1 / ray->ray_x);
			ray->delta_dist_y = fabs(1 / ray->ray_y);
		}
		calculate_step_and_side_dist(player, ray);
		perform_dda(image, player, ray, minimap);
		calculate_walls(ray);
		draw_vertival_lines(image, ray, x);
		draw_textures(image, player, ray, texture, x);
		x++;
	}
}

void	calculate_step_and_side_dist(t_player *player, t_raycasting *ray)
{
	if (ray->ray_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
	}
	if (ray->ray_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}

void	perform_dda(t_image *image, t_player *player, t_raycasting *ray, t_minimap *minimap)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		//check if ray has hit a wall
		if (ray->map[ray->map_x][ray->map_y] != '0')
		{
			ray->hit = 1;
			draw_map2d_rays(image, player, minimap, ray->map_x, ray->map_y);
		}
	}
}

void	calculate_walls(t_raycasting *ray)
{
	//calculate distance projected on camera direction
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	//calculate height of line to draw on screen
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	//calculate lowest and highest pixel to fill in current stripe
	ray->draw_start = -ray->line_height * 0.5 + SCREEN_HEIGHT * 0.5;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height * 0.5 + SCREEN_HEIGHT * 0.5;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
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
