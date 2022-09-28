/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:01:41 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/28 14:59:11 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(int key, t_structs *structs)
{
	if (key == 13 && \
		structs->minimap->map[(int) ((structs->player->py + structs->player->dy * structs->player->speed) / structs->minimap->zoom)][(int) ((structs->player->px + structs->player->dx * structs->player->speed) / structs->minimap->zoom)] == '0')
	{
		structs->player->px += structs->player->dx * structs->player->speed;
		structs->player->py += structs->player->dy * structs->player->speed;
	}
	else if (key == 1 && \
		structs->minimap->map[(int) ((structs->player->py - structs->player->dy * structs->player->speed) / structs->minimap->zoom)][(int) ((structs->player->px - structs->player->dx * structs->player->speed) / structs->minimap->zoom)] == '0')
	{
		structs->player->px -= structs->player->dx * structs->player->speed;
		structs->player->py -= structs->player->dy * structs->player->speed;
	}
}

void	translate_player(int key, t_structs *structs) //à revoir
{
	if (key == 0)
	{
		structs->player->px += structs->player->dy;
		structs->player->py += structs->player->dx;
	}
	else if (key == 2)
	{
		structs->player->px -= structs->player->dy;
		structs->player->py -= structs->player->dx;
	}
}

void	rotate_camera(int key, t_structs *structs)
{
	if (key == 123)
	{
		structs->player->angle -= 0.05;
		if (structs->player->angle < 0)
			structs->player->angle += 2 * M_PI;
		structs->player->dx = cos(structs->player->angle) * 5;
		structs->player->dy = sin(structs->player->angle) * 5;
	}
	else if (key == 124)
	{
		structs->player->angle += 0.05;
		if (structs->player->angle > 2 * M_PI)
			structs->player->angle -= 2 * M_PI;
		structs->player->dx = cos(structs->player->angle) * 5;
		structs->player->dy = sin(structs->player->angle) * 5;
	}
}
