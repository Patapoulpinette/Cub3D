/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:01:41 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/14 14:04:58 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(int key, t_structs *structs)
{
	if (key == 13) //move forward
	{
		if (structs->ray->map[(int)(structs->player->x + structs->player->dir_x * structs->ray->move_speed)][(int)(structs->player->y)] == '0')
			structs->player->x += structs->player->dir_x * structs->ray->move_speed;
		if (structs->ray->map[(int)(structs->player->x)][(int)(structs->player->y + structs->player->dir_y * structs->ray->move_speed)] == '0')
			structs->player->y += structs->player->dir_y * structs->ray->move_speed;
	}
	if (key == 1) //move backwards
	{
		if (structs->ray->map[(int)(structs->player->x - structs->player->dir_x * structs->ray->move_speed)][(int)(structs->player->y)] == '0')
			structs->player->x -= structs->player->dir_x * structs->ray->move_speed;
		if (structs->ray->map[(int)(structs->player->x)][(int)(structs->player->y - structs->player->dir_y * structs->ray->move_speed)] == '0')
			structs->player->y -= structs->player->dir_y * structs->ray->move_speed;
	}
	dprintf(2, "player_x = %f | player_y = %f\n", structs->player->x, structs->player->y);
}

void	translate_player(int key, t_structs *structs)
{
	if (key == 0) //move to the left
	{
		if (structs->ray->map[(int)(structs->player->x - structs->ray->plane_x * structs->ray->move_speed)][(int)(structs->player->y)] == '0')
			structs->player->x -= structs->ray->plane_x * structs->ray->move_speed;
		if (structs->ray->map[(int)(structs->player->x)][(int)(structs->player->y - structs->ray->plane_y * structs->ray->move_speed)] == '0')
			structs->player->y -= structs->ray->plane_y * structs->ray->move_speed;
	}
	if (key == 2) //move to the right
	{
		if (structs->ray->map[(int)(structs->player->x + structs->ray->plane_x * structs->ray->move_speed)][(int)(structs->player->y)] == '0')
			structs->player->x += structs->ray->plane_x * structs->ray->move_speed;
		if (structs->ray->map[(int)(structs->player->x)][(int)(structs->player->y + structs->ray->plane_y * structs->ray->move_speed)] == '0')
			structs->player->y += structs->ray->plane_y * structs->ray->move_speed;
	}
}

void	rotate_camera_left(t_structs *structs)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = structs->player->dir_x;
	structs->player->dir_x = structs->player->dir_x * cos(structs->ray->rot_speed) - structs->player->dir_y * sin(structs->ray->rot_speed);
	structs->player->dir_y = old_dir_x * sin(structs->ray->rot_speed) + structs->player->dir_y * cos(structs->ray->rot_speed);
	old_plane_x = structs->ray->plane_x;
	structs->ray->plane_x = structs->ray->plane_x * cos(structs->ray->rot_speed) - structs->ray->plane_y * sin(structs->ray->rot_speed);
	structs->ray->plane_y = old_plane_x * sin(structs->ray->rot_speed) + structs->ray->plane_y * cos(structs->ray->rot_speed);
}

void	rotate_camera_right(t_structs *structs)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = structs->player->dir_x;
	structs->player->dir_x = structs->player->dir_x * cos(-structs->ray->rot_speed) - structs->player->dir_y * sin(-structs->ray->rot_speed);
	structs->player->dir_y = old_dir_x * sin(-structs->ray->rot_speed) + structs->player->dir_y * cos(-structs->ray->rot_speed);
	old_plane_x = structs->ray->plane_x;
	structs->ray->plane_x = structs->ray->plane_x * cos(-structs->ray->rot_speed) - structs->ray->plane_y * sin(-structs->ray->rot_speed);
	structs->ray->plane_y = old_plane_x * sin(-structs->ray->rot_speed) + structs->ray->plane_y * cos(-structs->ray->rot_speed);
}
