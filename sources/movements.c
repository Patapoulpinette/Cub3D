/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:01:41 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/07 17:46:40 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	if (key == 13) //move forward
	{
		if (world_map[(int)(structs->raycasting->player_x \
			+ structs->raycasting->direction_x \
			* structs->raycasting->move_speed)] \
			[(int)(structs->raycasting->player_y)] == '0')
			structs->raycasting->player_x += structs->raycasting->direction_x \
				* structs->raycasting->move_speed;
		if (world_map[(int)(structs->raycasting->player_x)] \
			[(int)(structs->raycasting->player_y \
			+ structs->raycasting->direction_y \
			* structs->raycasting->move_speed)] == '0')
			structs->raycasting->player_y += structs->raycasting->direction_y \
				* structs->raycasting->move_speed;
	}
	if (key == 1) //move backwards
	{
		if (world_map[(int)(structs->raycasting->player_x \
			- structs->raycasting->direction_x \
			* structs->raycasting->move_speed)] \
			[(int)(structs->raycasting->player_y)] == '0')
			structs->raycasting->player_x -= structs->raycasting->direction_x \
				* structs->raycasting->move_speed;
		if (world_map[(int)(structs->raycasting->player_x)] \
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

	if (key == 0) //move to the left
	{
		if (world_map[(int)(structs->raycasting->player_x \
			- structs->raycasting->camera_plane_x \
			* structs->raycasting->move_speed)] \
			[(int)(structs->raycasting->player_y)] == '0')
			structs->raycasting->player_x -= structs->raycasting->camera_plane_x \
				* structs->raycasting->move_speed;
		if (world_map[(int)(structs->raycasting->player_x)] \
			[(int)(structs->raycasting->player_y \
			- structs->raycasting->camera_plane_y \
			* structs->raycasting->move_speed)] == '0')
			structs->raycasting->player_y -= structs->raycasting->camera_plane_y \
				* structs->raycasting->move_speed;
	}
	if (key == 2) //move to the right
	{
		if (world_map[(int)(structs->raycasting->player_x \
			+ structs->raycasting->camera_plane_x \
			* structs->raycasting->move_speed)] \
			[(int)(structs->raycasting->player_y)] == '0')
			structs->raycasting->player_x += structs->raycasting->camera_plane_x \
				* structs->raycasting->move_speed;
		if (world_map[(int)(structs->raycasting->player_x)] \
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
