/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:01:41 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/12 15:41:48 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(int key, t_structs *structs)
{
	if (key == 13)
	{
		structs->player->py += structs->player->pdy;
		structs->player->px += structs->player->pdx;
	}
	else if (key == 1)
	{
		structs->player->py -= structs->player->pdy;
		structs->player->px -= structs->player->pdx;
	}
}

void	translate_player(int key, t_structs *structs)
{
	if (key == 0)
	{
		structs->player->px += structs->player->pdx;
	}
	else if (key == 2)
	{
		structs->player->px -= structs->player->pdx;
	}
}

void	rotate_camera(int key, t_structs *structs)
{
	if (key == 123)
	{
		structs->player->pa -= 0.1;
		if (structs->player->pa < 0)
			structs->player->pa += 2 * M_PI;
		structs->player->pdx = cos(structs->player->pa) * 5;
		structs->player->pdy = sin(structs->player->pa) * 5;
	}
	else if (key == 124)
	{
		structs->player->pa += 0.1;
		if (structs->player->pa > 2 * M_PI)
			structs->player->pa -= 2 * M_PI;
		structs->player->pdx = cos(structs->player->pa) * 5;
		structs->player->pdy = sin(structs->player->pa) * 5;
	}
}
