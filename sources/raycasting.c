/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:02:13 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/07 15:44:27 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	char			*world_map[] =
				{
					"111111111111111111111111",
					"100000000000000000000001",
					"100000000000000000000001",
					"100000000000000000000001",
					"100000222220000333330001",
					"100000200020003000003001",
					"100000200020000300030001",
					"100000200020003000003001",
					"100000220220000300030001",
					"100000000000000000000001",
					"100000000000000000000001",
					"100000000000000000000001",
					"100000000000000000000001",
					"144444444000000000000001",
					"140400004000000000000001",
					"140000504000000000000001",
					"140400004000000000000001",
					"140444444000000000000001",
					"140000000000000000000001",
					"144444444000000000000001",
					"111111111111111111111111"
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
			if (world_map[map_x][map_y] != '0')
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

		//draw walls with vertical lines
		pt.x0 = x;
		pt.x1 = x;
		pt.y0 = draw_start;
		pt.y1 = draw_end;
		if (side == 1) //give x and y sides different brightness
			bhm_line(image, &pt, WALL_COLOR / 2);
		else
			bhm_line(image, &pt, WALL_COLOR);

		//draw ceilling with vertical lines
		pt.x0 = x;
		pt.x1 = x;
		pt.y0 = 0;
		pt.y1 = draw_start;
		bhm_line(image, &pt, SKY_COLOR);

		//draw floor with vertical lines
		pt.x0 = x;
		pt.x1 = x;
		pt.y0 = draw_end;
		pt.y1 = SCREEN_HEIGHT;
		bhm_line(image, &pt, FLOOR_COLOR);

		x++;
	}
}

void	move_player(int key, t_structs *structs)
{
	char	*world_map[] = {
					"111111111111111111111111",
					"100000000000000000000001",
					"100000000000000000000001",
					"100000000000000000000001",
					"100000222220000333330001",
					"100000200020003000003001",
					"100000200020000300030001",
					"100000200020003000003001",
					"100000220220000300030001",
					"100000000000000000000001",
					"100000000000000000000001",
					"100000000000000000000001",
					"100000000000000000000001",
					"144444444000000000000001",
					"140400004000000000000001",
					"140000504000000000000001",
					"140400004000000000000001",
					"140444444000000000000001",
					"140000000000000000000001",
					"144444444000000000000001",
					"111111111111111111111111"
				};

	if (key == 13)//move forward
	{
		if(world_map[(int)(structs->raycasting->player_x \
			+ structs->raycasting->direction_x \
			* structs->raycasting->move_speed)]\
			[(int)(structs->raycasting->player_y)] == '0')
			structs->raycasting->player_x += structs->raycasting->direction_x \
				* structs->raycasting->move_speed;
		if(world_map[(int)(structs->raycasting->player_x)]\
			[(int)(structs->raycasting->player_y \
			+ structs->raycasting->direction_y \
			* structs->raycasting->move_speed)] == '0')
			structs->raycasting->player_y += structs->raycasting->direction_y \
				* structs->raycasting->move_speed;
	}
	if (key == 1)//move backwards
	{
		if(world_map[(int)(structs->raycasting->player_x \
			- structs->raycasting->direction_x \
			* structs->raycasting->move_speed)]\
			[(int)(structs->raycasting->player_y)] == '0')
			structs->raycasting->player_x -= structs->raycasting->direction_x \
				* structs->raycasting->move_speed;
		if(world_map[(int)(structs->raycasting->player_x)]\
			[(int)(structs->raycasting->player_y \
			- structs->raycasting->direction_y \
			* structs->raycasting->move_speed)] == '0')
			structs->raycasting->player_y -= structs->raycasting->direction_y \
				* structs->raycasting->move_speed;
	}
}

