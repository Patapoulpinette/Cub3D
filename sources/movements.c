/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:01:41 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/11 13:51:03 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(int key, t_structs *structs)
{
	if (key == 13)//move forward
	{
		if (structs->minimap->map[(int) (((structs->player->y + structs->player->y_dir * structs->player->speed) / structs->ray->tile_size * structs->minimap->wall_size) / structs->minimap->wall_size)][(int) (((structs->player->x + structs->player->x_dir * structs->player->speed) / structs->ray->tile_size * structs->minimap->wall_size) / structs->minimap->wall_size)] == '0')
		{
			puts("move forward -------");
			dprintf(1, "avant : x = %d | y = %d\n", structs->player->x, structs->player->y);
			structs->player->x += structs->player->x_dir * structs->player->speed;
			structs->player->y += structs->player->y_dir * structs->player->speed;
			dprintf(1, "après : x = %d | y = %d\n", structs->player->x, structs->player->y);
		}
	}
	else if (key == 1)//move backward
	{
		if (structs->minimap->map[(int) (((structs->player->y - structs->player->y_dir * structs->player->speed) / structs->ray->tile_size * structs->minimap->wall_size) / structs->minimap->wall_size)][(int) (((structs->player->x - structs->player->x_dir * structs->player->speed) / structs->ray->tile_size * structs->minimap->wall_size) / structs->minimap->wall_size)] == '0')
		{
			puts("move backward --------");
			dprintf(1, "avant : x = %d | y = %d\n", structs->player->x, structs->player->y);
			structs->player->x -= structs->player->x_dir * structs->player->speed;
			structs->player->y -= structs->player->y_dir * structs->player->speed;
			dprintf(1, "après : x = %d | y = %d\n", structs->player->x, structs->player->y);
		}
	}
	dprintf(1, "player_x = %d | player_y = %d | maps_x = %d | map_y = %d\n", structs->player->x, structs->player->y, structs->ray->map_x, structs->ray->map_y);
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
		puts("rotate left --------");
		dprintf(1, "avant : angle = %d\n", structs->player->angle);
		structs->player->angle -= structs->ray->angle10;
		if (structs->player->angle < structs->ray->angle0)
		{
			puts("maintenant_left");
			structs->player->angle += structs->ray->angle360;
		}
		dprintf(1, "apres : angle = %d\n", structs->player->angle);
	}
	else if (key == 124)//rotate to the right
	{
		puts("rotate right --------");
		dprintf(1, "avant : angle = %d\n", structs->player->angle);
		structs->player->angle += structs->ray->angle10;
		if (structs->player->angle >= structs->ray->angle360)
		{
			puts("maintenant_right");
			structs->player->angle -= structs->ray->angle360;
		}
		dprintf(1, "apres : angle = %d\n", structs->player->angle);
	}
	structs->player->x_dir = structs->ray->cos_table[structs->player->angle];
	structs->player->y_dir = structs->ray->sin_table[structs->player->angle];
	dprintf(1, "x_dir = %f | y_dir = %f\n", structs->player->x_dir, structs->player->y_dir);
}
