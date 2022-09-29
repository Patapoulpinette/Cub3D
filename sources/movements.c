/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:01:41 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/29 17:17:43 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(int key, t_structs *structs)
{
	(void) key;
	(void) structs;
	return ;
	//if (key == 13 && \
	//	structs->minimap->map[(int) ((structs->player->y + structs->player->dy * structs->player->speed) / structs->minimap->zoom)][(int) ((structs->player->x + structs->player->dx * structs->player->speed) / structs->minimap->zoom)] == '0')
	//{
	//	structs->player->x += structs->player->dx * structs->player->speed;
	//	structs->player->y += structs->player->dy * structs->player->speed;
	//}
	//else if (key == 1 && \
	//	structs->minimap->map[(int) ((structs->player->y - structs->player->dy * structs->player->speed) / structs->minimap->zoom)][(int) ((structs->player->x - structs->player->dx * structs->player->speed) / structs->minimap->zoom)] == '0')
	//{
	//	structs->player->x -= structs->player->dx * structs->player->speed;
	//	structs->player->y -= structs->player->dy * structs->player->speed;
	//}
}

void	translate_player(int key, t_structs *structs) //à revoir
{
	(void) key;
	(void) structs;
	return ;
}

void	rotate_camera(int key, t_structs *structs)
{
	(void) key;
	(void) structs;
	return ;
	//if (key == 123)
	//{
	//	structs->player->angle -= 0.05;
	//	if (structs->player->angle < 0)
	//		structs->player->angle += 2 * M_PI;
	//	structs->player->dx = cos(structs->player->angle) * 5;
	//	structs->player->dy = sin(structs->player->angle) * 5;
	//}
	//else if (key == 124)
	//{
	//	structs->player->angle += 0.05;
	//	if (structs->player->angle > 2 * M_PI)
	//		structs->player->angle -= 2 * M_PI;
	//	structs->player->dx = cos(structs->player->angle) * 5;
	//	structs->player->dy = sin(structs->player->angle) * 5;
	//}
}
