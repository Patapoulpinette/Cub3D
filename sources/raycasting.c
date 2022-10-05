/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:02:13 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/05 11:51:46 by dbouron          ###   ########lyon.fr   */
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
	double	y_tmp;
	double	map_index;

	double	scale_factor;
	double	dist;
	double	top_of_wall;
	double	bottom_of_wall;
	double	projected_wall_height;

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
		if (cast_arc == ray->angle0 || cast_arc == ray->angle180)
			dist_to_horizontal_grid_being_hit = INT32_MAX; //not sure about this value
		// Else, move the ray until it hits a horizontal wall
		else
		{
			dist_to_next_x_intersection = ray->step_x_table[cast_arc];
			while (1)
			{
				x_grid_index = floor(x_intersection / ray->tile_size);
				y_grid_index = floor(horizontal_grid / ray->tile_size);
				//map_index = floor(y_grid_index * minimap->map_xlen + x_grid_index);//NOT NECESSARY I THINK
				// If we've looked as far as outside the map range, then bail out
				if ((x_grid_index >= minimap->map_xlen) || (y_grid_index >= minimap->map_ylen) || x_grid_index < 0 || y_grid_index < 0)
				{
					dist_to_horizontal_grid_being_hit = INT32_MAX;
					break;
				}
				// If the grid is not an Opening, then stop
				else if (minimap->map[y_grid_index][x_grid_index] != '0')
				{
					dist_to_horizontal_grid_being_hit = (x_intersection - player->x) * ray->cos_table_inv[cast_arc];
					break;
				}
				// Else, keep looking. At this point, the ray is not blocked, extend the ray to the next grid
				else
				{
					x_intersection += dist_to_next_x_intersection;
					horizontal_grid += dist_to_next_horizontal_grid;
				}
			}
		}
		// Follow x ray
		if (cast_arc < ray->angle90 || cast_arc > ray->angle270)
		{
			vertical_grid = ray->tile_size + floor(player->x / ray->tile_size) * ray->tile_size;
			dist_to_next_vertical_grid = ray->tile_size;
			y_tmp = ray->tan_table[cast_arc] * (vertical_grid - player->x);
			y_intersection = y_tmp + player->y;
		}
		// Ray facing left
		else
		{
			vertical_grid = floor(player->x / ray->tile_size) * ray->tile_size;
			dist_to_next_vertical_grid = -ray->tile_size;
			y_tmp = ray->tan_table[cast_arc] * (vertical_grid - player->x);
			y_intersection = y_tmp + player->y;
			vertical_grid--;
		}

		// LOOK FOR VERTICAL WALL

		if (cast_arc == ray->angle90 || cast_arc == ray->angle270)
			dist_to_vertical_grid_being_hit = INT32_MAX;
		else
		{
			dist_to_next_y_intersection = ray->step_y_table[cast_arc];
			while (1)
			{
				x_grid_index = floor(vertical_grid / ray->tile_size);
				y_grid_index = floor(y_intersection / ray->tile_size);
				//map_index = floor(y_grid_index * minimap->map_xlen + x_grid_index);//NOT NECESSARY I THINK
				if ((x_grid_index >= minimap->map_xlen) || (y_grid_index >= minimap->map_ylen) || x_grid_index < 0 || y_grid_index < 0)
				{
					dist_to_vertical_grid_being_hit = INT32_MAX;
					break;
				}
				else if (minimap->map[y_grid_index][x_grid_index] != '0')
				{
					dist_to_vertical_grid_being_hit = (y_intersection - player->y) * ray->sin_table_inv[cast_arc];
					break;
				}
				else
				{
					y_intersection += dist_to_next_y_intersection;
					vertical_grid += dist_to_next_vertical_grid;
				}
			}
		}

		// DRAW THE WALL SLICE

		// Determine which ray strikes a closer wall.
		// If yray distance to the wall is closer, the yDistance will be shorter than the xDistance
		if (dist_to_horizontal_grid_being_hit < dist_to_vertical_grid_being_hit)
		{
			draw_ray_on_map2d(image, minimap, ray, x_intersection, y_intersection);
			dist = dist_to_horizontal_grid_being_hit;
		}
		// Else, we use xray instead (meaning the vertical wall is closer than the horizontal wall)
		else
		{
			draw_ray_on_map2d(image, minimap, ray, vertical_grid, y_intersection);
			dist = dist_to_vertical_grid_being_hit;
		}
		// Correct distance (compensate for the fishbown effect)
		dist /= ray->fish_table[cast_column];
		// projected_wall_height/wall_height = fPlayerDistToProjectionPlane/dist;
		projected_wall_height = ray->wall_height * player->dist_from_proj_plane / dist;
		top_of_wall = ray->proj_plane_y_center - projected_wall_height * 0.5;
		if (top_of_wall < 0)
			top_of_wall = 0;
		bottom_of_wall = ray->proj_plane_y_center + projected_wall_height * 0.5;
		if (bottom_of_wall >= SCREEN_HEIGHT)
			bottom_of_wall = SCREEN_HEIGHT - 1;

		draw_fill_rect(image, cast_column, top_of_wall, 1, bottom_of_wall - top_of_wall + 1, WALL_COLOR);

		// TRACE THE NEXT RAY

		cast_arc++;
		if (cast_arc >= ray->angle360)
			cast_arc -= ray->angle360;

		cast_column++;
	}
}
