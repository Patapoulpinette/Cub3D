/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:01:41 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/13 16:56:36 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(int key, t_structs *structs)
{
	if (key == 13) //move forward
	{
		if (structs->ray->map[(int)(structs->ray->player_x \
			+ structs->ray->direction_x * structs->ray->move_speed)] \
			[(int)(structs->ray->player_y)] == '0')
			structs->ray->player_x += structs->ray->direction_x \
				* structs->ray->move_speed;
		if (structs->ray->map[(int)(structs->ray->player_x)] \
			[(int)(structs->ray->player_y + structs->ray->direction_y \
			* structs->ray->move_speed)] == '0')
			structs->ray->player_y += structs->ray->direction_y \
				* structs->ray->move_speed;
	}
	if (key == 1) //move backwards
	{
		if (structs->ray->map[(int)(structs->ray->player_x \
			- structs->ray->direction_x * structs->ray->move_speed)] \
			[(int)(structs->ray->player_y)] == '0')
			structs->ray->player_x -= structs->ray->direction_x \
				* structs->ray->move_speed;
		if (structs->ray->map[(int)(structs->ray->player_x)] \
			[(int)(structs->ray->player_y - structs->ray->direction_y \
			* structs->ray->move_speed)] == '0')
			structs->ray->player_y -= structs->ray->direction_y \
				* structs->ray->move_speed;
	}
}

void	translate_player(int key, t_structs *structs)
{
	if (key == 0) //move to the left
	{
		if (structs->ray->map[(int)(structs->ray->player_x \
			- structs->ray->camera_plane_x * structs->ray->move_speed)] \
			[(int)(structs->ray->player_y)] == '0')
			structs->ray->player_x -= structs->ray->camera_plane_x \
				* structs->ray->move_speed;
		if (structs->ray->map[(int)(structs->ray->player_x)] \
			[(int)(structs->ray->player_y - structs->ray->camera_plane_y \
			* structs->ray->move_speed)] == '0')
			structs->ray->player_y -= structs->ray->camera_plane_y \
				* structs->ray->move_speed;
	}
	if (key == 2) //move to the right
	{
		if (structs->ray->map[(int)(structs->ray->player_x \
			+ structs->ray->camera_plane_x * structs->ray->move_speed)] \
			[(int)(structs->ray->player_y)] == '0')
			structs->ray->player_x += structs->ray->camera_plane_x \
				* structs->ray->move_speed;
		if (structs->ray->map[(int)(structs->ray->player_x)] \
			[(int)(structs->ray->player_y + structs->ray->camera_plane_y \
			* structs->ray->move_speed)] == '0')
			structs->ray->player_y += structs->ray->camera_plane_y \
				* structs->ray->move_speed;
	}
}

void	rotate_camera_left(t_structs *structs)
{
	double	old_direction_x;
	double	old_camera_plane_x;

	old_direction_x = structs->ray->direction_x;
	structs->ray->direction_x = structs->ray->direction_x \
		* cos(structs->ray->rot_speed) - structs->ray->direction_y \
		* sin(structs->ray->rot_speed);
	structs->ray->direction_y = old_direction_x \
		* sin(structs->ray->rot_speed) + structs->ray->direction_y \
		* cos(structs->ray->rot_speed);
	old_camera_plane_x = structs->ray->camera_plane_x;
	structs->ray->camera_plane_x = structs->ray->camera_plane_x \
		* cos(structs->ray->rot_speed) - structs->ray->camera_plane_y \
		* sin(structs->ray->rot_speed);
	structs->ray->camera_plane_x = old_camera_plane_x \
		* sin(structs->ray->rot_speed) + structs->ray->camera_plane_y \
		* cos(structs->ray->rot_speed);
}

void	rotate_camera_right(t_structs *structs)
{
	double	old_direction_x;
	double	old_camera_plane_x;

	old_direction_x = structs->ray->direction_x;
	structs->ray->direction_x = structs->ray->direction_x \
		* cos(-structs->ray->rot_speed) - structs->ray->direction_y \
		* sin(-structs->ray->rot_speed);
	structs->ray->direction_y = old_direction_x \
		* sin(-structs->ray->rot_speed) + structs->ray->direction_y \
		* cos(-structs->ray->rot_speed);
	old_camera_plane_x = structs->ray->camera_plane_x;
	structs->ray->camera_plane_x = structs->ray->camera_plane_x \
		* cos(-structs->ray->rot_speed) - structs->ray->camera_plane_y \
		* sin(-structs->ray->rot_speed);
	structs->ray->camera_plane_x = old_camera_plane_x \
		* sin(-structs->ray->rot_speed) + structs->ray->camera_plane_y \
		* cos(-structs->ray->rot_speed);
}
