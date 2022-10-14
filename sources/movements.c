/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:01:41 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/14 14:41:31 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(int key, t_structs *strc)
{
	if (key == 13) //move forward
	{
		if (strc->ray->map[(int)(strc->player->x + strc->player->dir_x \
			* strc->ray->move_speed)][(int)(strc->player->y)] == '0')
			strc->player->x += strc->player->dir_x * strc->ray->move_speed;
		if (strc->ray->map[(int)(strc->player->x)][(int)(strc->player->y \
			+ strc->player->dir_y * strc->ray->move_speed)] == '0')
			strc->player->y += strc->player->dir_y * strc->ray->move_speed;
	}
	if (key == 1) //move backwards
	{
		if (strc->ray->map[(int)(strc->player->x - strc->player->dir_x \
			* strc->ray->move_speed)][(int)(strc->player->y)] == '0')
			strc->player->x -= strc->player->dir_x * strc->ray->move_speed;
		if (strc->ray->map[(int)(strc->player->x)][(int)(strc->player->y \
			- strc->player->dir_y * strc->ray->move_speed)] == '0')
			strc->player->y -= strc->player->dir_y * strc->ray->move_speed;
	}
}

void	translate_player(int key, t_structs *strc)
{
	if (key == 0) //move to the left
	{
		if (strc->ray->map[(int)(strc->player->x - strc->ray->plane_x \
			* strc->ray->move_speed)][(int)(strc->player->y)] == '0')
			strc->player->x -= strc->ray->plane_x * strc->ray->move_speed;
		if (strc->ray->map[(int)(strc->player->x)][(int)(strc->player->y \
			- strc->ray->plane_y * strc->ray->move_speed)] == '0')
			strc->player->y -= strc->ray->plane_y * strc->ray->move_speed;
	}
	if (key == 2) //move to the right
	{
		if (strc->ray->map[(int)(strc->player->x + strc->ray->plane_x \
			* strc->ray->move_speed)][(int)(strc->player->y)] == '0')
			strc->player->x += strc->ray->plane_x * strc->ray->move_speed;
		if (strc->ray->map[(int)(strc->player->x)][(int)(strc->player->y \
			+ strc->ray->plane_y * strc->ray->move_speed)] == '0')
			strc->player->y += strc->ray->plane_y * strc->ray->move_speed;
	}
}

void	rotate_camera_left(t_structs *strc)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = strc->player->dir_x;
	strc->player->dir_x = strc->player->dir_x * cos(strc->ray->rot_speed) \
		- strc->player->dir_y * sin(strc->ray->rot_speed);
	strc->player->dir_y = old_dir_x * sin(strc->ray->rot_speed) \
		+ strc->player->dir_y * cos(strc->ray->rot_speed);
	old_plane_x = strc->ray->plane_x;
	strc->ray->plane_x = strc->ray->plane_x * cos(strc->ray->rot_speed) \
		- strc->ray->plane_y * sin(strc->ray->rot_speed);
	strc->ray->plane_y = old_plane_x * sin(strc->ray->rot_speed) \
		+ strc->ray->plane_y * cos(strc->ray->rot_speed);
}

void	rotate_camera_right(t_structs *strc)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = strc->player->dir_x;
	strc->player->dir_x = strc->player->dir_x * cos(-strc->ray->rot_speed) \
		- strc->player->dir_y * sin(-strc->ray->rot_speed);
	strc->player->dir_y = old_dir_x * sin(-strc->ray->rot_speed) \
		+ strc->player->dir_y * cos(-strc->ray->rot_speed);
	old_plane_x = strc->ray->plane_x;
	strc->ray->plane_x = strc->ray->plane_x * cos(-strc->ray->rot_speed) \
		- strc->ray->plane_y * sin(-strc->ray->rot_speed);
	strc->ray->plane_y = old_plane_x * sin(-strc->ray->rot_speed) \
		+ strc->ray->plane_y * cos(-strc->ray->rot_speed);
}
