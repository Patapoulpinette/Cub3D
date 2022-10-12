/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:01:41 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/12 16:56:51 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(int key, t_structs *structs)
{
	if (key == 13)//move forward
	{
		if (structs->minimap->map[(int) (((structs->player->y + structs->player->y_dir * structs->player->speed) / structs->ray->tile_size * structs->minimap->wall_size) / structs->minimap->wall_size)][(int) (((structs->player->x + structs->player->x_dir * structs->player->speed) / structs->ray->tile_size * structs->minimap->wall_size) / structs->minimap->wall_size)] == '0')
		{
			structs->player->x += structs->player->x_dir * structs->player->speed;
			structs->player->y += structs->player->y_dir * structs->player->speed;
		}
	}
	else if (key == 1)//move backward
	{
		if (structs->minimap->map[(int) (((structs->player->y - structs->player->y_dir * structs->player->speed) / structs->ray->tile_size * structs->minimap->wall_size) / structs->minimap->wall_size)][(int) (((structs->player->x - structs->player->x_dir * structs->player->speed) / structs->ray->tile_size * structs->minimap->wall_size) / structs->minimap->wall_size)] == '0')
		{
			structs->player->x -= structs->player->x_dir * structs->player->speed;
			structs->player->y -= structs->player->y_dir * structs->player->speed;
		}
	}
}

void	translate_player(int key, t_structs *structs) //à revoir
{
	(void) key;
	(void) structs;
	return ;
}

void	rotate_camera(int key, t_structs *structs)
{
	if (key == 123)//rotate to the left
	{
		structs->player->angle -= structs->ray->angle5;
		if (structs->player->angle < structs->ray->angle0)
		{
			structs->player->angle += structs->ray->angle360;
		}
	}
	else if (key == 124)//rotate to the right
	{
		structs->player->angle += structs->ray->angle5;
		if (structs->player->angle >= structs->ray->angle360)
		{
			structs->player->angle -= structs->ray->angle360;
		}
	}
	structs->player->x_dir = structs->ray->cos_table[structs->player->angle];
	structs->player->y_dir = structs->ray->sin_table[structs->player->angle];
}
