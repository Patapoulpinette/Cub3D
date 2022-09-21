/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:01:41 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/21 18:11:40 by dbouron          ###   ########lyon.fr   */
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

void	translate_player(int key, t_structs *structs) //à revoir
{
	if (key == 0)
	{
		structs->player->px += structs->player->pdy;
		structs->player->py += structs->player->pdx;
	}
	else if (key == 2)
	{
		structs->player->px -= structs->player->pdy;
		structs->player->py -= structs->player->pdx;
	}
}

void	rotate_camera(int key, t_structs *structs)
{
	if (key == 123)
	{
		dprintf(2, "123.1 %f\n", structs->player->pangle);
		structs->player->pangle -= 0.25;
		dprintf(2, "123.2 %f\n", structs->player->pangle);
		if (structs->player->pangle < 0)
			structs->player->pangle += 2 * M_PI;
		structs->player->pdx = cos(structs->player->pangle) * 5;
		structs->player->pdy = sin(structs->player->pangle) * 5;
	}
	else if (key == 124)
	{
		dprintf(2, "124.1 %f\n", structs->player->pangle);
		structs->player->pangle += 0.25;
		dprintf(2, "124.2 %f\n", structs->player->pangle);
		if (structs->player->pangle > 2 * M_PI)
			structs->player->pangle -= 2 * M_PI;
		structs->player->pdx = cos(structs->player->pangle) * 5;
		structs->player->pdy = sin(structs->player->pangle) * 5;
	}
}
