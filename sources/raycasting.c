/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:02:13 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/04 15:04:48 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast(t_raycasting *ray, t_minimap *minimap, t_player *player)
{
	double	vertical_grid;
	double	horizontal_grid;
	double	dist_to_next_vertical_grid;
	double	dist_to_next_horizontal_grid;
	double	x_intersection;
	double	y_intersection;
	double	dist_to_next_x_intersection;
	double	dist_to_next_y_intersection;
	double	x_grid_index;
	double	y_grid_index;
	double	dist_to_vertical_grid_being_hit;
	double	dist_to_horizontal_grid_being_hit;
	double	cast_arc;
	double	cast_column;
	double	x_tmp;

	cast_arc = player->angle;
	// field of view is 60 degree with the point of view (player's direction in the middle)
		// 30  30
		//    ^
		//  \ | /
		//   \|/
		//    v
		// we will trace the rays starting from the leftmost ray
	cast_arc -= ray->angle30;

	if (cast_arc < 0)
		cast_arc += ray->angle30;

	cast_column = 0;
	while (cast_column < SCREEN_WIDTH)
	{
		// Ray is between 0 to 180 degree (1st and 2nd quadrant).

		// Ray is facing down
		if (cast_arc > ray->angle0 && cast_arc < ray->angle180)
		{
			horizontal_grid = floor(player->y / ray->tile_size) * ray->tile_size +ray->tile_size;
			dist_to_next_horizontal_grid = ray->tile_size;
			x_tmp = ray->tan_table_inv[cast_arc] * (horizontal_grid - player->y);
			x_intersection = x_tmp + player->x;
		}
		// Else, the ray is facing up
		else
		{
			horizontal_grid = floor(player->y / ray->tile_size) * ray->tile_size;
			dist_to_next_horizontal_grid = -ray->tile_size;
			x_tmp = ray->tan_table_inv[cast_arc] * (horizontal_grid - player->y);
			x_intersection = x_tmp + player->x;
			horizontal_grid--;
		}

		// LOOK FOR HORIZONTAL WALL
			
		// If ray is directly facing right or left, then ignore it
		

		cast_column++;
	}
}
