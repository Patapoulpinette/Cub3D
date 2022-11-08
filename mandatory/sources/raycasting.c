/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:02:13 by dbouron           #+#    #+#             */
/*   Updated: 2022/11/08 13:40:34 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting_algo(t_structs *structs)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		start_algo(structs, x);
		calculate_step_and_side_dist(structs->player, structs->ray);
		perform_dda(structs);
		calculate_walls(structs->ray);
		draw_vertival_lines(structs->image, structs->ray, x);
		draw_textures(structs, x);
		x++;
	}
}

void	start_algo(t_structs *structs, int x)
{
	structs->ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;//x coords in camera space
	structs->ray->ray_x = structs->player->dir_x + structs->ray->plane_x
		* structs->ray->camera_x;
	structs->ray->ray_y = structs->player->dir_y + structs->ray->plane_y
		* structs->ray->camera_x;
	structs->ray->map_x = (int)structs->player->x;
	structs->ray->map_y = (int)structs->player->y;
	if (structs->ray->ray_x == 0)
	{
		structs->ray->delta_dist_x = 1e30;
		structs->ray->delta_dist_y = 1e30;
	}
	else
	{
		structs->ray->delta_dist_x = fabs(1 / structs->ray->ray_x);
		structs->ray->delta_dist_y = fabs(1 / structs->ray->ray_y);
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

void	perform_dda(t_structs *structs)
{
	structs->ray->hit = 0;
	while (structs->ray->hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (structs->ray->side_dist_x < structs->ray->side_dist_y)
		{
			structs->ray->side_dist_x += structs->ray->delta_dist_x;
			structs->ray->map_x += structs->ray->step_x;
			structs->ray->side = 0;
		}
		else
		{
			structs->ray->side_dist_y += structs->ray->delta_dist_y;
			structs->ray->map_y += structs->ray->step_y;
			structs->ray->side = 1;
		}
		//check if ray has hit a wall
		if (structs->ray->map[structs->ray->map_x][structs->ray->map_y] != '0')
			structs->ray->hit = 1;
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