void	translate_player(int key, t_structs *structs)
{
	char	*world_map[] = {
					"111111111111111111111111",
					"100000000000000000000001",
					"100000000000000000000001",
					"100000000000000000000001",
					"100000222220000333330001",
					"100000200020003000003001",
					"100000200020000300030001",
					"100000200020003000003001",
					"100000220220000300030001",
					"100000000000000000000001",
					"100000000000000000000001",
					"100000000000000000000001",
					"100000000000000000000001",
					"144444444000000000000001",
					"140400004000000000000001",
					"140000504000000000000001",
					"140400004000000000000001",
					"140444444000000000000001",
					"140000000000000000000001",
					"144444444000000000000001",
					"111111111111111111111111"
				};

	if (key == 0)//move to the left
	{
		if(world_map[(int)(structs->raycasting->player_x \
			- structs->raycasting->camera_plane_x \
			* structs->raycasting->move_speed)]\
			[(int)(structs->raycasting->player_y)] == '0')
			structs->raycasting->player_x -= structs->raycasting->camera_plane_x \
				* structs->raycasting->move_speed;
		if(world_map[(int)(structs->raycasting->player_x)]\
			[(int)(structs->raycasting->player_y \
			- structs->raycasting->camera_plane_y \
			* structs->raycasting->move_speed)] == '0')
			structs->raycasting->player_y -= structs->raycasting->camera_plane_y \
				* structs->raycasting->move_speed;
	}
	if (key == 2)//move to the right
	{
		if(world_map[(int)(structs->raycasting->player_x \
			+ structs->raycasting->camera_plane_x \
			* structs->raycasting->move_speed)]\
			[(int)(structs->raycasting->player_y)] == '0')
			structs->raycasting->player_x += structs->raycasting->camera_plane_x \
				* structs->raycasting->move_speed;
		if(world_map[(int)(structs->raycasting->player_x)]\
			[(int)(structs->raycasting->player_y \
			+ structs->raycasting->camera_plane_y \
			* structs->raycasting->move_speed)] == '0')
			structs->raycasting->player_y += structs->raycasting->camera_plane_y \
				* structs->raycasting->move_speed;
	}
}

void	rotate_camera_left(t_structs *structs)
{
	double	old_direction_x;
	//double	old_camera_plane_x;

	old_direction_x = structs->raycasting->direction_x;
	structs->raycasting->direction_x = structs->raycasting->direction_x \
		* cos(structs->raycasting->rot_speed) \
		- structs->raycasting->direction_y \
		* sin(structs->raycasting->rot_speed);
	structs->raycasting->direction_y = old_direction_x \
		* sin(structs->raycasting->rot_speed) \
		+ structs->raycasting->direction_y \
		* cos(structs->raycasting->rot_speed);
	// old_camera_plane_x = structs->raycasting->camera_plane_x;
	// structs->raycasting->camera_plane_x = \
	// 	structs->raycasting->camera_plane_x \
	// 	* cos(structs->raycasting->rot_speed) \
	// 	- structs->raycasting->camera_plane_y \
	// 	* sin(structs->raycasting->rot_speed);
	// structs->raycasting->camera_plane_x = old_camera_plane_x \
	// 	* sin(structs->raycasting->rot_speed) \
	// 	+ structs->raycasting->camera_plane_y \
	// 	* cos(structs->raycasting->rot_speed);
}

void	rotate_camera_right(t_structs *structs)
{
	double	old_direction_x;
	//double	old_camera_plane_x;

	old_direction_x = structs->raycasting->direction_x;
	structs->raycasting->direction_x = structs->raycasting->direction_x \
		* cos(-structs->raycasting->rot_speed) \
		- structs->raycasting->direction_y \
		* sin(-structs->raycasting->rot_speed);
	structs->raycasting->direction_y = old_direction_x \
		* sin(-structs->raycasting->rot_speed) \
		+ structs->raycasting->direction_y \
		* cos(-structs->raycasting->rot_speed);
	// old_camera_plane_x = structs->raycasting->camera_plane_x;
	// structs->raycasting->camera_plane_x = \
	// 	structs->raycasting->camera_plane_x \
	// 	* cos(-structs->raycasting->rot_speed) \
	// 	- structs->raycasting->camera_plane_y \
	// 	* sin(-structs->raycasting->rot_speed);
	// structs->raycasting->camera_plane_x = old_camera_plane_x \
	// 	* sin(-structs->raycasting->rot_speed) \
	// 	+ structs->raycasting->camera_plane_y \
	// 	* cos(-structs->raycasting->rot_speed);
}
